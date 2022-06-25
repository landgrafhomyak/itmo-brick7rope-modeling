#include <windows.h>

#include "../app.h"
#include "button.hpp"


static const constexpr size_t Brick7RopeModeling_ToolPanelButton_Size = 64;


static Brick7RopeModeling_WinButtonFactory Brick7RopeModeling_ToolPanelButton_Factories[] = {
        {
                "BUTTON_CANCEL",        L"Cancel",        Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_VOID
                }
        },
        {
                "BUTTON_RESET",         L"Reset",         Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_RESUME",        L"Resume",        Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_PAUSE",         L"Pause",         Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::ENABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_UNDO",          L"Undo",          Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING

                }
        },
        {
                "BUTTON_REDO",          L"Redo",          Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_ADD_BUTTON",    L"Add button",    Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_REMOVE_BUTTON", L"Remove button", Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_ADD_ROPE",      L"Add rope",      Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_REMOVE_ROPE",   L"Remove rope",   Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_LOCK_BRICK",    L"Lock brick",    Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_UNLOCK_BRICK",  L"Unlock brick",  Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
        {
                "BUTTON_DRAG_BRICK",    L"Drag brick",    Brick7RopeModeling_ToolPanelButton_Size,
                Brick7RopeModeling_WinButton::DISABLED_ON_SPECIFIED_STATES,
                {
                        Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type_RUNNING
                }
        },
};

bool Brick7RopeModeling_ToolPanel_WM_CREATE() {

}