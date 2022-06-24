#ifndef Brick7RopeModeling_GUI_MAIN_WINDOW_DATA_H
# define Brick7RopeModeling_GUI_MAIN_WINDOW_DATA_H

# ifdef __cplusplus
extern "C" {
# endif

# include <windows.h>

typedef struct Brick7RopeModeling_GUI_MainWindow_Data
{
    unsigned short width;
    unsigned short height;
    void *bitmap;
    CRITICAL_SECTION mutex;
} Brick7RopeModeling_GUI_MainWindow_Data;

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_GUI_MAIN_WINDOW_DATA_H */
