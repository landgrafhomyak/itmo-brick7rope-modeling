#include <windows.h>
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
                case Brick7RopeModeling_AppState_ActionType_ADD_BRICK:
                    app->state.action_value.add_brick.x = LOWORD(lParam);
                    app->state.action_value.add_brick.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0:
                    break;
                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1:
                    break;
                case Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
                    break;
                default:
                    break;
            }
            LeaveCriticalSection(&(app->state.mutex));
            return 0;
        case WM_LBUTTONUP:
            EnterCriticalSection(&(app->state.mutex));
            switch (app->state.action_type)
            {
                case Brick7RopeModeling_AppState_ActionType_ADD_BRICK:
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Scene_AddBrick(
                            Brick7RopeModeling_Stack_GetCurrent(&(app->stack)),
                            (Brick7RopeModeling_Brick) {
                                    .x = app->state.action_value.add_brick.x,
                                    .y = app->state.action_value.add_brick.y,
                            }
                    );
                    Brick7RopeModeling_UpdateEngineWithCurrentStack(app);

                    break;
                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0:
                    break;
                case Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1:
                    break;
                case Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
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
            {}
            elifButton(select_rope)
            {}
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
            {}
            elifButton(add_rope)
            {}
            elifButton(remove_rope)
            {}

            elifButton(lock_brick)
            {}

            elifButton(unlock_brick)
            {}

            elifButton(drag_brick)
            {}

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


