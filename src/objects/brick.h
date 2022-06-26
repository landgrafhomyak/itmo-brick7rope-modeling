#ifndef Brick7RopeModeling_Objects_BRICK_H
# define Brick7RopeModeling_Objects_BRICK_H

# ifdef __cplusplus
#  include <cstddef>
# else

#  include <stddef.h>

# endif

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

typedef struct Brick7RopeModeling_Brick
{
    long double x;
    long double y;
    BOOL is_locked;

    long double mass;
    long double speed;
    long double sx;
    long double sy;
} Brick7RopeModeling_Brick;

BOOL Brick7RopeModeling_Brick_Init(Brick7RopeModeling_Brick *self);

void Brick7RopeModeling_Brick_Finalize(Brick7RopeModeling_Brick *self);

# ifdef __cplusplus
};
# endif

#endif /* Brick7RopeModeling_Objects_BRICK_H */
