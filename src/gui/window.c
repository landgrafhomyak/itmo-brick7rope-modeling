#include <windows.h>
#include "../app.h"

BOOL Brick7RopeModeling_CreateGUI(Brick7RopeModeling_App *app)
{
    app->main_window = CreateWindowExW(
            WS_EX_APPWINDOW | WS_EX_CONTROLPARENT | WS_EX_NOINHERITLAYOUT,
            app->main_window_class,
            L"Brick&Rope Modeling",
            WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
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

    app->tool_panel_window = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY | WS_EX_TOOLWINDOW,
            app->tool_panel_window_class,
            L"Actions",
            WS_POPUP | WS_CAPTION,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            app->button_size * 2 + 100,
            app->button_size + 100,
            app->main_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->tool_panel_window == NULL)
    { goto FREE_AND_ERR_1; }

    app->button_windows.add = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Add brick",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 0,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->button_windows.add == NULL)
    { goto FREE_AND_ERR_2; }

    if (SendMessageW(app->button_windows.add, BM_SETIMAGE, IMAGE_ICON, app->button_icons.add) != 0)
    { goto FREE_AND_ERR_3; }

    app->button_windows.remove = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Remove brick",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 1,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->button_windows.remove == NULL)
    { goto FREE_AND_ERR_3; }

    if (SendMessageW(app->button_windows.remove, BM_SETIMAGE, IMAGE_ICON, app->button_icons.remove) != 0)
    { goto FREE_AND_ERR_4; }

    ShowWindow(app->main_window, SW_SHOW);
    ShowWindow(app->tool_panel_window, SW_SHOW);

    return TRUE;
    FREE_AND_ERR_4:
    DestroyWindow(app->button_windows.remove);

    FREE_AND_ERR_3:
    DestroyWindow(app->button_windows.add);

    FREE_AND_ERR_2:
    DestroyWindow(app->tool_panel_window);

    FREE_AND_ERR_1:
    DestroyWindow(app->main_window);

    FREE_AND_ERR_0:
    return FALSE;
}