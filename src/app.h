#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>
# include "objects/scene_arena.h"
# include "objects/stack.h"
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
        HICON cancel;
        HICON reset;
        HICON resume;
        HICON pause;
        HICON undo;
        HICON redo;
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
        HWND cancel;
        HWND reset;
        HWND resume;
        HWND pause;
        HWND undo;
        HWND redo;
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

    /* App runtime data */
    CRITICAL_SECTION engine_state;
    CRITICAL_SECTION render_access_mutex;
    long double x;
    long double y;
    float zoom;

    DWORD main_window_width;
    DWORD main_window_height;

    struct
    {
        HDC hdc;

        DWORD width;
        DWORD height;

        HBITMAP bitmap1;
        void *bitmap1_data;
        HBITMAP bitmap2;
        void *bitmap2_data;
    } render_accessories;

    Brick7RopeModeling_SceneArena scene_arena;
    Brick7RopeModeling_Stack stack;
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
