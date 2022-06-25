#include "button.hpp"


void Brick7RopeModeling_WinButton::release_icon() noexcept
{
    if (this->icon != nullptr)
    {
        DeleteObject(this->icon);
    }
    this->icon = nullptr;
};

bool Brick7RopeModeling_WinButtonFactory::instantiate(Brick7RopeModeling_WinButton *dst, HINSTANCE hInstance, HWND parent, unsigned short x, unsigned short y) const noexcept
{
    HICON icon = LoadIconA(hInstance, this->icon_resource_name);
    HWND button = CreateWindowExW(
            WS_EX_NOPARENTNOTIFY,
            L"Button",
            this->button_name,
            WS_VISIBLE | WS_CHILD | BS_ICON,
            x,
            y,
            this->size,
            this->size,
            parent,
            nullptr,
            hInstance,
            nullptr
    );
    if (button == nullptr)
    {
        if (icon != nullptr)
        { DeleteObject(icon); }
        return true;
    }

    if (icon != nullptr)
    {
        if (SendMessageW(button, BM_SETIMAGE, IMAGE_ICON, (LPARAM) (icon) != 0))
        {
            DeleteObject(icon);
            DestroyWindow(button);
            return true;
        }
    }
    return false;
}

