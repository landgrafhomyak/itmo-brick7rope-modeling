#include <windows.h>
#include "rope.h"

BOOL Brick7RopeModeling_Rope_Init(Brick7RopeModeling_Rope *self)
{
    self->brick1_index = Brick7RopeModeling_INVALID_INDEX;
    self->brick2_index = Brick7RopeModeling_INVALID_INDEX;
    self->young_module = 1.0;
    return FALSE;
}

void Brick7RopeModeling_Rope_Finalize(Brick7RopeModeling_Rope *self)
{
    self->brick1_index = Brick7RopeModeling_INVALID_INDEX;
    self->brick2_index = Brick7RopeModeling_INVALID_INDEX;
}
