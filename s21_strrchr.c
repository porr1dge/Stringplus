#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;
  int i = 0;
  for (; *(str + i); i++) {
    if (*((unsigned char *)str + i) == c) result = (char *)(str + i);
  }
  if (c == 0 && *(str + i) == 0) result = (char *)(str + i);
  return result;
}
