#include "s21_string.h"

char *s21_strtok(char *str, const char *delim){
     static char* currentPosition = S21_NULL;
    if (str != S21_NULL) {
        currentPosition = str;
    }

    if (currentPosition == S21_NULL || *currentPosition == '\0') {
        return S21_NULL;
    }

    char* tokenStart = currentPosition;
    char* tokenEnd = strpbrk(currentPosition, delimiters);

    if (tokenEnd == NULL) {
        currentPosition = strchr(currentPosition, '\0');
    } else {
        *tokenEnd = '\0';
        currentPosition = tokenEnd + 1;
    }

    return tokenStart;
}
