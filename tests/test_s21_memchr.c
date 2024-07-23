#include "test.h"

START_TEST(memchr_1) {
  char str[] = "Hello S\0CHOOL\0";
  ck_assert_pstr_eq(memchr(str, 'r', 5), s21_memchr(str, 'r', 5));
}
END_TEST

START_TEST(memchr_2) {
  char str[] = "ABOBAabobavich";
  ck_assert_pstr_eq(memchr(str, 's', 6), s21_memchr(str, 's', 6));
}
END_TEST

START_TEST(memchr_3) {
  int array[] = {1, 2, 3, 666, 5, 99, 100};
  s21_size_t n_byte = sizeof(int) * 7;
  int find_byte = 666;
  ck_assert_ptr_eq(s21_memchr(array, find_byte, n_byte),
                   memchr(array, find_byte, n_byte));
}
END_TEST

Suite *test_s21_memchr(void) {
  Suite *s = suite_create("\033[45m-=S21_MEMCHR=-\033[0m");
  TCase *tc = tcase_create("memchr_tc");

  tcase_add_test(tc, memchr_1);
  tcase_add_test(tc, memchr_2);
  tcase_add_test(tc, memchr_3);

  suite_add_tcase(s, tc);
  return s;
}
