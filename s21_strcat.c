#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int destLen = s21_strlen(dest);
  int srcLen = s21_strlen(src);

  for (int i = 0; i <= srcLen; i += 1) dest[destLen + i] = src[i];

  return dest;
}