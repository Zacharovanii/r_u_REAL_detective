cmake_minimum_required(VERSION 3.20)
project(r_u_REAL_detective LANGUAGES CXX)

# ---- Настройка стандарта C++ ----
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Определение платформы ----
if(WIN32)
    message(STATUS "Building for Windows")
    set(PLATFORM_WINDOWS 1)
    set(PLATFORM_POSIX 0)
    add_definitions(-D_WIN32_WINNT=0x0A00)  # Windows 10

    # Для статической линковки библиотек C++ (РЕШЕНИЕ ПРОБЛЕМЫ С DLL)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
else()
    message(STATUS "Building for Unix-like system")
    set(PLATFORM_WINDOWS 0)
    set(PLATFORM_POSIX 1)
endif()

# ---- Настройки компилятора ----
if(MSVC)
    # Настройки для Visual Studio
    add_compile_options(/W4 /WX)  # Все предупреждения как ошибки
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS NOMINMAX)
else()
    # Настройки для GCC/Clang/MinGW
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)

    # Для MinGW на Windows - важные флаги
    if(WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        # Статическая линковка для GCC/MinGW
        add_compile_options(-static-libgcc -static-libstdc++ -static)
    endif()

    # Отключаем конкретные предупреждения если нужно
    add_compile_options(-Wno-unused-parameter)
    add_compile_options(-Wno-sign-compare)
endif()

# ---- Собираем список всех исходников ----
file(GLOB_RECURSE GAME_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/*.cpp"
)

message(STATUS "Found ${GAME_SOURCES} source files")

# ---- Создаём библиотеку с реализацией игры ----
add_library(game_lib STATIC ${GAME_SOURCES})

# Подключаем все include/ директории
target_include_directories(game_lib PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---- Копирование ресурсов ----
set(DATA_DESTINATION "${CMAKE_BINARY_DIR}")

# Создаем кастомную цель для копирования данных
add_custom_target(copy_data ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DATA_DESTINATION}/data"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "${DATA_DESTINATION}/data"
        COMMENT "Copying data files..."
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# ---- Настройки линковки в зависимости от платформы ----
if(PLATFORM_WINDOWS)
    # Windows специфичные библиотеки
    target_link_libraries(game_lib PRIVATE
            ws2_32  # Для сетевых функций (если нужно)
            # winmm   # Для мультимедиа (если нужно)
    )

    # Для поддержки UTF-8 в выводе
    target_compile_definitions(game_lib PRIVATE
            UNICODE
            _UNICODE
    )

    # Настройки для MinGW
    if(MINGW)
        # Полностью статическая линковка для MinGW
        set_target_properties(game_lib PROPERTIES
                LINK_FLAGS "-static"
        )
    endif()

    # Настройки для Release сборки
    if(CMAKE_BUILD_TYPE STREQUAL "Release" AND MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    endif()
else()
    # Unix-like системы
    find_package(Threads REQUIRED)
    target_link_libraries(game_lib PRIVATE
            Threads::Threads
    )
endif()

# ---- Санитайзеры ТОЛЬКО ДЛЯ DEBUG (и только для GCC/Clang) ----
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
    message(STATUS "Enabling sanitizers for Debug build")

    # Проверяем поддержку санитайзеров
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(-fsanitize=address HAS_ASAN)
    check_cxx_compiler_flag(-fsanitize=undefined HAS_UBSAN)

    if(HAS_ASAN AND HAS_UBSAN)
        target_compile_options(game_lib PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
        )
        target_link_options(game_lib PRIVATE
                -fsanitize=address,undefined
        )
    else()
        message(WARNING "Sanitizers not supported by compiler")
    endif()
endif()

# ---- Главный exe ----
# Указываем main.cpp явно
add_executable(Game main.cpp)

# Связываем с библиотекой
target_link_libraries(Game PRIVATE game_lib)

# Наследуем include директории
target_include_directories(Game PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Добавляем зависимость от копирования данных
add_dependencies(Game copy_data)

# Установка выходного пути для удобства
set_target_properties(Game PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_NAME "Game"
        OUTPUT_NAME "Game"
)

# Для Windows - устанавливаем рабочую директорию при запуске из IDE
if(PLATFORM_WINDOWS)
    # Для всех генераторов CMake
    set_target_properties(Game PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_BINARY_DIR};%PATH%"
    )
endif()

# ---- Post-build копирование DLL для Windows (если не статическая линковка) ----
if(PLATFORM_WINDOWS AND NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Копируем необходимые DLL для MinGW если не используем статическую линковку
    find_program(MINGW_PATH mingw32-make PATHS
            "C:/Program Files/mingw64/bin"
            "C:/MinGW/bin"
            "C:/msys64/mingw64/bin"
            ENV PATH
    )

    if(MINGW_PATH AND NOT CMAKE_EXE_LINKER_FLAGS MATCHES "-static")
        get_filename_component(MINGW_BIN_DIR "${MINGW_PATH}/../bin" ABSOLUTE)

        add_custom_command(TARGET Game POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/libstdc++-6.dll"
                "${CMAKE_BINARY_DIR}/libstdc++-6.dll"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
                "${CMAKE_BINARY_DIR}/libgcc_s_seh-1.dll"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${MINGW_BIN_DIR}/libwinpthread-1.dll"
                "${CMAKE_BINARY_DIR}/libwinpthread-1.dll"
                COMMENT "Copying MinGW runtime DLLs"
        )
    endif()
endif()

# ---- Полезные опции для пользователя ----
option(USE_STATIC_RUNTIME "Link C++ runtime statically" ON)
option(ENABLE_SANITIZERS "Enable address and undefined sanitizers" OFF)

if(USE_STATIC_RUNTIME AND WIN32 AND NOT MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    message(STATUS "Static linking enabled for MinGW")
endif()

# ---- Информация о сборке ----
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Binary output: ${CMAKE_BINARY_DIR}/Game${CMAKE_EXECUTABLE_SUFFIX}")