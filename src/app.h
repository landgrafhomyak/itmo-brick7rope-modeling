#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>
# include "gui/main_window_data.h"

# ifdef __cplusplus
extern "C" {
# endif

typedef struct Brick7RopeModeling_App
{
    /* Configuration */
    unsigned short button_size;

    /* Predefined handlers */
    HINSTANCE hInstance;

    /* Resources */
    HICON main_icon;
    HCURSOR canvas_cursor;
    struct
    {
        HICON add_brick;
        HICON remove_brick;
        HICON add_rope;
        HICON remove_rope;
        HICON lock_brick;
        HICON unlock_brick;
    } button_icons;

    /* Window classes */
    ATOM main_window_class;
    ATOM tool_panel_window_class;

    /* Window instances */
    HWND main_window;
    HWND tool_panel_window;
    struct
    {
        HWND add_brick;
        HWND remove_brick;
        HWND add_rope;
        HWND remove_rope;
        HWND lock_brick;
        HWND unlock_brick;
    } tool_panel_stuff_windows;

    /* Workers */
    HANDLE render_thread;
    HANDLE engine_thread;

    /* Windows extra data */
    Brick7RopeModeling_GUI_MainWindow_Data main_window_data;
} Brick7RopeModeling_App;

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app);

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_RegisterWindowClasses(Brick7RopeModeling_App *app);

void Brick7RopeModeling_UnRegisterWindowClasses(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_CreateAndShowWindows(Brick7RopeModeling_App *app);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_APP_H */
