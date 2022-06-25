cmake_minimum_required(VERSION 3.5)
project(brick7rope-modeling C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(
        brick7rope-modeling

        src/gui/processors.c

        src/main.c

        src/gui/classes.c
        src/common.h
        src/gui.h

        res/resources.rc
        src/app.h
        src/gui/resources.c
        src/gui/mainloop.c
        src/gui/windows.c
        src/gui/processors.h
        src/gui/main_window_data.h
        src/gui/render.cpp
        src/objects/stack.h
        src/objects/stack.c
        src/objects/scene.h
        src/objects/scene.c
        src/objects/brick.h
        src/objects/brick.c
        src/objects/rope.h
        src/objects/rope.c
        src/objects/scene_arena.h
        src/objects/scene_arena.c
        src/engine.c
        src/threads.h
        # src/gui/button.hpp
        # src/gui/button.cpp
        # src/gui/toolpanel.cpp
)

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