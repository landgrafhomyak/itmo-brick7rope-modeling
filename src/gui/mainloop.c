#include <windows.h>
#include "../app.h"

WPARAM Brick7RopeModeling_Mainloop(Brick7RopeModeling_App *app)
{
    MSG msg;
    BOOL fGotMessage;

    while ((fGotMessage = GetMessageW(&msg,  NULL, 0, 0)) != 0 && fGotMessage != -1)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return msg.wParam;
}