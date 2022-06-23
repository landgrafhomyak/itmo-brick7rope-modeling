#include <windows.h>

#include "app.h"
#include "gui.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Brick7RopeModeling_App app;
    int ret;

    app.button_size = 32;

    app.hInstance = hInstance;

    if (!Brick7RopeModeling_LoadResources(&app))
    {
        ret = 1;
        goto FREE_AND_ERR_0;
    }

    if (!Brick7RopeModeling_RegisterWindowClasses(&app))
    {
        ret = 2;
        goto FREE_AND_ERR_1;
    }
    if (!Brick7RopeModeling_CreateGUI(&app))
    {
        ret = 4;
        goto FREE_AND_ERR_3;
    }

    Brick7RopeModeling_Mainloop(&app);

    ret = 0;
    Brick7RopeModeling_UnRegisterWindowClasses(&app);

    FREE_AND_ERR_3:

    FREE_AND_ERR_2:

    FREE_AND_ERR_1:
    Brick7RopeModeling_DestroyResources(&app);

    FREE_AND_ERR_0:

    return ret;
}