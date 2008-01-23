#include <shlwapi.h>

inline int strncasecmp(const char* s1, const char* s2, int length)
{
  return StrCmpNI(s1, s2, length);
}

inline int strcasecmp(const char* s1, const char* s2)
{
  return StrCmpI(s1, s2);
}

