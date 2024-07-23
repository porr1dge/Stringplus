#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int correct = 1;
  char *result = S21_NULL;
  for (int i = 0; *(str1 + i) && correct; i++) {
    for (int k = 0; *(str2 + k) && correct; k++) {
      if (*(str1 + i) == *(str2 + k)) {
        correct = 0;
        result = (char *)(str1 + i);
      }
    }
  }
  return result;
}