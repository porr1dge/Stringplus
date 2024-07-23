#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

#include "s21_string.h"

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool sharp;
  bool prec_dot;
  int precision;
  int width;
  char length;
  char spec;
} flags;

/*Parser*/
const char *check_flags(const char *format, flags *f);
const char *check_width(const char *format, flags *f, va_list ap);
const char *check_precision(const char *format, flags *f, va_list ap);
const char *check_length(const char *format, flags *f);

/*Process functions*/
void get_arguments(char *buff, flags f, va_list ap);
void process_int(char *buff, flags f, va_list ap);
void process_unsigned(char *buff, flags f, va_list ap);
void process_octal(char *buff, flags f, va_list ap);
void process_char(char *buff, flags f, va_list ap);
void process_float(char *buff, flags f, va_list ap);
void process_float_gG(char *buff, flags f, va_list ap);
void process_hex(char *buff, flags f, va_list ap);
void process_exponent(char *buff, flags f, va_list ap);
void process_pointer(char *buff, flags f, va_list ap);
void process_string(char *buff, flags f, va_list ap);

/*Format functions*/
void format_flags(char *buff, flags f);
void format_precision(char *buff, flags f);
void format_char(char *buff, flags f, int c);
void format_wchar(char *buff, flags f, wchar_t wc);
void format_wide_string(char *buff, flags f, wchar_t *wstr);
void format_string(char *buff, flags f, char *str);

/*Helper functions*/
void s21_unsigned_ntoa(uint64_t value, char *buff, int base);
void s21_ntoa(int64_t value, char *buff, int base);
void s21_ftoa(long double value, char *buff, flags f);
bool is_all_zero(char *buff);
char *reverse_array(char *str, int len);
void start_ox(char *buff, flags f);
void start_exp(char *str, int pow, char sign);
bool check_integer_spec(char c);
double round_to_sig_digs(double value, int digits);
void remove_zeroes(char *buff);
int s21_isdigit(char c);
int s21_atoi(const char *str);

#endif  // SRC_S21_STRING_H_
