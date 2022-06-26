#include <windows.h>
#include "../common.h"
#include "../app.h"
#include "processors.h"

#define CREATE_BUTTON(FIELD, NAME, POS, LABEL_NO1, LABEL_NO2)               \
    app->tool_panel_stuff_windows.FIELD = CreateWindowExW(                  \
    WS_EX_NOPARENTNOTIFY,                                                   \
    L"Button",                                                              \
    NAME,                                                                   \
    WS_VISIBLE | WS_CHILD | BS_ICON,                                        \
    app->button_size * POS,                                                 \
    0,                                                                      \
    app->button_size,                                                       \
    app->button_size,                                                       \
    app->tool_panel_window,                                                 \
    NULL,                                                                   \
    app->hInstance,                                                         \
    NULL                                                                    \
    );                                                                      \
    if (app->tool_panel_stuff_windows.FIELD == NULL)                        \
    { goto FREE_AND_ERR_ ## LABEL_NO1; }                                    \
    if (                                                                    \
        SendMessageW(                                                       \
            app->tool_panel_stuff_windows.FIELD,                            \
            BM_SETIMAGE,                                                    \
            IMAGE_ICON,                                                     \
            (LPARAM) (app->button_icons.FIELD)                              \
        ) != 0                                                              \
    )                                                                       \
    { goto FREE_AND_ERR_ ## LABEL_NO2; }                                    \
    ((void)0)

#define DESTROY_BUTTON(FIELD, LABEL_NO)                     \
    FREE_AND_ERR_ ## LABEL_NO:                              \
    DestroyWindow(app->tool_panel_stuff_windows.FIELD);     \
    ((void)0)

BOOL Brick7RopeModeling_CreateAndShowWindows(Brick7RopeModeling_App *app)
{
    app->main_window = CreateWindowExW(
            WS_EX_APPWINDOW | WS_EX_CONTROLPARENT | WS_EX_NOINHERITLAYOUT,
            ATOM_AS_LPCWSTR(app->main_window_class),
            L"Brick&Rope Modeling v1.0+",
            WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            app->hInstance,
            app
    );
    if (app->main_window == NULL)
    { goto FREE_AND_ERR_0; }

    RECT tool_panel_window_rect = {.top=0, .left=0, .right=app->button_size * 21, .bottom=app->button_size};
    DWORD tool_panel_window_style = WS_POPUP | WS_CAPTION;

    AdjustWindowRect(&tool_panel_window_rect, tool_panel_window_style, FALSE);

    app->tool_panel_window = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY | WS_EX_TOOLWINDOW,
            ATOM_AS_LPCWSTR(app->tool_panel_window_class),
            L"Actions",
            tool_panel_window_style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            tool_panel_window_rect.right - tool_panel_window_rect.left,
            tool_panel_window_rect.bottom - tool_panel_window_rect.top,
            app->main_window,
            NULL,
            app->hInstance,
            app
    );
    if (app->tool_panel_window == NULL)
    { goto FREE_AND_ERR_1; }

    CREATE_BUTTON(save_capture, L"Save capture", 0, 1, 1);
    CREATE_BUTTON(save_capture_as, L"Save capture as", 1, 1, 1);
    CREATE_BUTTON(load_capture, L"Load capture", 2, 1, 1);
    CREATE_BUTTON(reset, L"Reset", 3, 1, 1);
    CREATE_BUTTON(resume, L"Resume", 4, 1, 1);
    CREATE_BUTTON(pause, L"Pause", 5, 1, 1);
    CREATE_BUTTON(undo, L"Undo", 6, 1, 1);
    CREATE_BUTTON(redo, L"Redo", 7, 1, 1);
    CREATE_BUTTON(clear, L"Clear", 8, 1, 1);
    CREATE_BUTTON(cancel_selection, L"Cancel selection", 9, 1, 1);
    CREATE_BUTTON(select_brick, L"Select brick", 10, 1, 1);
    CREATE_BUTTON(select_rope, L"Select rope", 11, 1, 1);
    CREATE_BUTTON(cancel_action, L"Cancel state", 12, 1, 1);
    CREATE_BUTTON(pan_scene, L"Pan scene", 13, 1, 1);
    CREATE_BUTTON(add_brick, L"Add brick", 14, 1, 1);
    CREATE_BUTTON(remove_brick, L"Remove brick", 15, 1, 1);
    CREATE_BUTTON(add_rope, L"Add rope", 16, 1, 1);
    CREATE_BUTTON(remove_rope, L"Remove rope", 17, 1, 1);
    CREATE_BUTTON(lock_brick, L"Lock brick", 18, 1, 1);
    CREATE_BUTTON(unlock_brick, L"Unlock brick", 19, 1, 1);
    CREATE_BUTTON(drag_brick, L"Drag brick", 20, 1, 1);

    EnableWindow(app->tool_panel_stuff_windows.save_capture, FALSE);
    EnableWindow(app->tool_panel_stuff_windows.save_capture_as, FALSE);
    EnableWindow(app->tool_panel_stuff_windows.load_capture, FALSE);
    EnableWindow(app->tool_panel_stuff_windows.pan_scene, FALSE);

    ShowWindow(app->main_window, SW_SHOW);
    ShowWindow(app->tool_panel_window, SW_SHOW);

    return TRUE;
    FREE_AND_ERR_1:
    DestroyWindow(app->main_window);

    FREE_AND_ERR_0:
    return FALSE;
}