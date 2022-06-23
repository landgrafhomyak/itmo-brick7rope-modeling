#include <windows.h>
#include "../app.h"

BOOL Brick7RopeModeling_CreateGUI(Brick7RopeModeling_App *app)
{
    app->main_window = CreateWindowExW(
            WS_EX_APPWINDOW | WS_EX_CONTROLPARENT | WS_EX_NOINHERITLAYOUT,
            app->main_window_class,
            L"Brick&Rope Modeling",
            WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->main_window == NULL)
    { goto FREE_AND_ERR_0; }

    return TRUE;

    FREE_AND_ERR_0:
    return FALSE;
}