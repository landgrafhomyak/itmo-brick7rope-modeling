#include <windows.h>

#include "brick.h"
#include "rope.h"
#include "scene_arena.h"
#include "scene.h"

BOOL Brick7RopeModeling_SceneArena_Init(Brick7RopeModeling_SceneArena *self, HANDLE heap)
{
    self->heap = heap;
    self->nodes = NULL;
    return FALSE;
}

BOOL Brick7RopeModeling_SceneArena_LinkScene(Brick7RopeModeling_SceneArena *self, Brick7RopeModeling_Scene *scene, size_t bricks_count, size_t ropes_count)
{
    if (scene->handler != NULL)
    { Brick7RopeModeling_SceneArena_UnLinkScene(self, scene); }

    struct Brick7RopeModeling_SceneArena_NodeHead *p = HeapAlloc(
            self->heap,
            0,
            sizeof(struct Brick7RopeModeling_SceneArena_NodeHead) + sizeof(Brick7RopeModeling_Brick) * bricks_count + sizeof(Brick7RopeModeling_Rope) * ropes_count
    );
    if (p == NULL)
    { return TRUE; }

    p->next = self->nodes;
    p->prev = NULL;
    if (self->nodes != NULL)
    { self->nodes->prev = p; }
    self->nodes = p;

    scene->owner = self;
    scene->handler = p;
    scene->allocated_bricks_count = bricks_count;
    scene->bricks = (Brick7RopeModeling_Brick *) (((uintptr_t) p) + sizeof(struct Brick7RopeModeling_SceneArena_NodeHead));
    scene->allocated_ropes_count = ropes_count;
    scene->ropes = (Brick7RopeModeling_Rope *) (((uintptr_t) p) + sizeof(Brick7RopeModeling_Brick) * bricks_count);

    return FALSE;
}

void Brick7RopeModeling_SceneArena_UnLinkScene(Brick7RopeModeling_SceneArena *self, Brick7RopeModeling_Scene *scene)
{
    struct Brick7RopeModeling_SceneArena_NodeHead *p = scene->handler;

    if (p == NULL)
    { return; }

    if (p == self->nodes)
    { self->nodes = p->next; }

    if (p->prev != NULL)
    { p->prev->next = p->next; }

    if (p->next != NULL)
    { p->next->prev = p->prev; }

    HeapFree(self->heap, 0, p);

    scene->owner = NULL;
    scene->handler = NULL;
    scene->allocated_bricks_count = 0;
    scene->bricks_count = 0;
    scene->bricks = NULL;
    scene->allocated_ropes_count = 0;
    scene->ropes_count = 0;
    scene->ropes = NULL;
}

void Brick7RopeModeling_SceneArena_Finalize(Brick7RopeModeling_SceneArena *self)
{
    Brick7RopeModeling_Scene fake_scene;

    while (self->nodes != NULL)
    {
        fake_scene.handler = self->nodes;
        Brick7RopeModeling_SceneArena_UnLinkScene(self, &fake_scene);
    }
}
