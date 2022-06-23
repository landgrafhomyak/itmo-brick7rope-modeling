#ifndef Brick7RopeModeling_GUI_H
# define Brick7RopeModeling_GUI_H

# include <windows.h>

# include "common.h"

# ifdef __cpluslpus
extern "C" {
# endif

extern const ATOM Brick7RopeModeling_MainWindow_ClassAtom;

ATOM *Brick7RopeModeling_MainWindow_RegisterClass(HINSTANCE hInstance);

BOOL Brick7RopeModeling_MainWindow_UnRegisterClass(void);

extern const ATOM Brick7RopeModeling_ToolPanel_ClassAtom;

ATOM *Brick7RopeModeling_ToolPanel_RegisterClass(HINSTANCE hInstance);

BOOL Brick7RopeModeling_ToolPanel_UnRegisterClass(void);

BOOL Brick7RopeModeling_GUI_RegisterAllClasses(HINSTANCE hInstance);

BOOL Brick7RopeModeling_GUI_UnRegisterAllClasses(void);


# define Brick7RopeModeling_MainWindow_ClassName (Brick7RopeModeling_WINDOWS_NAME(L"MainWindow"))
# define Brick7RopeModeling_ToolPanel_ClassName (Brick7RopeModeling_WINDOWS_NAME(L"ToolPanel"))

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_GUI_H */
