#include "test.h"

START_TEST(strerror_1) {
  for (int i = -1000; i < 150; i++) {
    char *got = s21_strerror(i);
    char *expected = strerror(i);
    ck_assert_str_eq(got, expected);
  }
}
END_TEST

START_TEST(strerror_2) {
  const char *got = s21_strerror(-1);
  char *expected = strerror(-1);
  ck_assert_str_eq(got, expected);
}
END_TEST

START_TEST(strerror_3) {
  int err_num1 = 404;
  ck_assert_pstr_eq(strerror(err_num1), s21_strerror(err_num1));
}
END_TEST

Suite *test_s21_strerror(void) {
  Suite *s = suite_create("\033[45m-=S21_STRERROR=-\033[0m");
  TCase *tc = tcase_create("strerror_tc");

  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strerror_2);
  tcase_add_test(tc, strerror_3);

  suite_add_tcase(s, tc);
  return s;
}
