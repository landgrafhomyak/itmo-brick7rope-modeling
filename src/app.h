#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>
# include "objects/brick.h"
# include "objects/rope.h"
# include "objects/scene_arena.h"
# include "objects/stack.h"
# include "gui/main_window_data.h"

# ifdef __cplusplus
extern "C" {
# endif

struct Brick7RopeModeling_AppAction
{
    enum Brick7RopeModeling_AppAction_Type
    {
        Brick7RopeModeling_AppAction_Type_VOID,
        Brick7RopeModeling_AppAction_Type_NEW_BRICK,
        Brick7RopeModeling_AppAction_Type_NEW_ROPE_0,
        Brick7RopeModeling_AppAction_Type_NEW_ROPE_1,
        Brick7RopeModeling_AppAction_Type_REMOVE_BRICK,
        Brick7RopeModeling_AppAction_Type_REMOVE_ROPE,
        Brick7RopeModeling_AppAction_Type_DRAG_BRICK,
        Brick7RopeModeling_AppAction_Type_RUNNING
    } type;

    union
    {
        struct Brick7RopeModeling_AppAction_NewBrick
        {
            int x;
            int y;
        } new_brick;
        struct Brick7RopeModeling_AppAction_NewRope0
        {
            int x1;
            int y1;
        } new_rope_0;
        struct Brick7RopeModeling_AppAction_NewRope1
        {
            size_t brick_index;
            int x2;
            int y2;
        } new_rope_1;
        struct Brick7RopeModeling_AppAction_RemoveBrick
        {
            int x;
            int y;
        } remove_brick;
        struct Brick7RopeModeling_AppAction_RemoveRope
        {
            int x;
            int y;
        } remove_rope;
        struct Brick7RopeModeling_AppAction_BrickDrag
        {
            Brick7RopeModeling_Brick *ptr;
            int x;
            int y;
        } brick_drag;
    } value;
};

typedef struct Brick7RopeModeling_App
{
    /* Configuration */
    const unsigned short button_size;

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
    Brick7RopeModeling_Scene engine_out;
    CRITICAL_SECTION engine_mutex;

    CRITICAL_SECTION render_access_mutex;
    long double x;
    long double y;

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

    CRITICAL_SECTION action_mutex;
    struct Brick7RopeModeling_AppAction action;
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
