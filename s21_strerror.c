#include "s21_string.h"

char *s21_strerror(int errnum) {
#ifdef STRERR
  static char stringerror[SIZE_ERROR][MAX] = STRERR;
  static char unknown[MAX] = UNKNOWN;
#else
#error Dont define list of error(STRERR)
#endif
  if (errnum < 0 || errnum >= SIZE_ERROR) {
    s21_sprintf(unknown + SIZE_FOR_COPY, "%d", errnum);
  }
  return errnum < SIZE_ERROR && errnum >= 0 ? stringerror[errnum] : unknown;
}
