#ifndef Brick7RopeModeling_Objects_ROPE_H
# define Brick7RopeModeling_Objects_ROPE_H

# ifdef __cplusplus
#  include <cstddef>
# else
#  include <stddef.h>
# endif

# include <windows.h>

# ifdef __cplusplus
extern "C" {
# endif

# define Brick7RopeModeling_Rope_INVALID_INDEX ((size_t)-1)

typedef struct Brick7RopeModeling_Rope
{
    size_t brick1_index;
    size_t brick2_index;
    long double young_module;
} Brick7RopeModeling_Rope;

BOOL Brick7RopeModeling_Rope_Init(Brick7RopeModeling_Rope *self);

void Brick7RopeModeling_Rope_Finalize(Brick7RopeModeling_Rope *self);

# ifdef __cplusplus
};
# endif


#endif /* Brick7RopeModeling_Objects_ROPE_H */
