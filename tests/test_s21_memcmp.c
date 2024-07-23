#include "test.h"

START_TEST(memcmp_1) {
  s21_size_t n = 3;
  void *str_1 = "Tesssst!";
  void *str_2 = "Tesssst!";
  ck_assert_int_eq(memcmp(str_1, str_2, n), s21_memcmp(str_1, str_2, n));
}
END_TEST

START_TEST(memcmp_2) {
  char str1[] = "1";
  char str2[] = "1234";
  int n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcmp_3) {
  char str1[] = "aboba";
  char str2[] = "Aboba";
  int n = 1;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

Suite *test_s21_memcmp(void) {
  Suite *s = suite_create("\033[45m-=S21_MEMCMP=-\033[0m");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, memcmp_1);
  tcase_add_test(tc, memcmp_2);
  tcase_add_test(tc, memcmp_3);

  suite_add_tcase(s, tc);
  return s;
}
