cmake_minimum_required(VERSION 3.5)
project(brick7rope-modeling)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)


add_executable(brick7rope-modeling
        src/engine_manager.cpp
        src/main.cpp
        src/mainwindow.cpp
        src/scene.cpp

        src/brick.hpp
        src/engine_manager.hpp
        src/mainwindow.hpp
        src/rope.hpp
        src/scene.hpp
)

install(TARGETS brick7rope-modeling)