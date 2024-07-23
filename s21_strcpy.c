#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *result = S21_NULL;
  if (dest != S21_NULL && src != S21_NULL) {
    int i = 0;
    result = dest;
    for (; *(src + i) != '\0'; i++) {
      *(dest + i) = *(src + i);
    }
    *(dest + i) = '\0';
  }
  return result;
}
