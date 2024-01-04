#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int Length = s21_strlen(str) + 1;
  char *answer = S21_NULL;

  for (int i = 0; i < Length && answer == S21_NULL; i += 1)
    if (str[i] == c) answer = (char *)str;

  return answer;
}