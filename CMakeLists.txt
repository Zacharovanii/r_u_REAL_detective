cmake_minimum_required(VERSION 3.20)
project(r_u_REAL_detective)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Собираем список всех исходников ----
file(GLOB_RECURSE GAME_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# ---- Создаём библиотеку с реализацией игры ----
add_library(game_lib ${GAME_SOURCES})

# Подключаем все include/ директории
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Добавляем предупреждения
target_compile_options(game_lib PRIVATE
        -Wall -Wextra -Wpedantic
)

# ---- Главный exe ----
add_executable(Game main.cpp)

target_link_libraries(Game PRIVATE game_lib)
