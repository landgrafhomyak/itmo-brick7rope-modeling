#include <new>

#include <windows.h>
#include "../app.h"
#include "processors.h"
#include "main_window_data.h"

LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    auto *app = (Brick7RopeModeling_App  *) (GetWindowLongPtrW(hWnd, 0));
    switch (Msg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            EnterCriticalSection(&(app->render_access_mutex));
            if (app->render_accessories.hdc != nullptr)
            {
                HDC hdc = GetDC(hWnd);

                BitBlt(hdc, 0, 0, app->render_accessories.width, app->render_accessories.height, app->render_accessories.hdc, 0, 0, SRCCOPY);

                ReleaseDC(hWnd, hdc);
            }
            LeaveCriticalSection(&(app->render_access_mutex));
            return 0;
        }
        case WM_SIZE:
            app->main_window_width = LOWORD(lParam);
            app->main_window_height = HIWORD(lParam);
            return 0;
#if 0
        {
            EnterCriticalSection(&(app->render_access_mutex));

            if (app->main_window_width * app->main_window_height < LOWORD(lParam) * HIWORD(lParam))
            {
                if (app->render_accessories.bitmap1 != nullptr)
                { DeleteObject(app->render_accessories.bitmap1); }

                if (app->render_accessories.bitmap2 != nullptr)
                { DeleteObject(app->render_accessories.bitmap2); }
            }

            if (app->main_window_data.bitmap_data == nullptr || )
            {
                if (app->main_window_data.bitmap_data != nullptr)
                {
                    LocalFree(app->main_window_data.bitmap_data);
                }
                app->main_window_data.bitmap_data = LocalAlloc(LMEM_FIXED, LOWORD(lParam) * HIWORD(lParam) * 4);
            }



            static BITMAPINFOHEADER bmih;
            bmih.biSize = sizeof(BITMAPINFOHEADER);
            bmih.biWidth = (LONG) (app->main_window_width);
            bmih.biHeight = -(LONG) (app->main_window_height);
            bmih.biPlanes = 1;
            bmih.biBitCount = 32;
            bmih.biCompression = BI_RGB;
            bmih.biSizeImage = app->main_window_width * app->main_window_height * 4;

            if (app->main_window_data.bitmap != nullptr)
            { DeleteObject(app->main_window_data.bitmap); }
            app->main_window_data.bitmap = CreateDIBSection(nullptr, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, &(app->main_window_data.bitmap_data), nullptr, 0);
            SelectObject(app->main_window_data.hdc, app->main_window_data.bitmap);
            if (app->main_window_data.bitmap != nullptr)
            { DeleteObject(app->main_window_data.bitmap); }
            LeaveCriticalSection(&(app->main_window_data.mutex));
            return 0;
        }
#endif
        case WM_CREATE:
        {
            auto create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            HDC wind_hdc = GetDC(hWnd);
            app->render_accessories.hdc = CreateCompatibleDC(wind_hdc);
            ReleaseDC(hWnd, wind_hdc);

            app->render_accessories.width = 0;
            app->render_accessories.height = 0;

            app->render_accessories.bitmap1 = nullptr;
            app->render_accessories.bitmap1_data = nullptr;
            app->render_accessories.bitmap2 = nullptr;
            app->render_accessories.bitmap2_data = nullptr;

            InitializeCriticalSection(&(app->engine_state));
            InitializeCriticalSection(&(app->render_access_mutex));
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
                //((Scene *)(app->main_window_data.scene)).
            }
            return 0;
        case WM_CREATE:
        {
            auto create_struct = (CREATESTRUCTW *) lParam;
            SetWindowLongPtrW(hWnd, 0, (LONG_PTR) (app = (Brick7RopeModeling_App *) (create_struct->lpCreateParams)));
            return 0;
        }
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
    }
}
