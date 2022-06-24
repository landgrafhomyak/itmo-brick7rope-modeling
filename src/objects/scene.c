#include <windows.h>

#include "scene_arena.h"
#include "scene.h"

BOOL Brick7RopeModeling_Scene_Init(Brick7RopeModeling_Scene *self)
{
    self->owner = NULL;
    self->allocated_bricks_count = 0;
    self->bricks_count = 0;
    self->bricks = NULL;
    self->allocated_ropes_count = 0;
    self->ropes_count = 0;
    self->ropes = NULL;
    return FALSE;
}

Brick7RopeModeling_Scene *Brick7RopeModeling_Scene_Copy(Brick7RopeModeling_Scene *self, Brick7RopeModeling_Scene *dst)
{
    if (self->owner != NULL)
    {
        Brick7RopeModeling_SceneArena_LinkScene(self->owner, self, self->bricks_count + 1, self->ropes_count + 1);
    }
    else
    { *dst = *self; }
    return dst;
}

void Brick7RopeModeling_Scene_Finalize(Brick7RopeModeling_Scene *self)
{
    if (self->owner != NULL)
    { Brick7RopeModeling_SceneArena_UnLinkScene(self->owner, self); }
}
