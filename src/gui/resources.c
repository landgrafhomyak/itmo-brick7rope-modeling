#include <Windows.h>
#include "../app.h"

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app)
{
    if ((app->main_icon = LoadIconA(app->hInstance, "MAIN_ICON")) == NULL)
    { goto FREE_AND_ERR_0; }
    if ((app->button_icons.add = LoadIconA(app->hInstance, "BUTTON_ADD")) == NULL)
    { goto FREE_AND_ERR_1; }
    if ((app->button_icons.remove = LoadIconA(app->hInstance, "BUTTON_REMOVE")) == NULL)
    { goto FREE_AND_ERR_2; }

    app->canvas_cursor = NULL;

    return TRUE;

    FREE_AND_ERR_2:
    DestroyIcon(app->button_icons.add);

    FREE_AND_ERR_1:
    DestroyIcon(app->main_icon);

    FREE_AND_ERR_0:
    return FALSE;
}

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app)
{
    DestroyIcon(app->button_icons.remove);
    DestroyIcon(app->button_icons.add);
    DestroyIcon(app->main_icon);
}