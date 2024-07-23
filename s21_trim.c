#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = S21_NULL;
  if (src) {
    int len = s21_strlen(src);
    if (!trim_chars) {
      res = (char *)malloc((len + 1) * sizeof(char));
      if (res) s21_strcpy(res, src);
    } else {
      int len_start = s21_strspn(src, trim_chars);
      int len_end = 0;
      if (len_start < len) {
        for (int i = len; i > 0; i--) {
          if (s21_strchr(trim_chars, src[i - 1]))
            len_end++;
          else
            i = 1;
        }
      }
      res = (char *)malloc((len - len_start - len_end + 1) * sizeof(char));
      if (res) {
        char *temp = res;
        for (int i = len_start; i < len - len_end; i++) {
          *temp++ = src[i];
        }
        *temp = '\0';
        temp = S21_NULL;
      }
    }
  }
  return res;
}