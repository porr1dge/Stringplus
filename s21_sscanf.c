#include "s21_sscanf.h"
int skip(char **str, char **format) {
  char space[7] = " \f\n\r\t\v";
  char del[8] = " \f\n\r\t\v\%";
  int correct = 0;
  while ((**format && **format != 37) && !correct) {
    int len = 0;
    if (s21_strchr(space, **format) != NULL) {
      len = (int)s21_strspn(*format, space);
      *format += len;
      len = (int)s21_strspn(*str, space);
      *str += len;
    }
    len = (int)s21_strcspn(*format, del);
    if (!s21_strncmp(*str, *format, len)) {
      *str += len;
      *format += len;
    } else {
      correct = 1;
    }
  }
  return correct;
}
int s21_sscanf(const char *str, const char *format, ...) {
  int result = 0, lens = 0, correct = 0, width = 0;
  char *temp_s = (char *)str, *temp_f = (char *)format;
  char space[7] = " \f\n\r\t\v";
  va_list ap;
  int bag = 1;
  int miss = 0;
  //  printf("gp_offset -  %u \nfp_offset - %u\n", ap->gp_offset,
  //  ap->fp_offset); printf("overflow_arg_area - %p\nreg_save_area - %p\n",
  //        ap->overflow_arg_area, ap->reg_save_area);
  va_start(ap, format);

  while (*temp_f && !correct) {
    correct = skip(&temp_s, &temp_f);
    if ((bag && *temp_s) || (bag && *temp_f == '%')) result = 0;
    // printf("%s\n%s\n", temp_s, temp_f);

    if (*temp_f == 37) {
      temp_f++;
      stars(&temp_f, &miss);
      if (*temp_f >= 48 && *temp_f <= 57) {
        width = s21_atod(&temp_f, 0, &correct, 117);
      }
      stars(&temp_f, &miss);
    }

    int shi = 0;
    if (*temp_f == 'h' && *(temp_f + 1) == 'h') {
      shi = 1, temp_f += 2;
    } else if (*temp_f == 'h')
      shi = 2, temp_f++;
    else if (*temp_f == 'l' && *(temp_f + 1) == 'l')
      shi = 4, temp_f += 2;
    else if (*temp_f == 'l')
      shi = 3, temp_f++;
    else if (*temp_f == 'L')
      shi = 5, *temp_f++;
    if (!correct) {
      // printf("%s\n%s\n", temp_s, temp_f);
      unsigned long long int sum = 0;
      long double sum_f = 0;
      unsigned base = 0;
      char temp_result[1024] = {0};
      int e = 0;
      int l = s21_strlen(temp_s);
      switch (*temp_f) {
        case 'c':
          if (*temp_s) {
            if (!miss) {
              *va_arg(ap, char *) = *temp_s;
              result++;
            } else {
              miss = 0, bag = 2;
            }
            if (width == 0)
              temp_s += 1;
            else if (width <= l)
              temp_s += width;
            else
              temp_s += l;
          } else {
            correct = 1;
            if (bag) result = -1;
          }
          break;
        case 'd':
        case 'u':
          temp_s += s21_strspn(temp_s, space);
          sum = s21_atod(&temp_s, width, &correct, *temp_f);
          if (!correct) {
            if (!miss) {
              if (*temp_f == 'u') {
                ushirina(&sum, ap, &shi);
              } else {
                shirina(&sum, ap, &shi);
              }
              result++;
            } else
              miss = 0, bag = 2;
          } else if (bag && !*temp_s)
            result = -1, bag = 0;
          break;
        case 'i':
        case 'o':
        case 'x':
        case 'X':
          if (*temp_f == 'i')
            base = 10;
          else if (*temp_f == 'o')
            base = 8;
          else
            base = 16;
          temp_s += s21_strspn(temp_s, space);
          if (*temp_f == 'i')
            sum = s21_atovi(&temp_s, width, &correct, base);
          else
            sum = s21_atoui(&temp_s, width, &correct, base);
          if (!correct) {
            if (!miss) {
              if (*temp_f == 'i') {
                shirina(&sum, ap, &shi);
              } else {
                ushirina(&sum, ap, &shi);
              }
              result++;
            } else
              miss = 0, bag = 2;
          } else if (bag && !*temp_s)
            result = -1, bag = 0;
          break;
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'f':
          e = 1;
          temp_s += s21_strspn(temp_s, space);
          sum_f = s21_atof(&temp_s, width, &correct, e);
          if (!correct) {
            if (!miss) {
              shirina_f(&sum_f, ap, &shi);
              result++;
            } else
              miss = 0, bag = 2;
          } else if (bag && !*temp_s)
            result = -1, bag = 0;
          break;
        case 's':
          temp_s += s21_strspn(temp_s, space);
          atos(temp_s, &lens, width, &correct, temp_result);
          temp_s += lens;
          lens = 0;
          if (!correct) {
            if (!miss) {
              // temp = va_arg(ap, char *);
              s21_strcpy(va_arg(ap, char *), temp_result);
              result++;
            } else
              miss = 0, bag = 2;
          } else if (bag && !*temp_s)
            result = -1, bag = 0;
          break;
        case 'p':
          temp_s += s21_strspn(temp_f, space);
          base = 16;
          sum = s21_atoui(&temp_s, width, &correct, base);
          if (!correct) {
            if (!miss) {
              shi = 3;
              ushirina(&sum, ap, &shi);
              result++;
            } else
              miss = 0, bag = 2;
          } else if (bag && !*temp_s)
            result = -1, bag = 0;
          break;
        case 'n':
          if (!miss) {
            sum = temp_s - str;
            shirina(&sum, ap, &shi);
          } else
            miss = 0, bag = 2;
          break;
        case '%':
          temp_s += s21_strspn(temp_s, space);
          if (*temp_s == '%')
            temp_s++;
          else
            correct = 1;
          miss = 0, bag = 2;
          break;
        default:
          correct = 1;
          break;
      }
      if (*temp_f) temp_f++;
      width = 0;
    }
    if (result) bag = 0;
    if (bag != 2) bag = 0;
  }
  va_end(ap);

  return result;
}
char *atos(char *temp_s, int *lens, int width, int *correct,
           char *temp_result) {
  char space[7] = " \f\n\r\t\v";
  int len = s21_strcspn(temp_s, space);

  if (width == 0) width = INT_MAX;
  int i = 0;
  for (; *(temp_s + i) && i < len && i < width; i++, (*lens)++) {
    *(temp_result + i) = *(temp_s + i);
  }
  *(temp_result + i) = '\0';
  if (i == 0) *correct = 1;
  return temp_result;
}

unsigned long long int s21_atod(char **str, int width, int *correct, int c) {
  unsigned long long int result = 0;
  int sign = 1, base = 10;

  if (width == 0) width = INT_MAX;
  find_sign(str, &width, &sign);

  int i = 0;
  int full = 0;
  for (; i < width && digit(**str); (*str)++, i++) {
    if (!full && ((c == 117 && result * base + (**str - 48) >= result) ||
                  (c == 100 && result * base + (**str - 48) <= LONG_MAX)))
      result = result * base + (**str - 48);
    else if (!full) {
      if (c == 117) {
        result = ULONG_MAX;
      } else if (c == 100) {
        sign == 1 ? (result = LONG_MAX) : (result = LONG_MIN);
      }
      full = 1;
    }
  }
  if (i == 0) *correct = 1;

  return full ? result : result * sign;
}
long long int s21_atovi(char **str, int width, int *correct, int base) {
  long long int result = 0;
  int sign = 1, temp = 0;

  if (width == 0) width = INT_MAX;
  find_sign(str, &width, &sign);

  int i = 0;
  check_base(str, &i, width, base);

  if (i == 1 && base == 10)
    base = 8;
  else if (i == 2)
    base = 16;

  int full = 0;
  if (base != 16) {
    for (; i < width && (**str >= 48 && **str <= 48 + base - 1);
         (*str)++, i++) {
      if (!full && result * base + (**str - 48) >= result)
        result = result * base + (**str - 48);
      else if (!full) {
        sign == 1 ? (result = LONG_MAX) : (result = LONG_MIN);
        full = 1;
      }
    }
  } else {
    for (; i < width && (digit(**str) || letter(**str)); (*str)++, i++) {
      if (digit(**str)) {
        temp = (**str) - 48;
      } else {
        temp = (**str) % 32 + 9;
      }

      if (!full && result * base + temp >= result) {
        result = result * base + temp;
      } else if (!full) {
        sign == 1 ? (result = LONG_MAX) : (result = LONG_MIN);
        full = 1;
      }
    }
  }
  if (i == 0) *correct = 1;

  return full ? result : result * sign;
}

unsigned long long int s21_atoui(char **str, int width, int *correct,
                                 int base) {
  unsigned long long int result = 0;
  int sign = 1, temp = 0;

  if (width == 0) width = INT_MAX;
  find_sign(str, &width, &sign);

  int i = 0;
  check_base(str, &i, width, base);

  if (i == 1 && base == 10)
    base = 8;
  else if (i == 2)
    base = 16;

  int full = 0;

  if (base != 16) {
    for (; i < width && (**str >= 48 && **str <= 48 + base - 1);
         (*str)++, i++) {
      if (!full && result * base + (**str - 48) >= result)
        result = result * base + (**str - 48);
      else if (!full) {
        result = ULONG_MAX;
        full = 1;
      }
    }
  } else {
    for (; i < width && (digit(**str) || letter(**str)); (*str)++, i++) {
      if (digit(**str)) {
        temp = (**str) - 48;
      } else {
        temp = (**str) % 32 + 9;
      }
      if (!full && result * base + temp >= result) {
        result = result * base + temp;
      } else if (!full) {
        result = ULONG_MAX;
        full = 1;
      }
    }
  }
  if (i == 0) *correct = 1;

  return full ? result : result * sign;
}
long double s21_atof(char **str, int width, int *correct, int e) {
  long double result = 0, del = 1;  // inf = 1.0/0.0, nan = 0.0/0.0;
  int point = 0, sign = 1, base = 10, check = 0, temp = 0;
  unsigned long long int p = 1;

  if (width == 0) width = INT_MAX;
  find_sign(str, &width, &sign);
  check = check_inf_nan(str, &result, &width, &sign);

  int i = 0;
  if (!check) {
    if (**str == '0' && width > 0) {
      i = 1;
      (*str)++;
      if (is_x(**str) && width - i > 0) {
        i = 2;
        base = 16;
        e = 0;
        if (width - i > 0 && (letter(*(*str + 1)) || digit(*(*str + 1)))) {
          (*str)++;
        } else if (width - i > 0 && *(*str + 1) == 46) {
          point = 1, i = 3;
          if (width - i > 0 && (letter(*(*str + 2)) || digit(*(*str + 2))))
            (*str) += 2;
        }
      }
    }
    for (; i < width && (e == 0 || (e == 1 && !is_e(**str))) &&
           (((digit(**str)) || (letter(**str) && base == 16)) ||
            (**str == 46 && point == 0));
         i++, (*str)++) {
      if (point < 2) {
        if (**str != '.') {
          if (digit(**str)) {
            temp = (**str) - 48;
          } else {
            temp = (**str) % 32 + 9;
          }
          result = result * base + temp;
          if (point == 1) del *= base;
        } else {
          point++;
        }
      } /*else {
        p *= base;
        // printf("%llu\n", p);
        if (digit(*(str + i))) {
          result += (long double)(*(str + i) - 48) / p;
          // printf("%d\n%.30Lf\n",(*(str + i) - 48), (long double)(*(str + i) -
          // 48) / p);
        } else {
          result += (long double)(*(str + i) % 32 + 9) / p;
        }
      }*/
      // printf("%.25Lf\n", result);
    }
    result /= del;
    result *= sign;

    if (point == 1 && i == 1) *correct = 1;
    if (i < width && is_e(**str)) {
      if (((*(*str + 1) == 43 || *(*str + 1) == 45) && digit(*(*str + 2)) &&
           i + 2 < width) ||
          (i + 1 < width && digit(*(*str + 1)))) {
        (*str)++, i++;
        sign = 0;
        find_sign(str, &width, &sign);
        if (sign != 0)
          i++;
        else
          sign = 1;

        p = 0;
        for (; i < width && digit(**str); (*str)++, i++) {
          p = p * 10 + (**str - 48);
        }
        for (; p > 0; p--) {
          if (sign == -1) {
            result /= 10;
            if (result == 0) p = 1;
          } else {
            result *= 10;
            if (isinf(result)) p = 1;
            if (result == 0) p = 1;
          }
        }
      }
    }
    if (i == 0 && check == 0) *correct = 1;
  }
  return result;
}
void shirina_f(long double *result, va_list ap, int *shi) {
  if (*shi == 0 || *shi == 2) {
    *va_arg(ap, float *) = (float)*result;
  } else if (*shi == 3) {
    *va_arg(ap, double *) = (double)*result;
  } else if (*shi == 4) {
    va_arg(ap, float *);
  } else if (*shi == 5) {
    *va_arg(ap, long double *) = *result;
  }
  *shi = 0;
}

void shirina(unsigned long long int *result, va_list ap, int *shi) {
  if (*shi == 0) {
    *va_arg(ap, int *) = (int)*result;
  } else if (*shi == 1) {
    *va_arg(ap, char *) = (char)*result;
  } else if (*shi == 2) {
    *va_arg(ap, short int *) = (short int)*result;
  } else if (*shi == 3) {
    *va_arg(ap, long int *) = (long int)*result;
  } else if (*shi == 4) {
    *va_arg(ap, long long int *) = (long long int)*result;
  }
  *shi = 0;
}
void ushirina(unsigned long long int *result, va_list ap, int *shi) {
  if (*shi == 0) {
    *va_arg(ap, unsigned int *) = (unsigned int)*result;
  } else if (*shi == 1) {
    *va_arg(ap, unsigned char *) = (unsigned char)*result;
  } else if (*shi == 2) {
    *va_arg(ap, unsigned short int *) = (unsigned short int)*result;
  } else if (*shi == 3) {
    *va_arg(ap, unsigned long int *) = (unsigned long int)*result;
  } else if (*shi == 4) {
    *va_arg(ap, unsigned long long int *) = (unsigned long long int)*result;
  }
  *shi = 0;
}
int check_inf_nan(char **str, long double *res, int *width, int *sign) {
  char temp[20] = {0};
  int check = 1;
  s21_strncpy(temp, *str, 10);
  s21_tolower(temp);

  if (*width > 2 && !s21_strncmp(temp, "nan", 3)) {
    *res = 0.0 / 0.0;
    *str += 3;
    *width -= 3;
  } else if (*width > 7 && !s21_strncmp(temp, "infinity", 8)) {
    *res = 1.0 / 0.0;
    *str += 8;
    *width -= 8;
  } else if (*width > 2 && !s21_strncmp(temp, "inf", 3)) {
    *res = 1.0 / 0.0;
    *str += 3;
    *width -= 3;
  } else {
    check = 0;
  }
  if (check) *res *= *sign;

  return check;
}

void s21_tolower(char *str) {
  for (int i = 0; *(str + i); i++) {
    if (*(str + i) >= 65 && *(str + i) <= 90) *(str + i) += 32;
  }
}
void stars(char **temp, int *miss) {
  if (**temp == '*') *miss = 1;
  while (**temp == '*') (*temp)++;
}
int oct(int c) { return (c >= 48 && c <= 55) ? 1 : 0; }
int digit(int c) { return (c >= 48 && c <= 57) ? 1 : 0; }
int letter(int c) {
  return ((c >= 65 && c <= 70) || (c >= 97 && c <= 102)) ? 1 : 0;
}
int is_x(int c) { return ((c == 88) || (c == 120)) ? 1 : 0; }
int is_e(int c) { return ((c == 69) || (c == 101)) ? 1 : 0; }
void check_base(char **str, int *i, int width, int base) {
  if (**str == '0' && width > 0) {
    *i = 1;
    (*str)++;
    if (is_x(**str) && width - *i > 0 && base != 8) {
      *i = 2;
      if (width - *i > 0 && (letter(*(*str + 1)) || digit(*(*str + 1))))
        (*str)++;
    }
  }
}
void find_sign(char **str, int *width, int *sign) {
  if (**str == '-') {
    *sign = -1;
    (*str)++;
    (*width)--;
  } else if (**str == '+') {
    (*str)++;
    (*width)--;
    *sign = 1;
  }
}
