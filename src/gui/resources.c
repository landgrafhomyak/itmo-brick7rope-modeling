#include <windows.h>
#include "../app.h"

#define LOAD_BUTTON_ICON(FIELD, RESOURCE, LABEL_NO)                                 \
    if ((app->button_icons.FIELD = LoadIconA(app->hInstance, RESOURCE)) == NULL)    \
    { goto FREE_AND_ERR_ ## LABEL_NO; }                                             \
    ((void)0)

#define DESTROY_BUTTON_ICON_ON_FAIL(FIELD, LABEL_NO)    \
    FREE_AND_ERR_ ## LABEL_NO:                          \
    if (app->button_icons.FIELD != NULL)                \
    { DestroyIcon(app->button_icons.FIELD); }           \
    ((void)0)

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app)
{
    if ((app->main_icon = LoadIconA(app->hInstance, "MAIN_ICON")) == NULL)
    { goto FREE_AND_ERR_0; }

    LOAD_BUTTON_ICON(save_capture, "BUTTON_SAVE_CAPTURE", 1);
    LOAD_BUTTON_ICON(save_capture_as, "BUTTON_SAVE_CAPTURE_AS", 2);
    LOAD_BUTTON_ICON(load_capture, "BUTTON_LOAD_CAPTURE", 3);
    LOAD_BUTTON_ICON(reset, "BUTTON_RESET", 4);
    LOAD_BUTTON_ICON(resume, "BUTTON_RESUME", 5);
    LOAD_BUTTON_ICON(pause, "BUTTON_PAUSE", 6);
    LOAD_BUTTON_ICON(undo, "BUTTON_UNDO", 7);
    LOAD_BUTTON_ICON(redo, "BUTTON_REDO", 8);
    LOAD_BUTTON_ICON(clear, "BUTTON_CLEAR", 9);
    LOAD_BUTTON_ICON(cancel_selection, "BUTTON_CANCEL_SELECTION", 10);
    LOAD_BUTTON_ICON(select_brick, "BUTTON_SELECT_BRICK", 11);
    LOAD_BUTTON_ICON(select_rope, "BUTTON_SELECT_ROPE", 12);
    LOAD_BUTTON_ICON(cancel_action, "BUTTON_CANCEL_ACTION", 13);
    LOAD_BUTTON_ICON(pan_scene, "BUTTON_PAN_SCENE", 14);
    LOAD_BUTTON_ICON(add_brick, "BUTTON_ADD_BRICK", 15);
    LOAD_BUTTON_ICON(remove_brick, "BUTTON_REMOVE_BRICK", 16);
    LOAD_BUTTON_ICON(add_rope, "BUTTON_ADD_ROPE", 17);
    LOAD_BUTTON_ICON(remove_rope, "BUTTON_REMOVE_ROPE", 18);
    LOAD_BUTTON_ICON(lock_brick, "BUTTON_LOCK_BRICK", 19);
    LOAD_BUTTON_ICON(unlock_brick, "BUTTON_UNLOCK_BRICK", 20);
    LOAD_BUTTON_ICON(drag_brick, "BUTTON_DRAG_BRICK", 21);

    return TRUE;


    DESTROY_BUTTON_ICON_ON_FAIL(drag_brick, 22);
    DESTROY_BUTTON_ICON_ON_FAIL(unlock_brick, 21);
    DESTROY_BUTTON_ICON_ON_FAIL(lock_brick, 20);
    DESTROY_BUTTON_ICON_ON_FAIL(remove_rope, 19);
    DESTROY_BUTTON_ICON_ON_FAIL(add_rope, 18);
    DESTROY_BUTTON_ICON_ON_FAIL(remove_brick, 17);
    DESTROY_BUTTON_ICON_ON_FAIL(add_brick, 16);
    DESTROY_BUTTON_ICON_ON_FAIL(pan_scene, 15);
    DESTROY_BUTTON_ICON_ON_FAIL(cancel_action, 14);
    DESTROY_BUTTON_ICON_ON_FAIL(select_rope, 13);
    DESTROY_BUTTON_ICON_ON_FAIL(select_brick, 12);
    DESTROY_BUTTON_ICON_ON_FAIL(cancel_selection, 11);
    DESTROY_BUTTON_ICON_ON_FAIL(clear, 10);
    DESTROY_BUTTON_ICON_ON_FAIL(redo, 9);
    DESTROY_BUTTON_ICON_ON_FAIL(undo, 8);
    DESTROY_BUTTON_ICON_ON_FAIL(pause, 7);
    DESTROY_BUTTON_ICON_ON_FAIL(resume, 6);
    DESTROY_BUTTON_ICON_ON_FAIL(reset, 5);
    DESTROY_BUTTON_ICON_ON_FAIL(load_capture, 4);
    DESTROY_BUTTON_ICON_ON_FAIL(save_capture_as, 3);
    DESTROY_BUTTON_ICON_ON_FAIL(save_capture, 2);

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