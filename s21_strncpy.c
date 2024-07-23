#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *result = S21_NULL;
  if (dest != S21_NULL || src != S21_NULL) {
    s21_size_t i = 0;
    result = dest;
    for (; i < n && *(src + i) != '\0'; i++) {
      *(dest + i) = *(src + i);
    }
    for (; i < n; i++) {
      *(dest + i) = '\0';
    }
  }

  return result;
}
