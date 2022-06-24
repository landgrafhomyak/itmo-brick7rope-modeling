#include <windows.h>

#include "brick.h"

BOOL Brick7RopeModeling_Brick_Init(Brick7RopeModeling_Brick *self)
{
    self->x = 0;
    self->y = 0;
    self->is_locked = FALSE;
    return FALSE;
}

void Brick7RopeModeling_Brick_Finalize(Brick7RopeModeling_Brick *self)
{}
