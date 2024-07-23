#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  int correct = 1, cor = 1;
  for (s21_size_t i = 0; *(str1 + i) && correct; i++) {
    correct = 0;
    for (s21_size_t k = 0; *(str2 + k) && cor; k++) {
      if (*(str1 + i) == *(str2 + k)) {
        correct = 1, cor = 0, result++;
      }
    }
    cor = 1;
  }
  return result;
}