#include "s21_string.h"

char *strrchr(const char *str, int c) {
  const char *p = str;

  while (*p) {
    if (*p == c) {
      return p;
    }
    p++;
  }

  if (c == '\0') {
    return p;
  }

  return S21_NULL;
}