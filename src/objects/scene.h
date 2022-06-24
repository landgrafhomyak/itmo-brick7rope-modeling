#ifndef Brick7RopeModeling_Objects_SCENE_H
# define Brick7RopeModeling_Objects_SCENE_H

# ifdef __cplusplus
#  include <cstddef>
# else
#  include <stddef.h>
# endif

# include <windows.h>

# include "brick.h"
# include "rope.h"
# include "scene_arena.h"

# ifdef __cplusplus
extern "C" {
# endif

typedef struct Brick7RopeModeling_Scene
{
    Brick7RopeModeling_SceneArena *owner;
    struct Brick7RopeModeling_SceneArena_NodeHead *handler;

    size_t allocated_bricks_count;
    size_t bricks_count;
    Brick7RopeModeling_Brick *bricks;

    size_t allocated_ropes_count;
    size_t ropes_count;
    Brick7RopeModeling_Rope *ropes;
} Brick7RopeModeling_Scene;

BOOL Brick7RopeModeling_Scene_Init(Brick7RopeModeling_Scene *self);

Brick7RopeModeling_Scene *Brick7RopeModeling_Scene_Copy(Brick7RopeModeling_Scene *self, Brick7RopeModeling_Scene *dst);

void Brick7RopeModeling_Scene_Finalize(Brick7RopeModeling_Scene *self);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_Objects_SCENE_H */
