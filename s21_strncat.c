#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int l = s21_strlen(src);

  for (s21_size_t i = 0; i < n && src[i] != '\0'; i += 1) {
    dest[l + i] = src[i];
    dest[l + i + 1] = '\0';
  }

  for (s21_size_t i = 0, n = s21_strlen(src); i < n && src[i] != '\0'; i += 1) {
    dest[l + i] = src[i];
    dest[l + i + 1] = '\0';
  }

  return dest;
}