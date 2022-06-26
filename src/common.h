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

# include <windows.h>

static inline LPCWSTR ATOM_AS_LPCWSTR(ATOM atom)
{ return (LPCWSTR) (((uintptr_t) 0) | atom); }

static inline LPCSTR ATOM_AS_LPCSTR(ATOM atom)
{ return (LPCSTR) (((uintptr_t) 0) | atom); }

unsigned long long Brick7RopeModeling_GetTicks(void);

# define Brick7RopeModeling_INVALID_INDEX ((size_t)-1)

#endif /* Brick7RopeModeling_COMMON_H */
