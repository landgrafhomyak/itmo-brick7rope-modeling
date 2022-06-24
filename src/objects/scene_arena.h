#ifndef Brick7RopeModeling_Objects_SCENE_ARENA_H
# define Brick7RopeModeling_Objects_SCENE_ARENA_H


# ifdef __cplusplus
#  include <cstddef>
# else

#  include <stddef.h>

# endif

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

struct Brick7RopeModeling_SceneArena_NodeHead
{
    struct Brick7RopeModeling_SceneArena_NodeHead *prev;
    struct Brick7RopeModeling_SceneArena_NodeHead *next;
};

typedef struct Brick7RopeModeling_SceneArena
{
    HANDLE heap;
    struct Brick7RopeModeling_SceneArena_NodeHead *nodes;
} Brick7RopeModeling_SceneArena;

BOOL Brick7RopeModeling_SceneArena_Init(Brick7RopeModeling_SceneArena *self, HANDLE heap);

struct Brick7RopeModeling_Scene;

BOOL Brick7RopeModeling_SceneArena_LinkScene(Brick7RopeModeling_SceneArena *self, struct Brick7RopeModeling_Scene *scene, size_t bricks_count, size_t ropes_count);

void Brick7RopeModeling_SceneArena_UnLinkScene(Brick7RopeModeling_SceneArena *self, struct Brick7RopeModeling_Scene *scene);

void Brick7RopeModeling_SceneArena_Finalize(Brick7RopeModeling_SceneArena *self);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_Objects_SCENE_ARENA_H */
