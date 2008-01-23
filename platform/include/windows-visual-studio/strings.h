#include <string.h>
#include <windows.h>
#include <winnls.h>

inline int strncasecmp(const char* s1, const char* s2, int length)
{
  return CompareString(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, s1, -1, s2, length);
}

inline int strcasecmp(const char* s1, const char* s2)
{
  return CompareString(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, s1, -1, s2, -1);
}

