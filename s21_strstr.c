#include "s21_string.h"
char *strstr(const char *haystack, const char *needle) {
  if (!needle || !*needle) {
    return (char *)haystack;
  }

  s21_size_t needle_len = s21_strlen(needle);

  for (const char *p = haystack; *p; ++p) {
    if (*p == needle[0]) {
      if (s21_memcmp(p, needle, needle_len) == 0) {
        return (char *)p;
      }
    }
  }

  return S21_NULL;
}