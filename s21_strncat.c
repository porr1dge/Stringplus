#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  for (; *(dest + i) != '\0'; i++) {
  }
  for (s21_size_t k = 0; k < n; k++) {
    *(dest + i + k) = *(src + k);
  }
  return dest;
}