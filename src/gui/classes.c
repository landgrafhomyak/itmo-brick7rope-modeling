#include <stddef.h>

#include <windows.h>

#include "../common.h"
#include "../app.h"
#include "../gui.h"


BOOL Brick7RopeModeling_RegisterWindowClasses(Brick7RopeModeling_App *app)
{
    WNDCLASSEXW MainWindow_Class = {
            .cbSize = sizeof(WNDCLASSEXW),
            .style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
            .lpfnWndProc = DefWindowProcW, // todo
            .cbClsExtra = 0,
            .cbWndExtra = 0,
            .hInstance = app->hInstance,
            .hIcon = app->main_icon,
            .hCursor = app->canvas_cursor,
            .hbrBackground = NULL,
            .lpszMenuName = NULL,
            .lpszClassName = Brick7RopeModeling_MainWindow_ClassName,
            .hIconSm = NULL
    };

    MainWindow_Class.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    if (MainWindow_Class.hbrBackground == NULL)
    { goto MAIN_WINDOW_ERR_0; }

    app->main_window_class = RegisterClassExW(&MainWindow_Class);
    if (app->main_window_class == 0)
    { goto MAIN_WINDOW_ERR_1; }


    WNDCLASSEXW ToolPanel_Class = {
            .cbSize = sizeof(WNDCLASSEXW),
            .style = CS_NOCLOSE,
            .lpfnWndProc = DefWindowProcW,
            .cbClsExtra = 0,
            .cbWndExtra = 0,
            .hInstance = app->hInstance,
            .hIcon = app->main_icon,
            .hCursor = NULL,
            .hbrBackground = NULL,
            .lpszMenuName = NULL,
            .lpszClassName = Brick7RopeModeling_ToolPanel_ClassName,
            .hIconSm = NULL
    };

    app->tool_panel_window_class = RegisterClassExW(&ToolPanel_Class);
    if (app->tool_panel_window_class == 0)
    { goto TOOL_PANEL_ERR_0; }

    return TRUE;

    UnregisterClassW(ATOM_AS_LPCWSTR(app->tool_panel_window_class), app->hInstance);

    if (0)
    {
        TOOL_PANEL_ERR_0:
        (void) 0;
    }

    UnregisterClassW(ATOM_AS_LPCWSTR(app->main_window_class), app->hInstance);

    if (0)
    {
        MAIN_WINDOW_ERR_1:
        DeleteObject(MainWindow_Class.hbrBackground);
        MAIN_WINDOW_ERR_0:
        (void) 0;
    }

    return FALSE;
}

void Brick7RopeModeling_UnRegisterWindowClasses(Brick7RopeModeling_App *app)
{
    UnregisterClassW(ATOM_AS_LPCWSTR(app->tool_panel_window_class), app->hInstance);
    UnregisterClassW(ATOM_AS_LPCWSTR(app->main_window_class), app->hInstance);
}
