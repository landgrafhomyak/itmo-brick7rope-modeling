#ifndef Brick7RopeModeling_COMMON_H
# define Brick7RopeModeling_COMMON_H

# define Brick7RopeModeling_WINDOWS_NAME_PREFIX L"Brick&Rope-Modeling::"
# define Brick7RopeModeling_WINDOWS_NAME(NAME) (Brick7RopeModeling_WINDOWS_NAME_PREFIX NAME)

# ifdef Brick7RopeModeling_DEBUG_MODE
#  if __cplusplus
#   include <cstdio>
#  else
#   include <stdio.h>
#  endif
#  define Brick7RopeModeling_Debug(MSG) (printf("[DEBUG] %s\n", (MSG)))
# else
#  define Brick7RopeModeling_Debug(MSG) ((void)0)
# endif

#endif /* Brick7RopeModeling_COMMON_H */
