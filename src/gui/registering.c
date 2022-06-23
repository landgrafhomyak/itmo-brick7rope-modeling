#include <stddef.h>

#include <windows.h>

#include "../common.h"
#include "../gui.h"

const ATOM Brick7RopeModeling_MainWindow_Class;

static WNDCLASSEXW Brick7RopeModeling_MainWindow_ClassDefImpl = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = NULL,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = NULL,
        .hIcon = NULL,
        .hCursor = NULL,
        .hbrBackground = NULL,
        .lpszMenuName = NULL,
        .lpszClassName = Brick7RopeModeling_MainWindow_ClassName,
        .hIconSm = NULL
};

static WNDCLASSEXW *Brick7RopeModeling_MainWindow_ClassDef = NULL;

ATOM *Brick7RopeModeling_MainWindow_RegisterClass(HINSTANCE hInstance)
{
    Brick7RopeModeling_Debug("  Checking main window class state...");
    if (Brick7RopeModeling_MainWindow_ClassDef == NULL)
    {
        Brick7RopeModeling_Debug("  Main window class wasn't initialized, initializing...");
        Brick7RopeModeling_MainWindow_ClassDefImpl.hInstance = hInstance;

        /* todo icon and cursor resources */

        Brick7RopeModeling_Debug("  Creating background brush...");
        Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
        if (Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground == NULL)
        {
            Brick7RopeModeling_Debug("  Failed to create background brush, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_0;
        }
        else
        {
            Brick7RopeModeling_Debug("  Background brush was created successful");
        }

        Brick7RopeModeling_Debug("  Registering...");
        *(ATOM *) &Brick7RopeModeling_MainWindow_Class = RegisterClassExW(&Brick7RopeModeling_MainWindow_ClassDefImpl);
        if (Brick7RopeModeling_MainWindow_Class == 0)
        {
            Brick7RopeModeling_Debug("  Failed to register main window class, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_1;
        }
        else
        {
            Brick7RopeModeling_Debug("  Main window class registered successful");
        }

        Brick7RopeModeling_MainWindow_ClassDef = &Brick7RopeModeling_MainWindow_ClassDefImpl;
    }
    else
    {
        Brick7RopeModeling_Debug("  Main window class was register earlier");
    }


    return (ATOM *) &Brick7RopeModeling_MainWindow_Class;

    FINALIZE_AND_RETURN_ERROR_1:

    Brick7RopeModeling_Debug("  Deleting background brush...");
    if (!DeleteObject(Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground))
    {
        Brick7RopeModeling_Debug("  Failed to delete background brush");
    }
    else
    {
        Brick7RopeModeling_Debug("  Background brush deleted successful");

    }

    FINALIZE_AND_RETURN_ERROR_0:
    Brick7RopeModeling_Debug("  Rolled back successful");

    return NULL;
}

BOOL Brick7RopeModeling_MainWindow_UnRegisterClass(void)
{
    Brick7RopeModeling_Debug("  Checking main window class state...");
    if (Brick7RopeModeling_MainWindow_ClassDef != NULL)
    {
        Brick7RopeModeling_Debug("  Main window class was register, unregistering...");
        if (!UnregisterClassW(Brick7RopeModeling_MainWindow_ClassName, Brick7RopeModeling_MainWindow_ClassDefImpl.hInstance))
        {
            Brick7RopeModeling_Debug("  Failed to unregister main window class");
            return FALSE;
        }
        else
        {
            Brick7RopeModeling_Debug("  Main window class unregistered successful");
        }
    }
    else
    {
        Brick7RopeModeling_Debug("  Main window class wasn't registered");
    }

    return TRUE;
}
