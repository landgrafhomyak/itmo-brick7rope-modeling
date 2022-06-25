#include <string.h>

#include <windows.h>

#include "scene_arena.h"
#include "scene.h"

BOOL Brick7RopeModeling_Scene_Init(Brick7RopeModeling_Scene *self)
{
    self->owner = NULL;
    self->handler = NULL;
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
        Brick7RopeModeling_SceneArena_LinkScene(self->owner, dst, self->bricks_count + 1, self->ropes_count + 1);
        memcpy(dst->bricks, self->bricks, sizeof(Brick7RopeModeling_Brick) * self->bricks_count);
        dst->bricks_count = self->bricks_count;
        memcpy(dst->ropes, self->ropes, sizeof(Brick7RopeModeling_Rope) * self->ropes_count);
        dst->ropes_count = self->ropes_count;
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


void Brick7RopeModeling_Scene_RemoveBrick(Brick7RopeModeling_Scene *self, size_t brick_index)
{
    if (brick_index >= self->bricks_count)
    { return; }

    memmove(&(self->bricks[brick_index]), &(self->bricks[brick_index + 1]), sizeof(Brick7RopeModeling_Brick) * (--self->bricks_count - brick_index));

    for (size_t i = 0; i < self->ropes_count; i++)
    {
        if (self->ropes[i].brick1_index == brick_index || self->ropes[i].brick2_index == brick_index)
        {
            Brick7RopeModeling_Scene_RemoveRope(self, i);
            i--;
            continue;
        }
        if (self->ropes[i].brick1_index > brick_index)
        { self->ropes[i].brick1_index--; }
        if (self->ropes[i].brick2_index > brick_index)
        { self->ropes[i].brick2_index--; }
    }
}

void Brick7RopeModeling_Scene_RemoveRope(Brick7RopeModeling_Scene *self, size_t rope_index)
{
    if (rope_index >= self->ropes_count)
    { return; }

    memmove(&(self->bricks[rope_index]), &(self->bricks[rope_index + 1]), sizeof(Brick7RopeModeling_Rope) * (--self->ropes_count - rope_index));
}

void Brick7RopeModeling_Scene_AddBrick(Brick7RopeModeling_Scene *self, Brick7RopeModeling_Brick brick)
{
    if (self->bricks_count >= self->allocated_bricks_count)
    { return; }

    self->bricks[self->bricks_count++] = brick;
}

void Brick7RopeModeling_Scene_AddRope(Brick7RopeModeling_Scene *self, Brick7RopeModeling_Rope rope)
{
    if (self->ropes_count >= self->allocated_ropes_count)
    { return; }

    self->ropes[self->ropes_count++] = rope;
}

