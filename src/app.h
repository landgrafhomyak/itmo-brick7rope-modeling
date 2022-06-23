#ifndef Brick7RopeModeling_APP_H
# define Brick7RopeModeling_APP_H

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct Brick7RopeModeling_App
{
    HINSTANCE hInstance;
    HICON main_icon;
    HCURSOR canvas_cursor;
    ATOM main_window_class;
    ATOM tool_panel_window_class;
    HWND main_window;
    HWND tool_panel_window;
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
