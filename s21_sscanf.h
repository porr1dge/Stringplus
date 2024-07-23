#include "s21_string.h"

int skip(char **str, char **format);
unsigned long long int s21_atod(char **, int, int *, int);
long long int s21_atovi(char **, int, int *, int);
unsigned long long int s21_atoui(char **, int, int *, int);
long double s21_atof(char **, int, int *, int);
char *atos(char *temp_s, int *lens, int width, int *correct, char *temp_result);
void sign_fun(char *str, int *len, int *width, int *sign);
void shirina(unsigned long long int *result, va_list ap, int *shi);
void ushirina(unsigned long long int *result, va_list ap, int *shi);
void shirina_f(long double *result, va_list ap, int *shi);
void find_sign(char **str, int *width, int *sign);
int check_inf_nan(char **str, long double *res, int *width, int *sign);
void s21_tolower(char *str);
int digit(int c);
int letter(int c);
int is_x(int c);
int is_e(int c);
int oct(int c);
void stars(char **temp, int *miss);
void check_base(char **, int *i, int width, int base);
