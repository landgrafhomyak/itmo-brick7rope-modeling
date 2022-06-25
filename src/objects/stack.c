#include <windows.h>
#include "scene.h"
#include "stack.h"

static inline size_t Brick7RopeModeling_DecP(size_t *n, size_t size)
{
    return *n = (*n - 1 + size) % size;
}

static inline size_t Brick7RopeModeling_Dec(size_t n, size_t size)
{
    return Brick7RopeModeling_DecP(&n, size);
}

static inline size_t Brick7RopeModeling_IncP(size_t *n, size_t size)
{
    return *n = (*n + 1) % size;
}

static inline size_t Brick7RopeModeling_Inc(size_t n, size_t size)
{
    return Brick7RopeModeling_IncP(&n, size);
}

BOOL Brick7RopeModeling_Stack_Init(Brick7RopeModeling_Stack *self)
{
    self->current = 0;
    self->start = 0;
    self->end = 0;
    return Brick7RopeModeling_Scene_Init(&(self->buffer[0]));
}


Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Add(Brick7RopeModeling_Stack *self)
{
    Brick7RopeModeling_Scene *last = &(self->buffer[self->current]);

    for (; self->end != self->current; Brick7RopeModeling_DecP(&(self->end), Brick7RopeModeling_STACK_SIZE))
    { Brick7RopeModeling_Scene_Finalize(&(self->buffer[self->end])); }

    self->current = Brick7RopeModeling_IncP(&(self->end), Brick7RopeModeling_STACK_SIZE);
    if (self->end == self->start)
    {
        Brick7RopeModeling_Scene_Finalize(&(self->buffer[self->start]));
        Brick7RopeModeling_IncP(&(self->start), Brick7RopeModeling_STACK_SIZE);
    }

    return Brick7RopeModeling_Scene_Copy(last, &(self->buffer[self->current]));
}

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Undo(Brick7RopeModeling_Stack *self)
{
    if (self->current != self->start)
    { Brick7RopeModeling_DecP(&(self->current), Brick7RopeModeling_STACK_SIZE); }

    return &(self->buffer[self->current]);
}

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Redo(Brick7RopeModeling_Stack *self)
{
    if (self->current != self->end)
    { Brick7RopeModeling_IncP(&(self->current), Brick7RopeModeling_STACK_SIZE); }

    return &(self->buffer[self->current]);
}

BOOL Brick7RopeModeling_Stack_CanUndo(Brick7RopeModeling_Stack *self)
{
    return self->current != self->start;
}

BOOL Brick7RopeModeling_Stack_CanRedo(Brick7RopeModeling_Stack *self)
{
    return self->current != self->end;
}

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_GetCurrent(Brick7RopeModeling_Stack *self)
{
    return &(self->buffer[self->current]);
}