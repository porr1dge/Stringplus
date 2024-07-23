#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *str_begin = str;
  flags f = {0};
  va_list ap;
  va_start(ap, format);

  while (*format) {
    if (*format == '%') {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    } else {
      *str++ = *format++;
      continue;
    }

    format = check_flags(format, &f);
    format = check_width(format, &f, ap);
    format = check_precision(format, &f, ap);
    format = check_length(format, &f);

    f.spec = *format;
    format++;

    char buffer[1024] = {'\0'};
    get_arguments(buffer, f, ap);
    for (int i = 0; buffer[i]; i++, str++) *str = buffer[i];

    if (f.spec == 'c' && buffer[0] == '\0') {
      get_arguments(str, f, ap);
      *str++ = '\0';
    }

    if (f.spec == 'n') {
      int *cnt = va_arg(ap, int *);
      *cnt = str - str_begin;
    }
  }

  *str = '\0';
  va_end(ap);
  return str - str_begin;
}

const char *check_flags(const char *format, flags *f) {
  do {
    switch (*format) {
      case '0':
        f->zero = true;
        format++;
        break;
      case '-':
        f->minus = true;
        format++;
        break;
      case '+':
        f->plus = true;
        format++;
        break;
      case ' ':
        f->space = true;
        format++;
        break;
      case '#':
        f->sharp = true;
        format++;
        break;
    }
  } while (*format == '-' || *format == '+' || *format == ' ' ||
           *format == '0' || *format == '#');

  return format;
}

const char *check_width(const char *format, flags *f, va_list ap) {
  switch (*format) {
    case '*':
      format++;
      f->width = va_arg(ap, int);
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':;
      char tmp[BUFF_SIZE] = {'\0'};
      for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
      f->width = s21_atoi(tmp);
      break;
  }
  return format;
}

const char *check_precision(const char *format, flags *f, va_list ap) {
  if (*format == '.') {
    f->prec_dot = true;
    format++;
  }

  if (*format == '*') {
    f->precision = va_arg(ap, int);
    format++;
  }

  if (s21_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; s21_isdigit(*format); i++, format++) tmp[i] = *format;
    f->precision = s21_atoi(tmp);
  }
  return format;
}

const char *check_length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
    case 'L':
      f->length = 'L';
      format++;
      break;
  }
  return format;
}

void get_arguments(char *buff, flags f, va_list ap) {
  switch (f.spec) {
    case 'c':
      process_char(buff, f, ap);
      break;

    case 'i':
    case 'd':
      process_int(buff, f, ap);
      break;

    case 'e':
    case 'E':
      process_exponent(buff, f, ap);
      break;

    case 'f':
      process_float(buff, f, ap);
      break;

    case 'g':
    case 'G':
      process_float_gG(buff, f, ap);
      break;

    case 'o':
      process_octal(buff, f, ap);
      break;

    case 'p':
      process_pointer(buff, f, ap);
      break;

    case 's':
      process_string(buff, f, ap);
      break;

    case 'u':
      process_unsigned(buff, f, ap);
      break;

    case 'x':
    case 'X':
      process_hex(buff, f, ap);
      break;

    case '%':
      buff[0] = '%';
      break;
  }

  // to upper case
  if (f.spec == 'E' || f.spec == 'G' || f.spec == 'X') {
    while (*buff) {
      if (*buff >= 'a' && *buff <= 'z') *buff = *buff - 'a' + 'A';
      buff++;
    }
  }
}

void format_char(char *buff, flags f, int c) {
  if (!f.minus && f.width && !f.zero) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = ' ';
      if (i == f.width - 1) buff[i] = c;
    }
  } else if (f.width && f.zero && !f.minus) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = '0';
      if (i == f.width - 1) buff[i] = c;
    }
  } else if (f.width) {
    buff[0] = c;
    for (int i = 1; i < f.width; i++) buff[i] = ' ';
  } else {
    buff[0] = c;
  }
}

void format_wchar(char *buff, flags f, wchar_t wc) {
  if (!f.minus && f.width) {
    char tmp[BUFF_SIZE] = {'\0'};
    wcstombs(tmp, &wc, BUFF_SIZE);
    for (s21_size_t i = 0; i < f.width - s21_strlen(tmp); i++) buff[i] = ' ';
    s21_strcat(buff, tmp);
  } else if (f.width) {
    wcstombs(buff, &wc, BUFF_SIZE);
    for (int i = s21_strlen(buff); i < f.width; i++) buff[i] = ' ';
  } else {
    wcstombs(buff, &wc, BUFF_SIZE);
  }
}

void process_char(char *buff, flags f, va_list ap) {
  if (f.length == 'l') {
    wchar_t w_c;
    w_c = va_arg(ap, wchar_t);
    format_wchar(buff, f, w_c);
  } else {
    char c;
    c = va_arg(ap, int);
    format_char(buff, f, c);
  }
}

void process_int(char *buff, flags f, va_list ap) {
  int64_t value = va_arg(ap, int64_t);
  switch (f.length) {
    case 0:
      value = (int32_t)value;
      break;

    case 'h':
      value = (int16_t)value;
      break;
  }
  s21_ntoa(value, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

/*
** Перевод цифры в строку
*/

void s21_ntoa(int64_t value, char *buff, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int index = BUFF_SIZE - 2;
  bool sign = false, check_min = false;

  if (value < 0) {
    value = -value;
    sign = true;
  }
  if (value == 0) {
    tmp[index] = '0';
  } else if (value == LONG_MIN) {
    value = LONG_MAX;
    check_min = true;
  }

  while (value > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[value % base];
    value /= base;
  }
  for (int j = 0; tmp[index]; index++, j++) {
    if (sign && j == 0) buff[j++] = '-';
    buff[j] = tmp[index];
  }
  if (sign && check_min) buff[s21_strlen(buff) - 1] = '8';
}

void format_precision(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buff);

  if (buff[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.precision > len) {
    int idx;
    for (idx = sign; idx < f.precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buff[i]; i++, idx++) tmp[idx] = buff[i];

    s21_strcpy(buff, tmp);
  }

  // Точность 0 означает, что для значения 0 не записывается ни одного символа
  if (f.prec_dot && f.precision == 0 && check_integer_spec(f.spec) &&
      s21_strcmp(buff, "0") == 0)
    buff[0] = '\0';
}

bool check_integer_spec(char c) {
  char specificators[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool result = false;
  for (s21_size_t i = 0; i < sizeof(specificators); i++) {
    if (specificators[i] == c) {
      result = true;
      break;
    }
  }
  return result;
}

/*
** Обработка знака и пробела. Далее дописываем 0 или пробелы для ширины.
*/

void format_flags(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};

  if (f.plus && f.spec != 'u' && f.spec != 'o' && !f.zero && f.spec != 'x' &&
      f.spec != 'X' && f.spec != 'p') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-' && f.spec != 'u' && f.spec != 'o' &&
             f.spec != 'x' && f.spec != 'X' && f.spec != 'p') {
    tmp[0] = ' ';
    if (f.plus && f.space && (f.minus || f.zero)) tmp[0] = '+';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  }

  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff);
    if (!f.minus) {
      if (tmp[0] == ' ') {
        s21_memset(tmp, f.zero ? '0' : ' ', idx);
        if (f.zero && f.space) {
          buff[0] = '0';
          tmp[0] = ' ';
        }
        if (f.plus) tmp[0] = '+';
      } else {
        s21_memset(tmp, f.zero ? '0' : ' ', idx);
      }
      if (buff[0] == '-' && tmp[0] == '0') {
        buff[0] = tmp[0];
        tmp[0] = '-';
      }
      if (!check_integer_spec(f.spec)) {
        if (f.plus && tmp[0] != '-' && !f.space && buff[0] != '+') {
          tmp[0] = '+';
        } else if (f.plus && f.space && f.zero) {
          tmp[0] = '+';
          buff[0] = '0';
        }
      }
      s21_strcpy(tmp + idx, buff);
    } else {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buff, tmp);
  }
}

void s21_unsigned_ntoa(uint64_t value, char *buff, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int index = BUFF_SIZE - 1;

  if (value == 0) {
    buff[0] = '0';
  }

  while (value && index) {
    index--;
    tmp[index] = "0123456789abcdef"[value % base];
    value /= base;
  }
  for (int j = 0; tmp[index]; index++, j++) {
    buff[j] = tmp[index];
  }
}

void process_unsigned(char *buff, flags f, va_list ap) {
  uint64_t value = va_arg(ap, uint64_t);
  switch (f.length) {
    case 0:
      value = (uint32_t)value;
      break;

    case 'h':
      value = (uint16_t)value;
      break;

    case 'l':
      value = (uint64_t)value;
      break;
  }
  s21_unsigned_ntoa(value, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

void process_octal(char *buff, flags f, va_list ap) {
  unsigned long long value = va_arg(ap, unsigned long long);
  buff[0] = '0';
  if (value == ULONG_MAX)
    s21_strcpy(buff, "1777777777777777777777");
  else if (value)
    s21_ntoa(value, buff + f.sharp, 8);
  format_precision(buff, f);
  format_flags(buff, f);
}

bool is_all_zero(char *buff) {
  bool result = true;
  for (int i = 0; buff[i]; i++) {
    if (buff[i] != '0') {
      result = false;
      break;
    }
  }
  return result;
}

void start_ox(char *buff, flags f) {
  if (!is_all_zero(buff) || f.spec == 'p') {
    s21_memmove(buff + 2, buff, s21_strlen(buff));
    buff[0] = '0';
    buff[1] = 'x';
  }
  if (f.prec_dot && buff[2] == '0' && !buff[3]) buff[2] = '\0';
}

void process_hex(char *buff, flags f, va_list ap) {
  uint64_t value = va_arg(ap, uint64_t);
  switch (f.length) {
    case 0:
      value = (uint32_t)value;
      break;

    case 'h':
      value = (uint16_t)value;
      break;

    case 'l':
      value = (uint64_t)value;
      break;
  }
  s21_unsigned_ntoa(value, buff, 16);
  format_precision(buff, f);
  if (f.sharp) start_ox(buff, f);
  format_flags(buff, f);
}

char *reverse_array(char *str, int len) {
  int p = 0;
  for (int i = 0; i < len; i++) {
    if (*(str + i)) {
      *(str + p) = *(str + i);
      p++;
    }
  }
  return str;
}

void start_exp(char *str, int pow, char sign) {
  int len = s21_strlen(str);
  str[len] = 'e';
  str[len + 1] = sign;
  if (pow < 0) pow = -pow;
  if (pow < 10) str[len + 2] = '0';
  if (pow == 0) str[len + 3] = '0';
  char tmp[10] = {'\0'};
  int i = 8;
  while (pow) {
    tmp[i] = pow % 10 + '0';
    i--;
    pow /= 10;
  }
  s21_strcat(str, reverse_array(tmp, 10));
}

void process_exponent(char *buff, flags f, va_list ap) {
  long double value = 0;
  if (f.length == 'L') {
    value = va_arg(ap, long double);
  } else {
    value = va_arg(ap, double);
  }

  if (isinf(value)) {
    if (value < 0)
      s21_strcpy(buff, "-inf");
    else
      s21_strcpy(buff, "inf");
  } else if (isnan(value)) {
    if (value < 0)
      s21_strcpy(buff, "-nan");
    else
      s21_strcpy(buff, "nan");
  } else {
    int pow = 0;
    char sign = (int)value == 0 ? '-' : '+';

    if ((int)value - value) {
      while ((int)value == 0) {
        pow++;
        value *= 10;
      }
    } else {
      sign = '+';
    }

    while ((int)value / 10 != 0) {
      pow++;
      value /= 10;
    }

    if (!f.prec_dot) f.precision = 6;

    s21_ftoa(value, buff, f);
    start_exp(buff, pow, sign);
    format_flags(buff, f);
  }
}

void s21_ftoa(long double value, char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool sign = false;
  if (value < 0 || signbit(value)) {
    value = -value;
    sign = true;
  }
  value = roundl(value * powl(10, f.precision)) / powl(10, f.precision);
  long double lpart = 0, rpart = modfl(value, &lpart);

  char divisional[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < f.precision; i++) {
    rpart = rpart * 10;
    divisional[i] = (int)rpart + '0';
  }
  uint64_t right = roundl(rpart), left = lpart;

  if (right) {
    for (int i = s21_strlen(divisional); right || i > 0;
         right /= 10, idx--, i--)
      tmp[idx] = (int)(right % 10 + 0.5) + '0';
  } else {
    for (int i = 0; i < f.precision; idx--, i++) tmp[idx] = '0';
  }

  if ((f.prec_dot && f.precision != 0) || (int)rpart ||
      (!f.prec_dot && value == 0) || s21_strlen(divisional) || f.sharp)
    tmp[idx--] = '.';

  if (left) {
    for (; left; left /= 10, idx--) tmp[idx] = (left % 10) + '0';
  } else {
    tmp[idx] = '0';
    idx--;
  }

  for (int i = 0; tmp[idx + 1]; idx++, i++) {
    if (sign && i == 0) {
      buff[i] = '-';
      i++;
    }
    buff[i] = tmp[idx + 1];
  }
}

void process_float(char *buff, flags f, va_list ap) {
  long double value = 0;
  if (f.length == 'L') {
    value = va_arg(ap, long double);
    if (isnan(value)) value = 0.;
  } else {
    value = va_arg(ap, double);
  }

  if (!f.prec_dot) f.precision = 6;

  if (isinf(value)) {
    if (value < 0)
      s21_strcpy(buff, "-inf");
    else
      s21_strcpy(buff, "inf");
  } else if (isnan(value)) {
    if (value < 0)
      s21_strcpy(buff, "-nan");
    else
      s21_strcpy(buff, "nan");
  } else {
    s21_ftoa(value, buff, f);
    format_flags(buff, f);
  }
}

void remove_zeroes(char *buff) {
  int len = s21_strlen(buff);
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    for (int i = len - 1; buff[i] != '.'; i--) {
      if (buff[i] == '0')
        buff[i] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

double round_to_sig_digs(double value, int digits) {
  if (value == 0.0) return 0.0;
  double factor = pow(10.0, digits - ceil(log10(fabs(value))));
  return roundl(value * factor) / factor;
}

void process_float_gG(char *buff, flags f, va_list ap) {
  long double value = 0;
  if (f.length == 'L') {
    value = va_arg(ap, long double);
  } else {
    value = va_arg(ap, double);
  }

  if (!f.prec_dot || f.precision < 0) f.precision = 6;

  if (f.precision == 0) f.precision = 1;

  if (isinf(value)) {
    if (value < 0)
      s21_strcpy(buff, "-inf");
    else
      s21_strcpy(buff, "inf");
  } else if (isnan(value)) {
    if (value < 0)
      s21_strcpy(buff, "-nan");
    else
      s21_strcpy(buff, "nan");
  } else if (value == 0) {
    s21_strcpy(buff, "0");
  } else {
    int precision = f.precision;
    long double mantiss = round_to_sig_digs(value, precision), tmp = mantiss;
    int exp = 0;

    while (fabsl(tmp) >= 1.0) {
      tmp /= 10;
      exp++;
    }

    while (fabsl(tmp) < 1.0) {
      tmp *= 10;
      exp--;
    }
    if (exp >= -4 && (int)precision > exp && fabsl(value) >= 1e-4 &&
        fabsl(value) < 1e6) {
      f.precision = (unsigned)((int)precision - exp - 1);
      s21_ftoa(mantiss, buff, f);
      if (!f.sharp) remove_zeroes(buff);
    } else {
      f.precision--;
      s21_ftoa(tmp, buff, f);
      if (!f.sharp) remove_zeroes(buff);
      start_exp(buff, exp, exp > 0 ? '+' : '-');
    }
    format_flags(buff, f);
  }
}

void process_pointer(char *buff, flags f, va_list ap) {
  s21_unsigned_ntoa(va_arg(ap, uint64_t), buff, 16);
  format_precision(buff, f);
  start_ox(buff, f);
  format_flags(buff, f);
}

void format_wide_string(char *buff, flags f, wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};

  wcstombs(str, wstr, BUFF_SIZE);
  s21_strcpy(tmp, str);
  if (f.prec_dot) tmp[f.precision] = '\0';
  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);
  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void format_string(char *buff, flags f, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.prec_dot) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0 && str) {
    s21_memset(buff, f.zero ? '0' : ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else if (!str && f.prec_dot && f.precision > shift) {
    s21_strncpy(buff, "(null)", f.precision);
  } else if (!str && shift > 0 && shift <= 6) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
    if (f.precision)
      s21_strncpy(buff - f.precision + shift, "(null)", f.precision);
  } else if (!str && shift > 6) {
    if (f.precision > 6) {
      s21_memset(buff, ' ', shift);
      s21_strcpy(buff + shift - 6, tmp);
      s21_strcat(buff, "(null)");
    } else {
      s21_memset(buff, ' ', shift);
      s21_strcpy(buff + shift, tmp);
      if (f.precision) {
        s21_strncpy(buff - f.precision + shift, "(null)", f.precision);
      } else if (f.width > 6 && !f.prec_dot)
        s21_strcpy(buff + shift - 6, "(null)");
    }
  } else if (!str && !f.prec_dot) {
    s21_strcpy(buff, "(null)");
  } else {
    s21_strcpy(buff, tmp);
  }
}

void process_string(char *buff, flags f, va_list ap) {
  if (f.length == 'l') {
    wchar_t *wstr = va_arg(ap, wchar_t *);
    format_wide_string(buff, f, wstr);
  } else {
    char *str = va_arg(ap, char *);
    format_string(buff, f, str);
  }
}

int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  int overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && s21_isdigit(*str)) {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }

  if (overflow) {
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  } else {
    res *= sign;
  }
  return res;
}

int s21_isdigit(char c) { return (c >= '0' && c <= '9' ? 1 : 0); }
