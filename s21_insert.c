#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = S21_NULL;

  if (src) {
    s21_size_t len = s21_strlen(src);
    if (len >= start_index && str) {
      s21_size_t len2 = s21_strlen(str);
      res = (char *)malloc((len + len2 + 1) * sizeof(char));
      if (res) {
        char *temp = res;
        for (s21_size_t i = 0; i < len; i++) {
          if (i == start_index) {
            while (*str) {
              *temp++ = *str++;
            }
          }
          *temp++ = src[i];
        }
        *temp = '\0';
        temp = S21_NULL;
      }
    }
  }
  return res;
}