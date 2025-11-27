cmake_minimum_required(VERSION 3.28)
project(r_u_REAL_detective)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game
        main.cpp
        src/model/Model.cpp
        src/view/View.cpp
        src/controller/Controller.cpp
)
