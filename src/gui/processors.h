#ifndef Brick7RopeModeling_GUI_PROCESSORS_H
# define Brick7RopeModeling_GUI_PROCESSORS_H

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

LRESULT Brick7RopeModeling_MainWindow_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

LRESULT Brick7RopeModeling_ToolPanel_Proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_GUI_PROCESSORS_H */
