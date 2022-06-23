#include <windows.h>
#include "../common.h"
#include "../app.h"

BOOL Brick7RopeModeling_CreateAndShowWindows(Brick7RopeModeling_App *app)
{
    app->main_window = CreateWindowExW(
            WS_EX_APPWINDOW | WS_EX_CONTROLPARENT | WS_EX_NOINHERITLAYOUT,
            ATOM_AS_LPCWSTR(app->main_window_class),
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

    RECT tool_panel_window_rect = {.top=0, .left=0, .right=app->button_size * 6, .bottom=app->button_size};
    DWORD tool_panel_window_style=WS_POPUP | WS_CAPTION;

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
            NULL
    );
    if (app->tool_panel_window == NULL)
    { goto FREE_AND_ERR_1; }

    app->tool_panel_stuff_windows.add_brick = CreateWindowExW(
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
    if (app->tool_panel_stuff_windows.add_brick == NULL)
    { goto FREE_AND_ERR_2; }

    if (SendMessageW(app->tool_panel_stuff_windows.add_brick, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.add_brick)) != 0)
    { goto FREE_AND_ERR_3; }

    app->tool_panel_stuff_windows.remove_brick = CreateWindowExW(
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
    if (app->tool_panel_stuff_windows.remove_brick == NULL)
    { goto FREE_AND_ERR_3; }

    if (SendMessageW(app->tool_panel_stuff_windows.remove_brick, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.remove_brick)) != 0)
    { goto FREE_AND_ERR_4; }
    app->tool_panel_stuff_windows.add_rope = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Add rope",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 2,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->tool_panel_stuff_windows.add_rope == NULL)
    { goto FREE_AND_ERR_4; }

    if (SendMessageW(app->tool_panel_stuff_windows.add_rope, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.add_rope)) != 0)
    { goto FREE_AND_ERR_5; }

    app->tool_panel_stuff_windows.remove_rope = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Remove rope",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 3,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->tool_panel_stuff_windows.remove_rope == NULL)
    { goto FREE_AND_ERR_5; }

    if (SendMessageW(app->tool_panel_stuff_windows.remove_rope, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.remove_rope)) != 0)
    { goto FREE_AND_ERR_6; }

    app->tool_panel_stuff_windows.lock_brick = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Lock brick",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 4,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->tool_panel_stuff_windows.lock_brick == NULL)
    { goto FREE_AND_ERR_6; }

    if (SendMessageW(app->tool_panel_stuff_windows.lock_brick, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.lock_brick)) != 0)
    { goto FREE_AND_ERR_7; }

    app->tool_panel_stuff_windows.unlock_brick = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            L"Unlock brick",
            WS_VISIBLE | WS_CHILD | BS_ICON,
            app->button_size * 5,
            0,
            app->button_size,
            app->button_size,
            app->tool_panel_window,
            NULL,
            app->hInstance,
            NULL
    );
    if (app->tool_panel_stuff_windows.unlock_brick == NULL)
    { goto FREE_AND_ERR_7; }

    if (SendMessageW(app->tool_panel_stuff_windows.unlock_brick, BM_SETIMAGE, IMAGE_ICON, (LPARAM)(app->button_icons.unlock_brick)) != 0)
    { goto FREE_AND_ERR_8; }

    ShowWindow(app->main_window, SW_SHOW);
    ShowWindow(app->tool_panel_window, SW_SHOW);

    return TRUE;
    FREE_AND_ERR_8:
    DestroyWindow(app->tool_panel_stuff_windows.unlock_brick);

    FREE_AND_ERR_7:
    DestroyWindow(app->tool_panel_stuff_windows.lock_brick);

    FREE_AND_ERR_6:
    DestroyWindow(app->tool_panel_stuff_windows.remove_rope);

    FREE_AND_ERR_5:
    DestroyWindow(app->tool_panel_stuff_windows.add_rope);

    FREE_AND_ERR_4:
    DestroyWindow(app->tool_panel_stuff_windows.remove_brick);

    FREE_AND_ERR_3:
    DestroyWindow(app->tool_panel_stuff_windows.add_brick);

    FREE_AND_ERR_2:
    DestroyWindow(app->tool_panel_window);

    FREE_AND_ERR_1:
    DestroyWindow(app->main_window);

    FREE_AND_ERR_0:
    return FALSE;
}