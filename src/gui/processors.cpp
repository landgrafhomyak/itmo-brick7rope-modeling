#include <new>

#include <windows.h>
#include "../app.h"
#include "processors.h"
#include "main_window_data.h"
#include "../objects/scene.hpp"

LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    auto *app = (Brick7RopeModeling_App  *) (GetWindowLongPtrW(hWnd, 0));
    switch (Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            EnterCriticalSection(&(app->main_window_data.mutex));
            if (app->main_window_data.bitmap != nullptr)
            {
                HDC hdc = GetDC(hWnd);

                BitBlt(hdc, 0, 0, app->main_window_data.width, app->main_window_data.height, app->main_window_data.hdc, 0, 0, SRCCOPY);

                ReleaseDC(hWnd, hdc);
            }
            LeaveCriticalSection(&(app->main_window_data.mutex));
            return 0;
        }
        case WM_SIZE:
        {
            EnterCriticalSection(&(app->main_window_data.mutex));

            if (app->main_window_data.bitmap_data == nullptr || app->main_window_data.width * app->main_window_data.height < LOWORD(lParam) * HIWORD(lParam))
            {
                if (app->main_window_data.bitmap_data != nullptr)
                {
                    LocalFree(app->main_window_data.bitmap_data);
                }
                app->main_window_data.bitmap_data = LocalAlloc(LMEM_FIXED, LOWORD(lParam) * HIWORD(lParam) * 4);
            }

            app->main_window_data.width = LOWORD(lParam);
            app->main_window_data.height = HIWORD(lParam);

            static BITMAPINFOHEADER bmih;
            bmih.biSize = sizeof(BITMAPINFOHEADER);
            bmih.biWidth = (LONG) (app->main_window_data.width);
            bmih.biHeight = -(LONG) (app->main_window_data.height);
            bmih.biPlanes = 1;
            bmih.biBitCount = 32;
            bmih.biCompression = BI_RGB;
            bmih.biSizeImage = app->main_window_data.width * 4 * app->main_window_data.height;

            if (app->main_window_data.bitmap != nullptr)
            { DeleteObject(app->main_window_data.bitmap); }
            app->main_window_data.bitmap = CreateDIBSection(nullptr, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, &(app->main_window_data.bitmap_data), nullptr, 0);
            SelectObject(app->main_window_data.hdc, app->main_window_data.bitmap);
            if (app->main_window_data.bitmap != nullptr)
            { DeleteObject(app->main_window_data.bitmap); }
            LeaveCriticalSection(&(app->main_window_data.mutex));
            return 0;
        }
        case WM_CREATE:
        {
            auto create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            HDC wind_hdc = GetDC(hWnd);
            app->main_window_data.hdc = CreateCompatibleDC(wind_hdc);
            ReleaseDC(hWnd, wind_hdc);
            app->main_window_data.bitmap = nullptr;
            app->main_window_data.bitmap_data = nullptr;
            app->main_window_data.scene = LocalAlloc(LMEM_FIXED, sizeof(Scene));
            new (app->main_window_data.scene) Scene;
            InitializeCriticalSection(&(app->main_window_data.mutex));
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
    auto *app = (Brick7RopeModeling_App  *) (GetWindowLongPtrW(hWnd, 0));

    switch (Msg)
    {
        case WM_COMMAND:
            if ((HWND)lParam == app->tool_panel_stuff_windows.add_brick)
            {
                ((Scene *)(app->main_window_data.scene)).
            }
            return 0;
        case WM_CREATE:
        {
            auto create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            HDC wind_hdc = GetDC(hWnd);
            app->main_window_data.hdc = CreateCompatibleDC(wind_hdc);
            ReleaseDC(hWnd, wind_hdc);
            app->main_window_data.bitmap = nullptr;
            app->main_window_data.bitmap_data = nullptr;
            app->main_window_data.scene = LocalAlloc(LMEM_FIXED, sizeof(Scene));
            new (app->main_window_data.scene) Scene;
            InitializeCriticalSection(&(app->main_window_data.mutex));
            return 0;
        }
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }
}
