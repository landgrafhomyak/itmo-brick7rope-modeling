#include <windows.h>
#include "../app.h"
#include "processors.h"
#include "../threads.h"

void Brick7RopeModeling_ToolPanel_SetButtonsState(Brick7RopeModeling_App *app)
{
    enum Brick7RopeModeling_AppAction_Type type = app->action.type;

    switch (type)
    {
        case Brick7RopeModeling_AppAction_Type_VOID:
            EnableWindow(app->tool_panel_stuff_windows.cancel, FALSE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
            EnableWindow(app->tool_panel_stuff_windows.cancel, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.pause, FALSE);
            break;
        case Brick7RopeModeling_AppAction_Type_RUNNING:
            EnableWindow(app->tool_panel_stuff_windows.cancel, FALSE);
            EnableWindow(app->tool_panel_stuff_windows.reset, TRUE);
            EnableWindow(app->tool_panel_stuff_windows.resume, FALSE);
            EnableWindow(app->tool_panel_stuff_windows.pause, TRUE);
            break;
    }
}


LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    Brick7RopeModeling_App *app = (Brick7RopeModeling_App *) (GetWindowLongPtrW(hWnd, 0));
    switch (Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
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
            EnterCriticalSection(&(app->action_mutex));
            switch (app->action.type)
            {
                case Brick7RopeModeling_AppAction_Type_VOID:
                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    app->action.value.new_brick.x = LOWORD(lParam);
                    app->action.value.new_brick.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    app->action.value.new_rope_0.x1 = LOWORD(lParam);
                    app->action.value.new_rope_0.y1 = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    app->action.value.new_rope_1.x2 = LOWORD(lParam);
                    app->action.value.new_rope_1.y2 = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    app->action.value.remove_brick.x = LOWORD(lParam);
                    app->action.value.remove_brick.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    app->action.value.remove_rope.x = LOWORD(lParam);
                    app->action.value.remove_rope.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                    app->action.value.brick_drag.x = LOWORD(lParam);
                    app->action.value.brick_drag.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_RUNNING:
                    break;
            }
            LeaveCriticalSection(&(app->action_mutex));
            return 0;
        case WM_LBUTTONUP:
            EnterCriticalSection(&(app->action_mutex));
            switch (app->action.type)
            {
                case Brick7RopeModeling_AppAction_Type_VOID:
                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    Brick7RopeModeling_Stack_Add(&(app->stack));
                    Brick7RopeModeling_Scene_AddBrick(
                            Brick7RopeModeling_Stack_GetCurrent(&(app->stack)),
                            (Brick7RopeModeling_Brick) {
                                    .x = app->action.value.new_brick.x,
                                    .y = app->action.value.new_brick.y,
                                    .is_locked = FALSE
                            }
                    );

                    EnterCriticalSection(&(app->engine_mutex));
                    Brick7RopeModeling_Scene_Finalize(&(app->engine_out));
                    Brick7RopeModeling_Scene_Copy(Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), &(app->engine_out));
                    LeaveCriticalSection(&(app->engine_mutex));

                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    app->action.value.new_rope_0.x1 = LOWORD(lParam);
                    app->action.value.new_rope_0.y1 = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    app->action.value.new_rope_1.x2 = LOWORD(lParam);
                    app->action.value.new_rope_1.y2 = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    app->action.value.remove_brick.x = LOWORD(lParam);
                    app->action.value.remove_brick.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    app->action.value.remove_rope.x = LOWORD(lParam);
                    app->action.value.remove_rope.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                    app->action.value.brick_drag.x = LOWORD(lParam);
                    app->action.value.brick_drag.y = HIWORD(lParam);
                    break;
                case Brick7RopeModeling_AppAction_Type_RUNNING:
                    break;
            }
            LeaveCriticalSection(&(app->action_mutex));
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
            InitializeCriticalSection(&(app->action_mutex));

            Brick7RopeModeling_SceneArena_Init(&(app->scene_arena), GetProcessHeap());
            Brick7RopeModeling_Stack_Init(&(app->stack));
            Brick7RopeModeling_SceneArena_LinkScene(&(app->scene_arena), Brick7RopeModeling_Stack_GetCurrent(&(app->stack)), 1, 1);
            Brick7RopeModeling_Scene_Init(&(app->engine_out));


            app->engine_thread = CreateThread(NULL, 0, Brick7RopeModeling_EngineThreadMain, app, 0, NULL);
            app->render_thread = CreateThread(NULL, 0, Brick7RopeModeling_RenderThreadMain, app, 0, NULL);

            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }

}

LRESULT Brick7RopeModeling_ToolPanel_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    Brick7RopeModeling_App *app = (Brick7RopeModeling_App *) (GetWindowLongPtrW(hWnd, 0));

    switch (Msg)
    {
        case WM_COMMAND:
            if ((HWND) lParam == app->tool_panel_stuff_windows.cancel)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {
                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_VOID;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.reset)
            {

                // todo
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.resume)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {

                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_RUNNING;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.pause)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {

                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        app->action.type = Brick7RopeModeling_AppAction_Type_VOID;
                        break;
                }
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.add_brick)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {

                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_NEW_BRICK;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                app->action.value.new_brick = (struct Brick7RopeModeling_AppAction_NewBrick) {.x = 0, .y=0};
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.remove_brick)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {
                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_REMOVE_BRICK;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                app->action.value.remove_brick = (struct Brick7RopeModeling_AppAction_RemoveBrick) {.x = 0, .y = 0};
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.add_rope)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {
                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_NEW_ROPE_0;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                app->action.value.new_rope_0 = (struct Brick7RopeModeling_AppAction_NewRope0) {.x1 = 0, .y1 = 0};
                LeaveCriticalSection(&(app->action_mutex));
            }
            else if ((HWND) lParam == app->tool_panel_stuff_windows.remove_rope)
            {
                EnterCriticalSection(&(app->action_mutex));
                switch (app->action.type)
                {
                    case Brick7RopeModeling_AppAction_Type_VOID:
                    case Brick7RopeModeling_AppAction_Type_NEW_BRICK:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_0:
                    case Brick7RopeModeling_AppAction_Type_NEW_ROPE_1:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_BRICK:
                    case Brick7RopeModeling_AppAction_Type_REMOVE_ROPE:
                    case Brick7RopeModeling_AppAction_Type_DRAG_BRICK:
                        app->action.type = Brick7RopeModeling_AppAction_Type_REMOVE_ROPE;
                        break;
                    case Brick7RopeModeling_AppAction_Type_RUNNING:
                        break;
                }
                app->action.value.remove_rope = (struct Brick7RopeModeling_AppAction_RemoveRope) {.x = 0, .y = 0};
                LeaveCriticalSection(&(app->action_mutex));
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


