#ifndef Brick7RopeModeling_Objects_STACK_H
# define Brick7RopeModeling_Objects_STACK_H

# ifdef __cplusplus
#  include <cstddef>
# else

#  include <stddef.h>

# endif

# include <windows.h>

# include "scene.h"

# ifdef __cplusplus
extern "C" {
# endif

# define Brick7RopeModeling_STACK_SIZE (64)

typedef struct Brick7RopeModeling_Stack
{
    size_t current;
    size_t start;
    size_t end;
    Brick7RopeModeling_Scene buffer[Brick7RopeModeling_STACK_SIZE];
} Brick7RopeModeling_Stack;

BOOL Brick7RopeModeling_Stack_Init(Brick7RopeModeling_Stack *self);

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Add(Brick7RopeModeling_Stack *self);

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Undo(Brick7RopeModeling_Stack *self);

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_Redo(Brick7RopeModeling_Stack *self);

BOOL Brick7RopeModeling_Stack_CanUndo(Brick7RopeModeling_Stack *self);

BOOL Brick7RopeModeling_Stack_CanRedo(Brick7RopeModeling_Stack *self);

Brick7RopeModeling_Scene *Brick7RopeModeling_Stack_GetCurrent(Brick7RopeModeling_Stack *self);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_Objects_STACK_H */
