#include <windows.h>

#include "gui.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    if (!Brick7RopeModeling_GUI_RegisterAllClasses(hInstance))
    {
        Brick7RopeModeling_Debug("Failed to register windows classes");
        MessageBoxA(NULL, "Can't register windows classes", "Initializing error", MB_OK | MB_ICONERROR);
        return 1;
    }

    Brick7RopeModeling_Debug("");
    Brick7RopeModeling_Debug("Creating windows...");
    Brick7RopeModeling_Debug("");

    if (!Brick7RopeModeling_GUI_UnRegisterAllClasses())
    {
        Brick7RopeModeling_Debug("Failed to unregister windows classes");
        MessageBoxA(NULL, "Can't unregister windows classes", "Finalizing error", MB_OK | MB_ICONERROR);
        return 2;
    }

    Brick7RopeModeling_Debug("");
    Brick7RopeModeling_Debug("Exit code 0");

    return 0;
}