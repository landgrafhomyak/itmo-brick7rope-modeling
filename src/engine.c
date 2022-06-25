#include <windows.h>
#include <stdio.h>

#include "objects/scene.h"
#include "app.h"
#include "threads.h"

DWORD DECLSPEC_NORETURN Brick7RopeModeling_EngineThreadMain(Brick7RopeModeling_App *app)
{
    Brick7RopeModeling_Scene local_scene;

    Brick7RopeModeling_Scene_Init(&local_scene);

    while (TRUE)
    {
        EnterCriticalSection(&(app->engine_state));
        LeaveCriticalSection(&(app->engine_state));
        EnterCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Copy(&(app->engine_out), &local_scene);
        LeaveCriticalSection(&(app->engine_mutex));

        /* todo */

        EnterCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Finalize(&(app->engine_out));
        app->engine_out = local_scene;
        Brick7RopeModeling_Scene_Init(&local_scene);
        LeaveCriticalSection(&(app->engine_mutex));
    }
}