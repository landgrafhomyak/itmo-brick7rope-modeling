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
            if (window_data->bitmap != nullptr)
            {
                HDC hdc = GetDC(hWnd);

                BitBlt(hdc, 0, 0, window_data->width, window_data->height, window_data->hdc, 0, 0, SRCCOPY);

                ReleaseDC(hWnd, hdc);
            }
            LeaveCriticalSection(&(window_data->mutex));
            return 0;
        }
        case WM_SIZE:
        {
            EnterCriticalSection(&(window_data->mutex));

            if (window_data->bitmap_data == nullptr || window_data->width * window_data->height < LOWORD(lParam) * HIWORD(lParam))
            {
                if (window_data->bitmap_data != nullptr)
                {
                    LocalFree(window_data->bitmap_data);
                }
                window_data->bitmap_data = LocalAlloc(LMEM_FIXED, LOWORD(lParam) * HIWORD(lParam) * 4);
            }

            window_data->width = LOWORD(lParam);
            window_data->height = HIWORD(lParam);

            static BITMAPINFOHEADER bmih;
            bmih.biSize = sizeof(BITMAPINFOHEADER);
            bmih.biWidth = (LONG) (window_data->width);
            bmih.biHeight = -(LONG) (window_data->height);
            bmih.biPlanes = 1;
            bmih.biBitCount = 32;
            bmih.biCompression = BI_RGB;
            bmih.biSizeImage = window_data->width * 4 * window_data->height;



            if (window_data->bitmap != nullptr)
            { DeleteObject(window_data->bitmap); }
            window_data->bitmap = CreateDIBSection(nullptr, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, &(window_data->bitmap_data), nullptr, 0);
            SelectObject(window_data->hdc, window_data->bitmap);
            if (window_data->bitmap != nullptr)
            { DeleteObject(window_data->bitmap); }
            LeaveCriticalSection(&(window_data->mutex));
            break;
        }
        case WM_CREATE:
        {
            auto create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (window_data = (Brick7RopeModeling_GUI_MainWindow_Data *) (create_struct->lpCreateParams)));
            HDC wind_hdc = GetDC(hWnd);
            window_data->hdc = CreateCompatibleDC(wind_hdc);
            ReleaseDC(hWnd, wind_hdc);
            window_data->bitmap = nullptr;
            window_data->bitmap_data = nullptr;
            InitializeCriticalSection(&(window_data->mutex));
            break;
        }
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
