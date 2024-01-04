#include "s21_string.h"
char *strpbrk(const char *str, const char *str2) {
  while (*str) {
    for (const char *p = str2; *p; ++p) {
      if (*str == *p) {
        return (char *)str;
      }
    }
    ++str;
  }

  return S21_NULL;
}