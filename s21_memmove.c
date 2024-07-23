#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest;
  const char *from = (const char *)src;

  char *tmp = (char *)malloc(sizeof(char) * n);
  if (S21_NULL == tmp) {
    return S21_NULL;
  } else {
    s21_size_t i = 0;
    for (i = 0; i < n; ++i) {
      *(tmp + i) = *(from + i);
    }

    for (i = 0; i < n; ++i) {
      *(to + i) = *(tmp + i);
    }
    free(tmp);
  }
  return dest;
}