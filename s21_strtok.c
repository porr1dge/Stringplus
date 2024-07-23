#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *temp = S21_NULL;
  char *result = S21_NULL;

  if (str != S21_NULL) temp = str;

  if (temp != S21_NULL) {
    result = temp + s21_strspn(temp, delim);
    temp = result;
    if (*result) {
      s21_size_t k = 0, i = 0;
      k = s21_strcspn(temp, delim);
      i = s21_strlen(temp);
      temp = temp + k;
      if (k < i) {
        temp[0] = '\0';
        temp = temp + 1;
      }
    } else {
      temp = S21_NULL;
      result = S21_NULL;
    }
  }
  return result;
}