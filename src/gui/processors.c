#include <float.h>
#include <math.h>

#include <windows.h>

#include "../common.h"
#include "../app.h"
#include "processors.h"
#include "../threads.h"

static void Brick7RopeModeling_UpdateEngineWithCurrentStack(Brick7RopeModeling_App *app)
{
    EnterCriticalSection(&(app->engine_mutex));
    Brick7RopeModeling_Scene_Copy(Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), &(app->engine_out));
    LeaveCriticalSection(&(app->engine_mutex));
}

static void Brick7RopeModeling_GetClientMousePos(HWND hWnd, int *x, int *y)
{
    POINT p;
    GetCursorPos(&p);
    if (ScreenToClient(hWnd, &p))
    { *x = 0, *y = 0; }
    else
    { *x = p.x, *y = p.y; }
}

static size_t Brick7RopeModeling_GetClosestRope(Brick7RopeModeling_App *app, int x, int y)
{
    size_t index;
    Brick7RopeModeling_Scene *scene = Brick7RopeModeling_Stack_GetCurrent(&(app->stack));

    size_t closest_index;
    long double distance;
    long double closest_distance = LDBL_MAX;

    for (index = 0; index < scene->ropes_count; index++)
    {
        distance = (scene->bricks[scene->ropes[index].brick1_index].x - x) * (scene->bricks[scene->ropes[index].brick2_index].y - y) - (scene->bricks[scene->ropes[index].brick1_index].y - y) * (scene->bricks[scene->ropes[index].brick2_index].x - x);
        if (distance < 0)
        { distance = -distance; }
        distance /= hypotl(scene->bricks[scene->ropes[index].brick1_index].x - scene->bricks[scene->ropes[index].brick2_index].x, scene->bricks[scene->ropes[index].brick1_index].y - scene->bricks[scene->ropes[index].brick2_index].y);

        if (distance < closest_distance)
        {
            closest_index = index;
            closest_distance = distance;
        }
    }

    return closest_distance <= 10 ? closest_index : Brick7RopeModeling_INVALID_INDEX;
}

static size_t Brick7RopeModeling_GetClosestBrick(Brick7RopeModeling_App *app, int x, int y)
{
    signed long long index;
    Brick7RopeModeling_Scene *scene = Brick7RopeModeling_Stack_GetCurrent(&(app->stack));

    for (index = scene->bricks_count - 1; index >= 0; index--)
    {
        if (hypotl(scene->bricks[index].x - x, scene->bricks[index].y - y) <= app->brick_size)
        { return index; }
    }

    return Brick7RopeModeling_INVALID_INDEX;
}

static void Brick7RopeModeling_ToolPanel_Clear(Brick7RopeModeling_App *app);

static void Brick7RopeModeling_ToolPanel_CancelAction(Brick7RopeModeling_App *app);

LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    Brick7RopeModeling_App *app = (Brick7RopeModeling_App *) (GetWindowLongPtrW(hWnd, 0));
    switch (Msg)
    {
        case WM_PAINT:
        {
            EnterCriticalSection(&(app->render_access_mutex));
            if (app->render_accessories.hdc != NULL)
            {
                HDC hdc = GetDC(hWnd);

                BitBlt(hdc, 0, 0, app->render_accessories.width, app->render_accessories.height, app->render_accessories.hdc, 0, 0, SRCCOPY);

                ReleaseDC(hWnd, hdc);
            }
            LeaveCriticalSection(&(app->render_access_mutex));
            return 0;
        }
        case WM_MOUSEMOVE:
            EnterCriticalSection(&(app->state.mutex));
            switch (app->state.action_type)
            {
                case Brick7RopeModeling_AppState_ActionType_SELECT_BRICK:
                    app->state.action_value.select_brick.brick_index = Brick7RopeModeling_GetClosestBrick(app, LOWORD(lParam), HIWORD(lParam));
                    break;

                case Brick7RopeModeling_AppState_ActionType_SELECT_ROPE:
                    app->state.action_value.select_rope.rope_index = Brick7RopeModeling_GetClosestRope(app, LOWORD(lParam), HIWORD(lParam));
                    break;

                case Brick7RopeModeling_AppState_ActionType_ADD_BRICK:
                    app->state.action_value.add_brick.x = LOWORD(lParam);
                    app->state.action_value.add_brick.y = HIWORD(lParam);
                    break;

                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0:
                    app->state.action_value.add_rope_0.brick1_index = Brick7RopeModeling_GetClosestBrick(app, LOWORD(lParam), HIWORD(lParam));
                    break;

                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1:
                    app->state.action_value.add_rope_1.brick2_index = Brick7RopeModeling_GetClosestBrick(app, LOWORD(lParam), HIWORD(lParam));
                    app->state.action_value.add_rope_1.x2 = LOWORD(lParam);
                    app->state.action_value.add_rope_1.y2 = HIWORD(lParam);
                    break;

                case Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
                    if (!app->state.action_value.drag_brick.hold)
                    { app->state.action_value.drag_brick.brick_index = Brick7RopeModeling_GetClosestBrick(app, LOWORD(lParam), HIWORD(lParam)); }
                    app->state.action_value.drag_brick.x = LOWORD(lParam);
                    app->state.action_value.drag_brick.y = HIWORD(lParam);
                    break;

                default:
                    break;
            }
            LeaveCriticalSection(&(app->state.mutex));
            return 0;

        case WM_LBUTTONDOWN:
            EnterCriticalSection(&(app->state.mutex));
            switch (app->state.action_type)
            {
                case Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
                {
                    app->state.action_value.drag_brick.brick_index = Brick7RopeModeling_GetClosestBrick(app, app->state.action_value.drag_brick.x, app->state.action_value.drag_brick.y);
                    if (app->state.action_value.drag_brick.brick_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        app->state.action_value.drag_brick.hold = TRUE;
                        app->state.action_value.drag_brick.ox = ((INT) Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.action_value.drag_brick.brick_index].x) - app->state.action_value.drag_brick.x;
                        app->state.action_value.drag_brick.oy = ((INT) Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.action_value.drag_brick.brick_index].y) - app->state.action_value.drag_brick.y;
                    }
                    break;
                }

                default:
                    break;
            }
            LeaveCriticalSection(&(app->state.mutex));
            return 0;

        case WM_LBUTTONUP:
            EnterCriticalSection(&(app->state.mutex));
            switch (app->state.action_type)
            {
                case Brick7RopeModeling_AppState_ActionType_SELECT_BRICK:
                    if (app->state.action_value.select_brick.brick_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        app->state.selection_type = Brick7RopeModeling_AppState_SelectionType_BRICK;
                        app->state.selection_value.brick.brick_index = app->state.action_value.select_brick.brick_index;
                        app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    }
                    break;

                case Brick7RopeModeling_AppState_ActionType_SELECT_ROPE:
                    if (app->state.action_value.select_rope.rope_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        app->state.selection_type = Brick7RopeModeling_AppState_SelectionType_ROPE;
                        app->state.selection_value.rope.rope_index = app->state.action_value.select_rope.rope_index;
                        app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    }
                    break;

                case Brick7RopeModeling_AppState_ActionType_ADD_BRICK:
                {
                    Brick7RopeModeling_Brick brick;
                    Brick7RopeModeling_Brick_Init(&brick);
                    brick.x = app->state.action_value.add_brick.x;
                    brick.y = app->state.action_value.add_brick.y;

                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Scene_AddBrick(
                            Brick7RopeModeling_Stack_GetCurrent(&(app->stack)),
                            brick

                    );
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                    break;
                }

                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0:
                    if (app->state.action_value.add_rope_0.brick1_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        size_t brick1_index = app->state.action_value.add_rope_0.brick1_index;
                        app->state.action_type = Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1;
                        app->state.action_value.add_rope_1.brick1_index = brick1_index;
                        Brick7RopeModeling_GetClientMousePos(hWnd, &(app->state.action_value.add_rope_1.x2), &(app->state.action_value.add_rope_1.y2));
                        app->state.action_value.add_rope_1.brick2_index = Brick7RopeModeling_GetClosestBrick(app, app->state.action_value.add_rope_1.x2, app->state.action_value.add_rope_1.y2);
                    }
                    break;

                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1:
                    if (app->state.action_value.add_rope_1.brick2_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        Brick7RopeModeling_Rope rope;
                        Brick7RopeModeling_Rope_Init(&rope);
                        rope.brick1_index = app->state.action_value.add_rope_1.brick1_index;
                        rope.brick2_index = app->state.action_value.add_rope_1.brick2_index;

                        Brick7RopeModeling_Stack_Add(&(app->stack));
                        Brick7RopeModeling_Scene_AddRope(
                                Brick7RopeModeling_Stack_GetCurrent(&(app->stack)),
                                rope
                        );
                        Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                        app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    }
                    break;

                case Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
                    if (app->state.action_value.drag_brick.brick_index != Brick7RopeModeling_INVALID_INDEX)
                    {
                        Brick7RopeModeling_Stack_Add(&(app->stack));
                        Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.action_value.drag_brick.brick_index].x = app->state.action_value.drag_brick.x + app->state.action_value.drag_brick.ox;
                        Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.action_value.drag_brick.brick_index].y = app->state.action_value.drag_brick.y + app->state.action_value.drag_brick.oy;
                        Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                        app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    }
                    break;

                default:
                    break;
            }
            LeaveCriticalSection(&(app->state.mutex));
            return 0;

        case WM_SIZE:
            EnterCriticalSection(&(app->render_access_mutex));
            app->main_window_width = LOWORD(lParam);
            app->main_window_height = HIWORD(lParam);
            LeaveCriticalSection(&(app->render_access_mutex));
            return 0;
        case WM_CREATE:
        {
            CREATESTRUCTW *create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            HDC wind_hdc = GetDC(hWnd);
            app->render_accessories.hdc = CreateCompatibleDC(wind_hdc);
            ReleaseDC(hWnd, wind_hdc);

            app->render_accessories.width = 0;
            app->render_accessories.height = 0;

            app->render_accessories.bitmap1 = NULL;
            app->render_accessories.bitmap1_data = NULL;
            app->render_accessories.bitmap2 = NULL;
            app->render_accessories.bitmap2_data = NULL;

            InitializeCriticalSection(&(app->engine_state));
            InitializeCriticalSection(&(app->engine_mutex));
            InitializeCriticalSection(&(app->render_access_mutex));
            InitializeCriticalSection(&(app->state.mutex));

            Brick7RopeModeling_SceneArena_Init(&(app->scene_arena), GetProcessHeap());
            Brick7RopeModeling_Stack_Init(&(app->stack));
            Brick7RopeModeling_ToolPanel_Clear(app);
            Brick7RopeModeling_ToolPanel_CancelAction(app);
            EnterCriticalSection(&(app->engine_state));

            app->engine_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Brick7RopeModeling_EngineThreadMain, app, 0, NULL);
            app->render_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Brick7RopeModeling_RenderThreadMain, app, 0, NULL);

            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }

}


static void Brick7RopeModeling_ToolPanel_Clear(Brick7RopeModeling_App *app)
{
    Brick7RopeModeling_SceneArena_LinkScene(&(app->scene_arena), Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), 1, 1);
    Brick7RopeModeling_Scene_Init(&(app->engine_out));
}

static void Brick7RopeModeling_ToolPanel_CancelSelection(Brick7RopeModeling_App *app)
{
    EnterCriticalSection(&(app->state.mutex));
    app->state.selection_type = Brick7RopeModeling_AppState_SelectionType_NONE;
    LeaveCriticalSection(&(app->state.mutex));
}

static void Brick7RopeModeling_ToolPanel_CancelAction(Brick7RopeModeling_App *app)
{
    EnterCriticalSection(&(app->state.mutex));
    app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
    LeaveCriticalSection(&(app->state.mutex));
}


#define ifButton(FIELD) if ((HWND) lParam == app->tool_panel_stuff_windows.FIELD)
#define elifButton(FIELD) else ifButton(FIELD)

LRESULT Brick7RopeModeling_ToolPanel_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    Brick7RopeModeling_App *app = (Brick7RopeModeling_App *) (GetWindowLongPtrW(hWnd, 0));

    switch (Msg)
    {
        case WM_COMMAND:
            ifButton(save_capture)
            {}
            elifButton(save_capture_as)
            {}
            elifButton(load_capture)
            {}
            elifButton(reset)
            {
                Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
            }
            elifButton(resume)
            {
                app->engine_last_tick = Brick7RopeModeling_GetTicks();
                LeaveCriticalSection(&(app->engine_state));
            }
            elifButton(pause)
            {
                EnterCriticalSection(&(app->engine_state));
            }
            elifButton(undo)
            {
                Brick7RopeModeling_Stack_Undo(&(app->stack));
                Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                EnableWindow(app->tool_panel_stuff_windows.undo, Brick7RopeModeling_Stack_CanUndo(&(app->stack)));
                EnableWindow(app->tool_panel_stuff_windows.redo, Brick7RopeModeling_Stack_CanRedo(&(app->stack)));
            }
            elifButton(redo)
            {
                Brick7RopeModeling_Stack_Redo(&(app->stack));
                Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                EnableWindow(app->tool_panel_stuff_windows.undo, Brick7RopeModeling_Stack_CanUndo(&(app->stack)));
                EnableWindow(app->tool_panel_stuff_windows.redo, Brick7RopeModeling_Stack_CanRedo(&(app->stack)));
            }
            elifButton(clear)
            {
                if (Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks_count > 0)
                {
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_ToolPanel_CancelSelection(app);
                    Brick7RopeModeling_ToolPanel_Clear(app);
                }
            }
            elifButton(cancel_selection)
            {
                Brick7RopeModeling_ToolPanel_CancelSelection(app);
            }
            elifButton(select_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                app->state.action_type = Brick7RopeModeling_AppState_ActionType_SELECT_BRICK;
                int x, y;
                Brick7RopeModeling_GetClientMousePos(hWnd, &x, &y);
                app->state.action_value.select_brick.brick_index = Brick7RopeModeling_GetClosestBrick(app, x, y);
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(select_rope)
            {
                EnterCriticalSection(&(app->state.mutex));
                app->state.action_type = Brick7RopeModeling_AppState_ActionType_SELECT_ROPE;
                int x, y;
                Brick7RopeModeling_GetClientMousePos(hWnd, &x, &y);
                app->state.action_value.select_rope.rope_index = Brick7RopeModeling_GetClosestRope(app, x, y);
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(cancel_action)
            {
                Brick7RopeModeling_ToolPanel_CancelAction(app);
            }
            elifButton(add_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                app->state.action_type = Brick7RopeModeling_AppState_ActionType_ADD_BRICK;
                Brick7RopeModeling_GetClientMousePos(hWnd, &(app->state.action_value.add_brick.x), &(app->state.action_value.add_brick.y));
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(remove_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                if (app->state.selection_type == Brick7RopeModeling_AppState_SelectionType_BRICK)
                {
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Scene_RemoveBrick(Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), app->state.selection_value.brick.brick_index);
                    app->state.selection_type = Brick7RopeModeling_AppState_SelectionType_NONE;
                    app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                }
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(add_rope)
            {
                EnterCriticalSection(&(app->state.mutex));
                if (app->state.selection_type == Brick7RopeModeling_AppState_SelectionType_BRICK)
                {
                    app->state.action_type = Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1;
                    app->state.action_value.add_rope_1.brick1_index = app->state.selection_value.brick.brick_index;
                    Brick7RopeModeling_GetClientMousePos(hWnd, &(app->state.action_value.add_rope_1.x2), &(app->state.action_value.add_rope_1.y2));
                    app->state.action_value.add_rope_1.brick2_index = Brick7RopeModeling_GetClosestBrick(app, app->state.action_value.add_rope_1.x2, app->state.action_value.add_rope_1.y2);
                }
                else
                {
                    app->state.action_type = Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0;
                    app->state.action_value.add_rope_1.brick1_index = Brick7RopeModeling_INVALID_INDEX;
                    int x, y;
                    Brick7RopeModeling_GetClientMousePos(hWnd, &x, &y);
                    app->state.action_value.add_rope_0.brick1_index = Brick7RopeModeling_GetClosestBrick(app, x, y);
                }
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(remove_rope)
            {
                EnterCriticalSection(&(app->state.mutex));
                if (app->state.selection_type == Brick7RopeModeling_AppState_SelectionType_ROPE)
                {
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Scene_RemoveRope(Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), app->state.selection_value.rope.rope_index);
                    app->state.selection_type = Brick7RopeModeling_AppState_SelectionType_NONE;
                    app->state.action_type = Brick7RopeModeling_AppState_ActionType_VOID;
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                }
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(lock_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                if (app->state.selection_type == Brick7RopeModeling_AppState_SelectionType_BRICK)
                {
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.selection_value.brick.brick_index].is_locked = TRUE;
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                }
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(unlock_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                if (app->state.selection_type == Brick7RopeModeling_AppState_SelectionType_BRICK)
                {
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Stack_GetCurrent(&(app->stack))->bricks[app->state.selection_value.brick.brick_index].is_locked = FALSE;
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);
                }
                LeaveCriticalSection(&(app->state.mutex));
            }
            elifButton(drag_brick)
            {
                EnterCriticalSection(&(app->state.mutex));
                app->state.action_type = Brick7RopeModeling_AppState_ActionType_DRAG_BRICK;
                Brick7RopeModeling_GetClientMousePos(hWnd, &(app->state.action_value.drag_brick.x), &(app->state.action_value.drag_brick.y));
                app->state.action_value.drag_brick.brick_index = Brick7RopeModeling_GetClosestBrick(app, app->state.action_value.drag_brick.x, app->state.action_value.drag_brick.y);
                app->state.action_value.drag_brick.hold = FALSE;
                LeaveCriticalSection(&(app->state.mutex));
            }

            return 0;
        case WM_CREATE:
        {
            CREATESTRUCTW *create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            return 0;
        }
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }
}


