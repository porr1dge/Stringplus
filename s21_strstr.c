#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = (char *)haystack;
  if (*needle) {
    int correct = 1;
    result = S21_NULL;
    for (s21_size_t i = 0; *(haystack + i) && correct; i++) {
      for (s21_size_t k = 0; *(needle + k) && correct; k++) {
        if (*(haystack + i + k) != *(needle + k)) correct = 0;
      }
      if (correct == 1) {
        result = (char *)(haystack + i);
        correct = 0;
      } else {
        correct = 1;
      }
    }
  }
  return result;
}