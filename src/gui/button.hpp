#ifndef Brick7RopeModeling_GUI_BUTTON_HPP
# define Brick7RopeModeling_GUI_BUTTON_HPP

# include <initializer_list>

# include <windows.h>

# include "../app.h"

class Brick7RopeModeling_WinButton
{
public:
    enum IsEnabledOnStates {
        ENABLED_ON_SPECIFIED_STATES,
        DISABLED_ON_SPECIFIED_STATES,
    };
private:
    std::initializer_list<Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type> states;
    IsEnabledOnStates is_enabled_on_states;

    HICON icon = nullptr;

    HWND reference = nullptr;

    BOOL (*click_event_callback)(Brick7RopeModeling_App *);

public:
    constexpr inline Brick7RopeModeling_WinButton(
            std::initializer_list<Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type> states,
            IsEnabledOnStates is_enabled_on_states,
            HICON icon,
            HWND reference,
            BOOL (*click_event_callback)(Brick7RopeModeling_App *)
    ) noexcept: states(states), is_enabled_on_states(is_enabled_on_states), icon(icon), reference(reference), click_event_callback(click_event_callback)
    {}

    void release_icon() noexcept;
};


class Brick7RopeModeling_WinButtonFactory
{
private:
    char const *icon_resource_name;
    wchar_t const *button_name;
    unsigned short size;

    std::initializer_list<Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type> states;
    Brick7RopeModeling_WinButton::IsEnabledOnStates is_enabled_on_states;
public:
    constexpr inline Brick7RopeModeling_WinButtonFactory(
            char const *icon_resource_name,
            wchar_t const *button_name,
            unsigned short size,
            Brick7RopeModeling_WinButton::IsEnabledOnStates is_enabled_on_states,
            std::initializer_list<Brick7RopeModeling_AppAction::Brick7RopeModeling_AppAction_Type> states
    ) noexcept: icon_resource_name(icon_resource_name), button_name(button_name), size(size), states(states), is_enabled_on_states(is_enabled_on_states)
    {}

    bool instantiate(
            Brick7RopeModeling_WinButton *dst,
            HINSTANCE hInstance,
            HWND parent,
            unsigned short x,
            unsigned short y
    ) const noexcept;
};


#endif /* Brick7RopeModeling_GUI_BUTTON_HPP */
