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
class Brick7RopeModeling_DrawCircle
{
private:
    canvas_t canvas;
    INT cx;
    INT cy;
    INT r;

    template<class action_t>
    inline void calc(DWORD color)
    {
        INT x = 0, y = r, delta = 1 - 2 * r, error = 0;
        action_t action(this->canvas, color);

        while (y >= x)
        {
            action.process(cx - x, cy + y, cx + x);
            action.process(cx - x, cy - y, cx + x);
            action.process(cx - y, cy + x, cx + y);
            action.process(cx - y, cy - x, cx + y);

            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0))
            { delta += 2 * ++x + 1; }
            else if ((delta > 0) && (error > 0))
            { delta -= 2 * --y + 1; }
            else
            { delta += 2 * (++x - --y); }
        }
    }

    class FillAction
    {
    private:
        canvas_t canvas;
        DWORD color;
    public:
        inline constexpr FillAction(canvas_t canvas, DWORD color) noexcept: canvas(canvas), color(color)
        {}

        inline void process(INT x1, INT y, INT x2)
        {
            INT x;
            for (x = x1 + 1; x < x2; x++)
            { this->canvas.set_pixel(x, y, this->color); }
        }
    };

    class OutlineAction
    {
    private:
        canvas_t canvas;
        DWORD color;
    public:
        inline constexpr OutlineAction(canvas_t canvas, DWORD color) noexcept: canvas(canvas), color(color)
        {}

        inline void process(INT x1, INT y, INT x2)
        {
            this->canvas.set_pixel(x1, y, this->color);
            this->canvas.set_pixel(x2, y, this->color);
        }
    };

public:
    inline Brick7RopeModeling_DrawCircle(canvas_t canvas, INT cx, INT cy, INT r, DWORD outline, DWORD fill) :
            canvas(canvas), cx(cx), cy(cy), r(r)
    {
        this->calc<Brick7RopeModeling_DrawCircle<canvas_t>::FillAction>(fill);
        this->calc<Brick7RopeModeling_DrawCircle<canvas_t>::OutlineAction>(outline);
    }

    inline Brick7RopeModeling_DrawCircle(canvas_t canvas, INT cx, INT cy, INT r, DWORD outline) :
            canvas(canvas), cx(cx), cy(cy), r(r)
    {
        this->calc<Brick7RopeModeling_DrawCircle<canvas_t>::OutlineAction>(outline);
    }
};

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
    Brick7RopeModeling_AppState state;

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
        EnterCriticalSection(&(app->state.mutex));
        state = app->state;
        LeaveCriticalSection(&(app->state.mutex));

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
            Brick7RopeModeling_DrawCircle<Brick7RopeModeling_RawBufferCanvas<DWORD>>(
                    canvas,
                    (INT) local_scene.bricks[i].x,
                    (INT) local_scene.bricks[i].y,
                    app->brick_size,
                    RGB(255, 255, 255),
                    local_scene.bricks[i].is_locked ? RGB(127, 127, 127) : RGB(0, 0, 0)
            );
        }

        switch (state.selection_type)
        {
            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_SelectionType_BRICK:
                Brick7RopeModeling_DrawCircle<Brick7RopeModeling_RawBufferCanvas<DWORD>>(
                        canvas,
                        (INT) local_scene.bricks[state.selection_value.brick.brick_index].x,
                        (INT) local_scene.bricks[state.selection_value.brick.brick_index].y,
                        app->brick_size,
                        RGB(255, 0, 0),
                        local_scene.bricks[state.selection_value.brick.brick_index].is_locked ? RGB(200, 0, 0) : RGB(100, 0, 0)
                );
                break;

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_SelectionType_ROPE:
                Brick7RopeModeling_DrawLine(
                        canvas,
                        (INT) local_scene.bricks[local_scene.ropes[state.selection_value.rope.rope_index].brick1_index].x,
                        (INT) local_scene.bricks[local_scene.ropes[state.selection_value.rope.rope_index].brick1_index].y,
                        (INT) local_scene.bricks[local_scene.ropes[state.selection_value.rope.rope_index].brick2_index].x,
                        (INT) local_scene.bricks[local_scene.ropes[state.selection_value.rope.rope_index].brick2_index].y,
                        RGB(0, 255, 0)
                );
                break;
                
            default:
                break;
        }

        switch (state.action_type)
        {
            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_SELECT_BRICK:
                if (state.action_value.select_brick.brick_index != Brick7RopeModeling_INVALID_INDEX)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y - app->brick_size,
                            RGB(255, 0, 0)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y - app->brick_size,
                            RGB(255, 0, 0)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y + app->brick_size,
                            RGB(255, 0, 0)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.select_brick.brick_index].y + app->brick_size,
                            RGB(255, 0, 0)
                    );
                }

                break;

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_SELECT_ROPE:
                if (state.action_value.select_rope.rope_index != Brick7RopeModeling_INVALID_INDEX)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[local_scene.ropes[state.action_value.select_rope.rope_index].brick1_index].x,
                            (INT) local_scene.bricks[local_scene.ropes[state.action_value.select_rope.rope_index].brick1_index].y,
                            (INT) local_scene.bricks[local_scene.ropes[state.action_value.select_rope.rope_index].brick2_index].x,
                            (INT) local_scene.bricks[local_scene.ropes[state.action_value.select_rope.rope_index].brick2_index].y,
                            RGB(0, 255, 0)
                    );
                }
                break;

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_ADD_ROPE_1:
                if (state.action_value.add_rope_1.brick2_index != Brick7RopeModeling_INVALID_INDEX)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y - app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y - app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y + app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y + app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick1_index].x,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick1_index].y,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].x,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick2_index].y,
                            RGB(0, 255, 255)
                    );
                }
                else
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick1_index].x,
                            (INT) local_scene.bricks[state.action_value.add_rope_1.brick1_index].y,
                            (INT) state.action_value.add_rope_1.x2,
                            (INT) state.action_value.add_rope_1.y2,
                            RGB(0, 255, 255)
                    );
                }

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_ADD_ROPE_0:
                if (state.action_value.add_rope_0.brick1_index != Brick7RopeModeling_INVALID_INDEX)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y - app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y - app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y + app->brick_size,
                            RGB(0, 255, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.add_rope_0.brick1_index].y + app->brick_size,
                            RGB(0, 255, 255)
                    );
                }
                break;

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_ADD_BRICK:
                Brick7RopeModeling_DrawCircle<Brick7RopeModeling_RawBufferCanvas<DWORD>>(
                        canvas,
                        (INT) state.action_value.add_brick.x,
                        (INT) state.action_value.add_brick.y,
                        app->brick_size,
                        RGB(0, 255, 0)
                );
                break;

            case Brick7RopeModeling_AppState::Brick7RopeModeling_AppState_ActionType_DRAG_BRICK:
                if (state.action_value.drag_brick.brick_index != Brick7RopeModeling_INVALID_INDEX)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y - app->brick_size,
                            RGB(0, 0, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y - app->brick_size,
                            RGB(0, 0, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y + app->brick_size,
                            RGB(0, 0, 255)
                    );
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x - app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x + app->brick_size,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y + app->brick_size,
                            RGB(0, 0, 255)
                    );
                }
                if (state.action_value.drag_brick.held)
                {
                    Brick7RopeModeling_DrawLine(
                            canvas,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].x,
                            (INT) local_scene.bricks[state.action_value.drag_brick.brick_index].y,
                            state.action_value.drag_brick.x + state.action_value.drag_brick.ox,
                            state.action_value.drag_brick.y + state.action_value.drag_brick.oy,
                            RGB(0, 0, 255)
                    );
                    Brick7RopeModeling_DrawCircle<Brick7RopeModeling_RawBufferCanvas<DWORD>>(
                            canvas,
                            state.action_value.drag_brick.x + state.action_value.drag_brick.ox,
                            state.action_value.drag_brick.y + state.action_value.drag_brick.oy,
                            app->brick_size,
                            RGB(0, 0, 255)
                    );
                }
                break;


            default:
                break;
        }

        Brick7RopeModeling_Scene_Finalize(&local_scene);
        Brick7RopeModeling_Scene_Init(&local_scene);

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