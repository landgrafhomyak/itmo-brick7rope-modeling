#include <Windows.h>
#include "../app.h"

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app)
{
    if ((app->main_icon = LoadIconA(app->hInstance, "MAIN_ICON")) == NULL)
    { goto FREE_AND_ERR_0; }

    app->canvas_cursor = NULL;

    return TRUE;

    FREE_AND_ERR_0:
    return FALSE;
}

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app)
{
    DestroyIcon(app->main_icon);
}