#include <stddef.h>

#include <windows.h>

#include "../common.h"
#include "../gui.h"

const ATOM Brick7RopeModeling_MainWindow_ClassAtom;

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

        Brick7RopeModeling_Debug("  Loading icon...");
        Brick7RopeModeling_MainWindow_ClassDefImpl.hIcon = LoadImageA(hInstance, "MAIN_ICON", IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
        if (Brick7RopeModeling_MainWindow_ClassDefImpl.hIcon == NULL)
        {
            Brick7RopeModeling_Debug("  Failed to load icon, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_0;
        }
        else
        {
            Brick7RopeModeling_Debug("  Icon loaded successful");
        }

#if 0
        Brick7RopeModeling_Debug("  Loading cursor...");
        Brick7RopeModeling_MainWindow_ClassDefImpl.hCursor = LoadImageA(hInstance, "MAIN_CURSOR", IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR);
        if (Brick7RopeModeling_MainWindow_ClassDefImpl.hCursor == NULL)
        {
            Brick7RopeModeling_Debug("  Failed to load cursor, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_1;
        }
        else
        {
            Brick7RopeModeling_Debug("  Cursor loaded successful");
        }
#endif

        Brick7RopeModeling_Debug("  Creating background brush...");
        Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
        if (Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground == NULL)
        {
            Brick7RopeModeling_Debug("  Failed to create background brush, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_2;
        }
        else
        {
            Brick7RopeModeling_Debug("  Background brush was created successful");
        }

        Brick7RopeModeling_Debug("  Registering...");
        *(ATOM *) &Brick7RopeModeling_MainWindow_ClassAtom = RegisterClassExW(&Brick7RopeModeling_MainWindow_ClassDefImpl);
        if (Brick7RopeModeling_MainWindow_ClassAtom == 0)
        {
            Brick7RopeModeling_Debug("  Failed to register main window class, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_3;
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


    return (ATOM *) &Brick7RopeModeling_MainWindow_ClassAtom;

    FINALIZE_AND_RETURN_ERROR_3:
    Brick7RopeModeling_Debug("  Deleting background brush...");
    if (!DeleteObject(Brick7RopeModeling_MainWindow_ClassDefImpl.hbrBackground))
    {
        Brick7RopeModeling_Debug("  Failed to delete background brush");
    }
    else
    {
        Brick7RopeModeling_Debug("  Background brush deleted successful");

    }

    FINALIZE_AND_RETURN_ERROR_2:
#if 0
    Brick7RopeModeling_Debug("  Destroying cursor...");
    if (!DestroyCursor(Brick7RopeModeling_MainWindow_ClassDefImpl.hCursor))
    {
        Brick7RopeModeling_Debug("  Failed to destroy cursor");
    }
    else
    {
        Brick7RopeModeling_Debug("  Cursor destroyed successful");
    }
# endif

    FINALIZE_AND_RETURN_ERROR_1:
    Brick7RopeModeling_Debug("  Destroying icon...");
    if (!DestroyIcon(Brick7RopeModeling_MainWindow_ClassDefImpl.hIcon))
    {
        Brick7RopeModeling_Debug("  Failed to destroy icon");
    }
    else
    {
        Brick7RopeModeling_Debug("  Icon destroyed successful");
    }

    FINALIZE_AND_RETURN_ERROR_0:
    Brick7RopeModeling_Debug("  Rolled back successful");

    return NULL;
}

BOOL Brick7RopeModeling_MainWindow_UnRegisterClass(void)
{
    BOOL ret = TRUE;

    Brick7RopeModeling_Debug("  Checking main window class state...");
    if (Brick7RopeModeling_MainWindow_ClassDef != NULL)
    {
        Brick7RopeModeling_Debug("  Main window class was register, unregistering...");
        if (!UnregisterClassW(Brick7RopeModeling_MainWindow_ClassAtom, Brick7RopeModeling_MainWindow_ClassDefImpl.hInstance))
        {
            Brick7RopeModeling_Debug("  Failed to unregister main window class");
            ret = FALSE;
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

#if 0
    Brick7RopeModeling_Debug("  Destroying cursor...");
    if (!DestroyCursor(Brick7RopeModeling_MainWindow_ClassDefImpl.hCursor))
    {
        Brick7RopeModeling_Debug("  Failed to destroy cursor");
        ret = FALSE;
    }
    else
    {
        Brick7RopeModeling_Debug("  Cursor destroyed successful");
    }
# endif

    Brick7RopeModeling_Debug("  Destroying icon...");
    if (!DestroyIcon(Brick7RopeModeling_MainWindow_ClassDefImpl.hIcon))
    {
        Brick7RopeModeling_Debug("  Failed to destroy icon");
        ret = FALSE;
    }
    else
    {
        Brick7RopeModeling_Debug("  Icon destroyed successful");
    }

    return ret;
}


const ATOM Brick7RopeModeling_ToolPanel_ClassAtom;

static WNDCLASSEXW Brick7RopeModeling_ToolPanel_ClassDefImpl = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = 0,
        .lpfnWndProc = NULL,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = NULL,
        .hIcon = NULL,
        .hCursor = NULL,
        .hbrBackground = NULL,
        .lpszMenuName = NULL,
        .lpszClassName = Brick7RopeModeling_ToolPanel_ClassName,
        .hIconSm = NULL
};

static WNDCLASSEXW *Brick7RopeModeling_ToolPanel_ClassDef = NULL;


ATOM *Brick7RopeModeling_ToolPanel_RegisterClass(HINSTANCE hInstance)
{
    Brick7RopeModeling_Debug("  Checking tool panel class state...");
    if (Brick7RopeModeling_ToolPanel_ClassDef == NULL)
    {
        Brick7RopeModeling_Debug("  Tool panel class wasn't initialized, initializing...");
        Brick7RopeModeling_ToolPanel_ClassDefImpl.hInstance = hInstance;

        Brick7RopeModeling_Debug("  Registering...");
        *(ATOM *) &Brick7RopeModeling_ToolPanel_ClassAtom = RegisterClassExW(&Brick7RopeModeling_ToolPanel_ClassDefImpl);
        if (Brick7RopeModeling_ToolPanel_ClassAtom == 0)
        {
            Brick7RopeModeling_Debug("  Failed to register tool panel class, rollback...");
            goto FINALIZE_AND_RETURN_ERROR_0;
        }
        else
        {
            Brick7RopeModeling_Debug("  Tool panel class registered successful");
        }

        Brick7RopeModeling_ToolPanel_ClassDef = &Brick7RopeModeling_ToolPanel_ClassDefImpl;
    }
    else
    {
        Brick7RopeModeling_Debug("  Tool panel class was register earlier");
    }


    return (ATOM *) &Brick7RopeModeling_ToolPanel_ClassAtom;

    FINALIZE_AND_RETURN_ERROR_0:

    Brick7RopeModeling_Debug("  Rolled back successful");

    return NULL;
}

BOOL Brick7RopeModeling_ToolPanel_UnRegisterClass(void)
{
    BOOL ret = TRUE;

    Brick7RopeModeling_Debug("  Checking tool panel class state...");
    if (Brick7RopeModeling_ToolPanel_ClassDef != NULL)
    {
        Brick7RopeModeling_Debug("  Tool panel class was register, unregistering...");
        if (!UnregisterClassW(Brick7RopeModeling_ToolPanel_ClassAtom, Brick7RopeModeling_ToolPanel_ClassDefImpl.hInstance))
        {
            Brick7RopeModeling_Debug("  Failed to unregister tool panel class");
            ret = FALSE;
        }
        else
        {
            Brick7RopeModeling_Debug("  Tool panel class unregistered successful");
        }
    }
    else
    {
        Brick7RopeModeling_Debug("  Tool panel class wasn't registered");
    }

    return ret;
}

BOOL Brick7RopeModeling_GUI_RegisterAllClasses(HINSTANCE hInstance)
{
    Brick7RopeModeling_Debug("Registering main window class...");
    if (Brick7RopeModeling_MainWindow_RegisterClass(hInstance) == NULL)
    {
        Brick7RopeModeling_Debug("Failed to register main window class, rolling back...");
        goto FINALIZE_AND_RETURN_ERROR;
    }
    else
    {
        Brick7RopeModeling_Debug("Main window class registered successful");
    }

    Brick7RopeModeling_Debug("Registering tool panel class...");
    if (Brick7RopeModeling_ToolPanel_RegisterClass(hInstance) == NULL)
    {
        Brick7RopeModeling_Debug("Failed to register tool panel class, rolling back...");
        goto FINALIZE_AND_RETURN_ERROR;
    }
    else
    {
        Brick7RopeModeling_Debug("Tool panel class registered successful");
    }

    return TRUE;

    FINALIZE_AND_RETURN_ERROR:

    if (!Brick7RopeModeling_GUI_UnRegisterAllClasses())
    {
        Brick7RopeModeling_Debug("Failed to rollback");
    }
    else
    {
        Brick7RopeModeling_Debug("Rolled back successful");
    }

    return FALSE;
}

BOOL Brick7RopeModeling_GUI_UnRegisterAllClasses(void)
{
    BOOL ret = TRUE;

    Brick7RopeModeling_Debug("Unregistering main window class...");
    if (!Brick7RopeModeling_MainWindow_UnRegisterClass())
    {
        Brick7RopeModeling_Debug("Failed to unregister main window class");
        ret = FALSE;
    }
    else
    {
        Brick7RopeModeling_Debug("Main window class unregistered successful");
    }

    Brick7RopeModeling_Debug("Unregistering tool panel class...");
    if (!Brick7RopeModeling_ToolPanel_UnRegisterClass())
    {
        Brick7RopeModeling_Debug("Failed to unregister tool panel class");
        ret = FALSE;
    }
    else
    {
        Brick7RopeModeling_Debug("Tool panel class unregistered successful");
    }

    return ret;
}