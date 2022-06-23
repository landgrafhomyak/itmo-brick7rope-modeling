#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct Brick7RopeModeling_App
{
    /* Configuration */
    size_t button_size;

    /* Predefined handlers */
    HINSTANCE hInstance;

    /* Resources */
    HICON main_icon;
    HCURSOR canvas_cursor;
    struct
    {
        HICON add;
        HICON remove;
    } button_icons;

    /* Window classes */
    ATOM main_window_class;
    ATOM tool_panel_window_class;

    /* Window instances */
    HWND main_window;
    HWND tool_panel_window;
    struct
    {
        HWND add;
        HWND remove;
    } button_windows;

} Brick7RopeModeling_App;

BOOL Brick7RopeModeling_LoadResources(Brick7RopeModeling_App *app);

void Brick7RopeModeling_DestroyResources(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_RegisterWindowClasses(Brick7RopeModeling_App *app);

void Brick7RopeModeling_UnRegisterWindowClasses(Brick7RopeModeling_App *app);

BOOL Brick7RopeModeling_CreateGUI(Brick7RopeModeling_App *app);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_APP_H */
