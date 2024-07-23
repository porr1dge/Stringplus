#include "test.h"

START_TEST(strlen_1) {
  char *str_1 = "\0";
  ck_assert_int_eq(strlen(str_1), s21_strlen(str_1));
}
END_TEST

START_TEST(strlen_2) {
  char src[] = "aboba\0test";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(strlen_3) {
  char src[] = "aboba";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

Suite *test_s21_strlen(void) {
  Suite *s = suite_create("\033[45m-=S21_STRLEN=-\033[0m");
  TCase *tc = tcase_create("strlen_tc");

  tcase_add_test(tc, strlen_1);
  tcase_add_test(tc, strlen_2);
  tcase_add_test(tc, strlen_3);

  suite_add_tcase(s, tc);
  return s;
}
