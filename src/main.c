#include <windows.h>

#include "gui.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    int exit_code = -1;
    Brick7RopeModeling_Debug("Registering main window class...");
    if (Brick7RopeModeling_MainWindow_RegisterClass(hInstance) == NULL)
    {
        Brick7RopeModeling_Debug("Failed to register main window class");
        MessageBoxA(NULL, "Can't register main window class", "Initializing error", MB_OK | MB_ICONERROR);
        goto EXIT0;
    }
    else
    {
        Brick7RopeModeling_Debug("Main window class registered successful");
    }

    exit_code = 0;

    EXIT1:
    Brick7RopeModeling_Debug("Unregistering main window class...");
    if (!Brick7RopeModeling_MainWindow_UnRegisterClass())
    {
        Brick7RopeModeling_Debug("Failed to unregister main window class");
        MessageBoxA(NULL, "Can't unregister main window class", "Finalizing error", MB_OK | MB_ICONERROR);
        goto EXIT0;
    }
    else
    {
        Brick7RopeModeling_Debug("Main window class unregistered successful");
    }


    EXIT0:
    return exit_code;
}