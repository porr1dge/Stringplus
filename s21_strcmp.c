#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  for (int i = 0;
       !(result = *(str1 + i) - *(str2 + i)) && (i < (int)s21_strlen(str1));
       i++) {
  }
  return result;
}