#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = S21_NULL;

  for (s21_size_t i = 0; i < n; i++) {
    if ((*((unsigned char *)str + i)) == (unsigned char)c) {
      result = (char *)str + i;
      i = n;
    }
  }
  return result;
}