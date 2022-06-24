#include <windows.h>

#include "../objects/scene.h"
#include "../app.h"
#include "../threads.h"

DWORD Brick7RopeModeling_RenderThreadMain(Brick7RopeModeling_App *app)
{
    Brick7RopeModeling_Scene local_scene;

    Brick7RopeModeling_Scene_Init(&local_scene);

    while (TRUE)
    {
        LeaveCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Copy(&(app->engine_out), &local_scene);
        LeaveCriticalSection(&(app->engine_mutex));

        /* todo */

        Brick7RopeModeling_Scene_Finalize(&(app->engine_out));
    }
}