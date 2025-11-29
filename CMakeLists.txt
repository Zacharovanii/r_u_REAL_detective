cmake_minimum_required(VERSION 3.20)
project(r_u_REAL_detective)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Настройки сборки ----
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build with sanitizers enabled")
    add_compile_options(-fno-omit-frame-pointer)
endif()

# ---- Собираем список всех исходников ----
file(GLOB_RECURSE GAME_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Копируем data, если исходники изменились
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/data
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_BINARY_DIR}/data
        DEPENDS ${CMAKE_SOURCE_DIR}/data
        COMMENT "Copying data files..."
)

# Создаем цель для копирования


# ---- Создаём библиотеку с реализацией игры ----
add_library(game_lib ${GAME_SOURCES})

add_custom_target(copy_data ALL DEPENDS ${CMAKE_BINARY_DIR}/data)
add_dependencies(game_lib copy_data)

# Подключаем все include/ директории
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Добавляем предупреждения
target_compile_options(game_lib PRIVATE
        -Wall -Wextra -Wpedantic -Werror
)

# ---- САНИТАЙЗЕРЫ ТОЛЬКО ДЛЯ DEBUG ----
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(game_lib PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )
    target_link_options(game_lib PRIVATE
            -fsanitize=address,undefined
    )
endif()

# ---- Главный exe ----
add_executable(Game main.cpp)

target_link_libraries(Game PRIVATE game_lib)

# Санитайзеры для исполняемого файла тоже
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Game PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
    )
    target_link_options(Game PRIVATE
            -fsanitize=address,undefined
    )
endif()