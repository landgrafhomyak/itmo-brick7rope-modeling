#include <windows.h>
#include "../app.h"

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app)
{
    if ((app->main_icon = LoadIconA(app->hInstance, "MAIN_ICON")) == NULL)
    { goto FREE_AND_ERR_0; }
    if ((app->button_icons.cancel = LoadIconA(app->hInstance, "BUTTON_CANCEL")) == NULL)
    { goto FREE_AND_ERR_1; }
    if ((app->button_icons.reset = LoadIconA(app->hInstance, "BUTTON_RESET")) == NULL)
    { goto FREE_AND_ERR_2; }
    if ((app->button_icons.resume = LoadIconA(app->hInstance, "BUTTON_RESUME")) == NULL)
    { goto FREE_AND_ERR_3; }
    if ((app->button_icons.pause = LoadIconA(app->hInstance, "BUTTON_PAUSE")) == NULL)
    { goto FREE_AND_ERR_4; }
#if 0
    if ((app->button_icons.undo = LoadIconA(app->hInstance, "BUTTON_UNDO")) == NULL)
    { goto FREE_AND_ERR_5; }
    if ((app->button_icons.redo = LoadIconA(app->hInstance, "BUTTON_REDO")) == NULL)
    { goto FREE_AND_ERR_6; }
#endif
    if ((app->button_icons.add_brick = LoadIconA(app->hInstance, "BUTTON_ADD_BRICK")) == NULL)
    { goto FREE_AND_ERR_7; }
    if ((app->button_icons.remove_brick = LoadIconA(app->hInstance, "BUTTON_REMOVE_BRICK")) == NULL)
    { goto FREE_AND_ERR_8; }
    if ((app->button_icons.add_rope = LoadIconA(app->hInstance, "BUTTON_ADD_ROPE")) == NULL)
    { goto FREE_AND_ERR_9; }
    if ((app->button_icons.remove_rope = LoadIconA(app->hInstance, "BUTTON_REMOVE_ROPE")) == NULL)
    { goto FREE_AND_ERR_10; }
    if ((app->button_icons.lock_brick = LoadIconA(app->hInstance, "BUTTON_LOCK_BRICK")) == NULL)
    { goto FREE_AND_ERR_11; }
    if ((app->button_icons.unlock_brick = LoadIconA(app->hInstance, "BUTTON_UNLOCK_BRICK")) == NULL)
    { goto FREE_AND_ERR_12; }

    app->canvas_cursor = NULL;

    return TRUE;

    FREE_AND_ERR_13:
    DestroyIcon(app->button_icons.unlock_brick);

    FREE_AND_ERR_12:
    DestroyIcon(app->button_icons.lock_brick);

    FREE_AND_ERR_11:
    DestroyIcon(app->button_icons.remove_rope);

    FREE_AND_ERR_10:
    DestroyIcon(app->button_icons.add_rope);

    FREE_AND_ERR_9:
    DestroyIcon(app->button_icons.remove_brick);

    FREE_AND_ERR_8:
    DestroyIcon(app->button_icons.add_brick);

    FREE_AND_ERR_7:
#if 0
    DestroyIcon(app->button_icons.redo);

    FREE_AND_ERR_6:
    DestroyIcon(app->button_icons.redo);
    FREE_AND_ERR_5:
#endif
    DestroyIcon(app->button_icons.pause);

    FREE_AND_ERR_4:
    DestroyIcon(app->button_icons.resume);

    FREE_AND_ERR_3:
    DestroyIcon(app->button_icons.reset);

    FREE_AND_ERR_2:
    DestroyIcon(app->button_icons.cancel);

    FREE_AND_ERR_1:
    DestroyIcon(app->main_icon);

    FREE_AND_ERR_0:
    return FALSE;
}

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app)
{
    DestroyIcon(app->button_icons.remove_rope);
    DestroyIcon(app->button_icons.add_rope);
    DestroyIcon(app->button_icons.remove_brick);
    DestroyIcon(app->button_icons.add_brick);
    DestroyIcon(app->main_icon);
}