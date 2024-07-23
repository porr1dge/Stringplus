#include "test.h"

START_TEST(strncat_1) {
  s21_size_t n3 = 2;
  char b1[1024] = "123";
  char b2[1024] = "123";
  char str_3_2[1024] = " boba";
  ck_assert_pstr_eq(strncat(b1, str_3_2, n3), s21_strncat(b2, str_3_2, n3));
}
END_TEST

START_TEST(strncat_2) {
  char src[] = "";
  char res[] = "";
  char expected[] = "";
  s21_size_t n_byte = 0;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(strncat_3) {
  char src[] = "abboba";
  char res[10] = "qw";
  char expected[10] = "qw";
  s21_size_t n_byte = 5;
  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);
  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

Suite *test_s21_strncat(void) {
  Suite *s = suite_create("\033[45m-=S21_STRNCAT=-\033[0m");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, strncat_1);
  tcase_add_test(tc, strncat_2);
  tcase_add_test(tc, strncat_3);

  suite_add_tcase(s, tc);
  return s;
}
