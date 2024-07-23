#include "test.h"

START_TEST(memset_1) {
  s21_size_t n = 4;
  int c = '4';
  char b1[1024] = " BEST!!";
  char b2[1024] = " BEST!!";
  ck_assert_pstr_eq(memset(b1, c, n), s21_memset(b2, c, n));
}
END_TEST

START_TEST(memset_2) {
  char res[] = "";
  char expected[] = "";
  char replace = '\0';
  s21_size_t n = 0;
  s21_memset(res, replace, n);
  memset(expected, replace, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(memset_3) {
  char res[] = "aboba";
  char expected[] = "aboba";
  char replace = 'A';
  s21_size_t n = 3;
  s21_memset(res, replace, n);
  memset(expected, replace, n);
  ck_assert_str_eq(res, expected);
}
END_TEST

Suite *test_s21_memset(void) {
  Suite *s = suite_create("\033[45m-=S21_MEMSET=-\033[0m");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, memset_1);
  tcase_add_test(tc, memset_2);
  tcase_add_test(tc, memset_3);

  suite_add_tcase(s, tc);
  return s;
}
