#include <stdio.h>

#include <windows.h>

#include "processors.h"
#include "main_window_data.h"


LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    auto *window_data = (Brick7RopeModeling_GUI_MainWindow_Data *) (GetWindowLongPtrW(hWnd, 0));
    switch (Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            EnterCriticalSection(&(window_data->mutex));
            if (window_data->bitmap == nullptr)
            { goto END_PAINTING; }
            {
                HDC hdc = BeginPaint(hWnd, &ps);
                HBITMAP bmp = CreateBitmap(window_data->width, window_data->height, 1, 8, window_data->bitmap);
                HDC tmp_hdc = CreateCompatibleDC(hdc);
                HGDIOBJ old_bmp = SelectObject(tmp_hdc, bmp);

                BitBlt(hdc, 0, 0, window_data->width, window_data->height, tmp_hdc, 0, 0, SRCCOPY);
                SelectObject(tmp_hdc, old_bmp);
                DeleteDC(tmp_hdc);
                DeleteObject(bmp);

                EndPaint(hWnd, &ps);
            }
            END_PAINTING:
            LeaveCriticalSection(&(window_data->mutex));
            return 0;
        }
        case WM_SIZE:
            EnterCriticalSection(&(window_data->mutex));
            LeaveCriticalSection(&(window_data->mutex));
            break;
        case WM_CREATE:
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (window_data = (Brick7RopeModeling_GUI_MainWindow_Data *) ((CREATESTRUCTW *) (lParam))->lpCreateParams));
            window_data->bitmap = nullptr;
            InitializeCriticalSection(&(window_data->mutex));
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
    return DefWindowProcW(hWnd, Msg, wParam, lParam);
}

LRESULT Brick7RopeModeling_ToolPanel_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {}

    return DefWindowProcW(hWnd, Msg, wParam, lParam);
}
