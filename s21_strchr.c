#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  char *temp = (char *)str;
  if (c == 0) result = (char *)(str + s21_strlen(str));
  for (int i = 0; *(temp + i) != '\0' && !result; i++) {
    if (*(temp + i) == c) result = (temp + i);
  }
  return result;
}
