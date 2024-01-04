#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t counter = 0;

    for (const char *right = str1; *right; right++) {
        unsigned short found = 0;
        for (const char *left = str2; *left; left++) {
            if (*right == *left) {
                counter++;
                found = 1;
                break;
            }
        }
        if (!found)
            break;
    }
    return counter;
}