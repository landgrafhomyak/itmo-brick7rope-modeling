#ifndef Brick7RopeModeling_GUI_H
# define Brick7RopeModeling_GUI_H

# include <windows.h>

# include "common.h"

extern const ATOM Brick7RopeModeling_MainWindow_Class;

ATOM *Brick7RopeModeling_MainWindow_RegisterClass(HINSTANCE hInstance);

BOOL Brick7RopeModeling_MainWindow_UnRegisterClass(void);

# define Brick7RopeModeling_MainWindow_ClassName (Brick7RopeModeling_WINDOWS_NAME(L"MainWindow"))

#endif /* Brick7RopeModeling_GUI_H */
