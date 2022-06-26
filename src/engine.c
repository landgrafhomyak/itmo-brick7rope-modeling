#include <math.h>

#include <windows.h>

#include "objects/scene.h"
#include "app.h"
#include "threads.h"


static unsigned long long Brick7RopeModeling_GetTicks(void)
{

    FILETIME ft;
    ULARGE_INTEGER li;

    GetSystemTimeAsFileTime(&ft);

    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    return li.QuadPart;
}


DWORD DECLSPEC_NORETURN Brick7RopeModeling_EngineThreadMain(Brick7RopeModeling_App *app)
{
    Brick7RopeModeling_Scene local_scene;
    Brick7RopeModeling_Scene new_scene;
    long double a, ax, ay, f, dl, dt;
    size_t brick_index, rope_index;
    unsigned long long prev_time = Brick7RopeModeling_GetTicks();


    Brick7RopeModeling_Scene_Init(&local_scene);
    Brick7RopeModeling_Scene_Init(&new_scene);

    while (TRUE)
    {
        EnterCriticalSection(&(app->engine_state));
        LeaveCriticalSection(&(app->engine_state));
        EnterCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Copy(&(app->engine_out), &local_scene);
        LeaveCriticalSection(&(app->engine_mutex));

        dt = (long double) (Brick7RopeModeling_GetTicks() - prev_time) / 10000000;
        prev_time = Brick7RopeModeling_GetTicks();

        Brick7RopeModeling_Scene_Copy(&local_scene, &new_scene);

        for (brick_index = 0; brick_index < local_scene.bricks_count; brick_index++)
        {
            if (local_scene.bricks[brick_index].is_locked)
            { continue; }
            new_scene.bricks[brick_index].x += local_scene.bricks[brick_index].sx * (long double) dt;
            new_scene.bricks[brick_index].y += local_scene.bricks[brick_index].sy * (long double) dt;
            ax = 0, ay = 0;
            for (rope_index = 0; rope_index < local_scene.ropes_count; rope_index++)
            {
                if (brick_index != local_scene.ropes[rope_index].brick1_index && brick_index != local_scene.ropes[rope_index].brick2_index)
                { continue; }
                dl = -local_scene.ropes[rope_index].length + hypotl(local_scene.bricks[local_scene.ropes[rope_index].brick1_index].x - local_scene.bricks[local_scene.ropes[rope_index].brick2_index].x, local_scene.bricks[local_scene.ropes[rope_index].brick1_index].y - local_scene.bricks[local_scene.ropes[rope_index].brick2_index].y);
                f = local_scene.ropes[rope_index].young_module * local_scene.ropes[rope_index].square * dl / local_scene.ropes[rope_index].length;

                a = f / local_scene.bricks[brick_index].mass;

                if (brick_index == local_scene.ropes[rope_index].brick1_index && local_scene.bricks[local_scene.ropes[rope_index].brick2_index].is_locked)
                {}
                if (brick_index == local_scene.ropes[rope_index].brick2_index && local_scene.bricks[local_scene.ropes[rope_index].brick1_index].is_locked)
                {}
                else
                { a /= 2; }

                if (brick_index == local_scene.ropes[rope_index].brick1_index)
                {
                    ax += (local_scene.bricks[local_scene.ropes[rope_index].brick2_index].x - local_scene.bricks[local_scene.ropes[rope_index].brick1_index].x) / (dl + local_scene.ropes[rope_index].length) * a;
                    ay += (local_scene.bricks[local_scene.ropes[rope_index].brick2_index].y - local_scene.bricks[local_scene.ropes[rope_index].brick1_index].y) / (dl + local_scene.ropes[rope_index].length) * a;
                }
                else
                {
                    ax += (local_scene.bricks[local_scene.ropes[rope_index].brick1_index].x - local_scene.bricks[local_scene.ropes[rope_index].brick2_index].x) / (dl + local_scene.ropes[rope_index].length) * a;
                    ay += (local_scene.bricks[local_scene.ropes[rope_index].brick1_index].y - local_scene.bricks[local_scene.ropes[rope_index].brick2_index].y) / (dl + local_scene.ropes[rope_index].length) * a;
                }
            }
            new_scene.bricks[brick_index].sx += ax * (long double) dt;
            new_scene.bricks[brick_index].sy += ay * (long double) dt;
        }


        Brick7RopeModeling_Scene_Finalize(&local_scene);

        EnterCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Finalize(&(app->engine_out));
        app->engine_out = new_scene;
        Brick7RopeModeling_Scene_Init(&new_scene);
        LeaveCriticalSection(&(app->engine_mutex));
    }
}