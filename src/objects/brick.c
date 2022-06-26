#include <windows.h>

#include "brick.h"

BOOL Brick7RopeModeling_Brick_Init(Brick7RopeModeling_Brick *self)
{
    self->x = 0;
    self->y = 0;
    self->is_locked = FALSE;
    self->mass = rand() % 100000 + 10000;
    self->speed = 0;
    self->sx = 0;
    self->sy = 0;
    return FALSE;
}


void Brick7RopeModeling_Brick_Finalize(Brick7RopeModeling_Brick *self)
{}
