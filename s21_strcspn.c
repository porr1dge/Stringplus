#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  int correct = 1;
  for (s21_size_t i = 0; correct; i++) {
    result = i;
    int cor = 1;
    for (s21_size_t k = 0; correct && cor; k++) {
      if (*(str1 + i) == *(str2 + k)) correct = 0;
      if (*(str2 + k) == '\0') cor = 0;
    }
  }
  return result;
}