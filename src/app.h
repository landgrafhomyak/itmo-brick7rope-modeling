#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>
# include "objects/brick.h"
# include "objects/rope.h"
# include "objects/scene_arena.h"
# include "objects/stack.h"

# ifdef __cplusplus
extern "C" {
# endif

struct Brick7RopeModeling_AppState
{
    CRITICAL_SECTION mutex;

    enum Brick7RopeModeling_AppState_SelectionType
    {
        Brick7RopeModeling_AppState_SelectionType_NONE,
        Brick7RopeModeling_AppState_SelectionType_BRICK,
        Brick7RopeModeling_AppState_SelectionType_ROPE,
    } selection_type;

    union
    {
        struct Brick7RopeModeling_AppState_Selection_Brick
        {
            size_t brick_index;
        } brick;

        struct Brick7RopeModeling_AppState_Selection_Rope
        {
            size_t rope_index;
        } rope;
    } selection_value;

    enum Brick7RopeModeling_AppState_ActionType
    {
        Brick7RopeModeling_AppState_ActionType_VOID,
        Brick7RopeModeling_AppState_ActionType_SELECT_BRICK,
        Brick7RopeModeling_AppState_ActionType_SELECT_ROPE,
        Brick7RopeModeling_AppState_ActionType_ADD_BRICK,
        Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0,
        Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1,
        Brick7RopeModeling_AppState_ActionType_DRAG_BRICK,
    } action_type;

    union
    {
        struct Brick7RopeModeling_AppState_Action_SelectBrick
        {
            size_t brick_index;
        } select_brick;
        struct Brick7RopeModeling_AppState_Action_SelectRope
        {
            size_t rope_index;
        } select_rope;
        struct Brick7RopeModeling_AppState_Action_AddBrick
        {
            int x;
            int y;
        } add_brick;
        struct Brick7RopeModeling_AppState_Action_AddRope0
        {
            size_t brick1_index;
        } add_rope_0;
        struct Brick7RopeModeling_AppState_Action_AddRope1
        {
            size_t brick1_index;
            size_t brick2_index;
            int x2;
            int y2;
        } add_rope_1;
        struct Brick7RopeModeling_AppState_Action_DragBrick
        {
            size_t brick_index;
            int x;
            int y;
            int ox;
            int oy;
            BOOL hold;
        } drag_brick;
    } action_value;

};

typedef struct Brick7RopeModeling_App
{
    /* Configuration */
    const unsigned short button_size;
    const unsigned short brick_size;

    /* Predefined handlers */
    HINSTANCE hInstance;

    /* Resources */
    HICON main_icon;
    HCURSOR canvas_cursor;
    struct
    {
        HICON save_capture;
        HICON save_capture_as;
        HICON load_capture;
        HICON reset;
        HICON resume;
        HICON pause;
        HICON undo;
        HICON redo;
        HICON clear;
        HICON cancel_selection;
        HICON select_brick;
        HICON select_rope;
        HICON cancel_action;
        HICON add_brick;
        HICON remove_brick;
        HICON add_rope;
        HICON remove_rope;
        HICON lock_brick;
        HICON unlock_brick;
        HICON drag_brick;
    } button_icons;

    /* Window classes */
    ATOM main_window_class;
    ATOM tool_panel_window_class;

    /* Window instances */
    HWND main_window;
    HWND tool_panel_window;
    struct
    {
        HWND save_capture;
        HWND save_capture_as;
        HWND load_capture;
        HWND reset;
        HWND resume;
        HWND pause;
        HWND undo;
        HWND redo;
        HWND clear;
        HWND cancel_selection;
        HWND select_brick;
        HWND select_rope;
        HWND cancel_action;
        HWND add_brick;
        HWND remove_brick;
        HWND add_rope;
        HWND remove_rope;
        HWND lock_brick;
        HWND unlock_brick;
        HWND drag_brick;
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

    struct Brick7RopeModeling_AppState state;
} Brick7RopeModeling_App;

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app);

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_RegisterWindowClasses(Brick7RopeModeling_App *app);

void Brick7RopeModeling_UnRegisterWindowClasses(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_CreateAndShowWindows(Brick7RopeModeling_App *app);

# ifdef __cplusplus
}
# endif

#endif /* Brick7RopeModeling_APP_H */
