cmake_minimum_required(VERSION 3.5)
project(brick7rope-modeling C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(
        brick7rope-modeling

        src/gui/processors.cpp

        src/main.c

        src/objects/brick.hpp
        src/objects/rope.hpp
        src/objects/scene.hpp
        src/objects/buffer.hpp
        src/objects/history.hpp

        src/gui/classes.c
        src/common.h
        src/gui.h

        res/resources.rc
        src/app.h
        src/gui/resources.c
        src/gui/mainloop.c
        src/gui/window.c
        src/gui/processors.h
        src/gui/main_window_data.h)

target_compile_definitions(brick7rope-modeling PUBLIC UNICODE)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    message(STATUS "Enabling debug output in app")
    target_compile_definitions(brick7rope-modeling PUBLIC Brick7RopeModeling_DEBUG_MODE)
endif ()

if (DEFINED MSVC)
    target_link_options(brick7rope-modeling PRIVATE /ENTRY:wWinMainCRTStartup)
endif ()
if (DEFINED MINGW)
    target_link_options(brick7rope-modeling PRIVATE -municode)
endif ()

install(TARGETS brick7rope-modeling)