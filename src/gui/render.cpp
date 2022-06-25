#include <windows.h>

#include "../objects/scene.h"
#include "../app.h"
#include "../threads.h"

template<typename pixel_t>
class Brick7RopeModeling_RawBufferCanvas
{
private:
    pixel_t *buffer;
    size_t width;
    size_t height;
public:
    constexpr inline explicit Brick7RopeModeling_RawBufferCanvas(pixel_t *buffer, size_t width, size_t height) noexcept: buffer(buffer), width(width), height(height)
    {}

    constexpr inline void set_pixel(size_t x, size_t y, pixel_t color)
    {
        if (!(0 <= x && x < this->width) || !(0 <= y && y < this->height))
        { return; }
        buffer[y * width + x] = color;
    }
};

template<class canvas_t>
void Brick7RopeModeling_DrawLine(canvas_t canvas, INT x1, INT y1, INT x2, INT y2, DWORD outline)
{
    INT X, Y, dx, dy, count, sx, F;
    if (y2 < y1)
    {
        INT _tmp;
        _tmp = x1, x1 = x2, x2 = _tmp;
        _tmp = y1, y1 = y2, y2 = _tmp;
    }
    sx = (x2 > x1) ? 1 : -1;

    dx = (x2 - x1) * sx;
    dy = y2 - y1;

    if (dx > 3000 || dy > 3000)
    {
        return;
    }

    X = x1;
    Y = y1;


    canvas.set_pixel(X, Y, outline);

    if (dx > dy)
    {

        F = dy * 2 - dx;
        count = dx;
        while (count-- > 0)
        {
            if (F > 0)
            {
                Y++;
                F += dy * 2 - dx * 2;
            }
            else
            {
                F += dy * 2;
            }
            X += sx;
            canvas.set_pixel(X, Y, outline);
        }
    }
    else
    {
        F = dx * 2 - dy;
        count = dy;
        while (count-- > 0)
        {

            if (F > 0)
            {
                X += sx;
                F += dx * 2 - dy * 2;
            }
            else
            {
                F += dx * 2;
            }
            Y++;
            canvas.set_pixel(X, Y, outline);
        }
    }
}


template<class canvas_t>
void Brick7RopeModeling_Fill(canvas_t canvas, INT x1, INT y1, INT x2, INT y2, DWORD outline, DWORD fill)
{
    INT x, y;

    for (x = x1; x <= x2; x++)
    { canvas.set_pixel(x, y1, outline); }

    for (y = y1 + 1; y < y2; y++)
    {
        canvas.set_pixel(x1, y, outline);
        for (x = x1 + 1; x < x2; x++)
        { canvas.set_pixel(x, y, fill); }
        canvas.set_pixel(x2, y, outline);
    }

    for (x = x1; x <= x2; x++)
    { canvas.set_pixel(x, y2, outline); }
}

template<class canvas_t>
inline void Brick7RopeModeling_DrawCircle(canvas_t canvas, INT cx, INT cy, INT r, DWORD outline, DWORD fill)
{
    Brick7RopeModeling_Fill(canvas, cx - r, cy - r, cx + r, cy + r, outline, fill);
}

DWORD DECLSPEC_NORETURN Brick7RopeModeling_RenderThreadMain(Brick7RopeModeling_App *app)
{
    Brick7RopeModeling_Scene local_scene;
    enum
    {
        BUFFER_1,
        BUFFER_2
    } buffer_no = BUFFER_1;
    Brick7RopeModeling_RawBufferCanvas<DWORD> canvas(nullptr, 0, 0);
    int i;

    Brick7RopeModeling_Scene_Init(&local_scene);

    while (TRUE)
    {
        EnterCriticalSection(&(app->render_access_mutex));
        if (app->render_accessories.width != app->main_window_width || app->render_accessories.height != app->main_window_height)
        {
            app->render_accessories.width = app->main_window_width;
            app->render_accessories.height = app->main_window_height;
            LeaveCriticalSection(&(app->render_access_mutex));
            goto REALLOC_BUFFERS;
        }
        LeaveCriticalSection(&(app->render_access_mutex));

        if (0)
        {
            REALLOC_BUFFERS:
            if (app->render_accessories.bitmap1 != nullptr)
            { DeleteObject(app->render_accessories.bitmap1); }
            if (app->render_accessories.bitmap2 != nullptr)
            { DeleteObject(app->render_accessories.bitmap2); }


            static BITMAPINFOHEADER bmih;
            bmih.biSize = sizeof(BITMAPINFOHEADER);
            bmih.biWidth = (LONG) (app->render_accessories.width);
            bmih.biHeight = -(LONG) (app->render_accessories.height);
            bmih.biPlanes = 1;
            bmih.biBitCount = 32;
            bmih.biCompression = BI_RGB;
            bmih.biSizeImage = app->render_accessories.width * app->render_accessories.height * 4;

            app->render_accessories.bitmap1 = CreateDIBSection(nullptr, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, &(app->render_accessories.bitmap1_data), nullptr, 0);
            app->render_accessories.bitmap2 = CreateDIBSection(nullptr, (BITMAPINFO *) &bmih, DIB_RGB_COLORS, &(app->render_accessories.bitmap2_data), nullptr, 0);
        }


        EnterCriticalSection(&(app->engine_mutex));
        Brick7RopeModeling_Scene_Copy(&(app->engine_out), &local_scene);
        LeaveCriticalSection(&(app->engine_mutex));

        switch (buffer_no)
        {
            case BUFFER_1:
                canvas = Brick7RopeModeling_RawBufferCanvas<DWORD>((DWORD *) app->render_accessories.bitmap1_data, app->render_accessories.width, app->render_accessories.height);
                break;
            case BUFFER_2:
                canvas = Brick7RopeModeling_RawBufferCanvas<DWORD>((DWORD *) app->render_accessories.bitmap2_data, app->render_accessories.width, app->render_accessories.height);
                break;
        }

        Brick7RopeModeling_Fill(canvas, 0, 0, app->render_accessories.width - 1, app->render_accessories.height - 1, RGB(0, 0, 0), RGB(0, 0, 0));

        for (i = 0; i < local_scene.ropes_count; i++)
        {
            Brick7RopeModeling_DrawLine(
                    canvas,
                    (INT) local_scene.bricks[local_scene.ropes[i].brick1_index].x,
                    (INT) local_scene.bricks[local_scene.ropes[i].brick1_index].y,
                    (INT) local_scene.bricks[local_scene.ropes[i].brick2_index].x,
                    (INT) local_scene.bricks[local_scene.ropes[i].brick2_index].y,
                    RGB(255, 255, 255)
            );
        }

        for (i = 0; i < local_scene.bricks_count; i++)
        {
            Brick7RopeModeling_DrawCircle(
                    canvas,
                    (INT) local_scene.bricks[i].x,
                    (INT) local_scene.bricks[i].y,
                    app->brick_size,
                    RGB(255, 255, 255),
                    RGB(15, 15, 15)
            );
        }

        Brick7RopeModeling_Scene_Finalize(&local_scene);

        EnterCriticalSection(&(app->render_access_mutex));
        switch (buffer_no)
        {
            case BUFFER_1:
                SelectObject(app->render_accessories.hdc, app->render_accessories.bitmap1);
                buffer_no = BUFFER_2;
                break;
            case BUFFER_2:
                SelectObject(app->render_accessories.hdc, app->render_accessories.bitmap2);
                buffer_no = BUFFER_1;
                break;
        }
        LeaveCriticalSection(&(app->render_access_mutex));

    }
}