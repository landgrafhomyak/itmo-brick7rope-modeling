#ifndef BRICK7ROPE_MODELING_THREADS_H
# define BRICK7ROPE_MODELING_THREADS_H

# include <windows.h>
# include "app.h"

# ifdef __cplusplus
extern "C" {
# endif

DWORD Brick7RopeModeling_EngineThreadMain(Brick7RopeModeling_App *app);
DWORD Brick7RopeModeling_RenderThreadMain(Brick7RopeModeling_App *app);

# ifdef __cplusplus
};
# endif

#endif //BRICK7ROPE_MODELING_THREADS_H
