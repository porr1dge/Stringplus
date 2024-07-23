#include "test.h"

START_TEST(strcat_1) {
  char b1[1024] = "OK";
  char b2[1024] = "OK";
  char str_2_2[1024] = " TEST!!";
  ck_assert_pstr_eq(strcat(b1, str_2_2), s21_strcat(b2, str_2_2));
}
END_TEST

START_TEST(strcat_2) {
  char src[] = " aboba!!!";
  char res[0 + 10] = "";
  char expected[0 + 10] = "";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST

START_TEST(strcat_3) {
  char src[] = "RTHKJI ouhdfoidfoi dfjpgnfg fdfgfgdfn gr";
  char res[5 + 53] = "Hello";
  char expected[5 + 53] = "Hello";
  s21_strcat(res, src);
  strcat(expected, src);
  ck_assert_str_eq(res, expected);
}
END_TEST
Suite *test_s21_strcat(void) {
  Suite *s = suite_create("\033[45m-=S21_STRCAT=-\033[0m");
  TCase *tc = tcase_create("strcat_tc");

  tcase_add_test(tc, strcat_1);
  tcase_add_test(tc, strcat_2);
  tcase_add_test(tc, strcat_3);

  suite_add_tcase(s, tc);
  return s;
}
