#include "test.h"

START_TEST(memmove_1) {
  s21_size_t n = 3;
  char b1[1024] = "aaaa test! aaaaaa!";
  char b2[1024] = "aaaa test! aaaaaa!";
  ck_assert_pstr_eq(memmove(b1, b1 + 5, n), s21_memmove(b2, b1 + 5, n));
}
END_TEST

START_TEST(memmove_2) {
  char src[200] = "";
  char src2[200] = "";
  s21_size_t copy_kByte = 0;
  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 0;
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

START_TEST(memmove_3) {
  char src[200] = "I HATE TEEEEST!!!";
  char src2[200] = "I HATE TEEEEST!!!";
  s21_size_t copy_kByte = 17;
  char *res = src;
  char *expected = src2;
  s21_size_t check_kByte = 34;
  s21_memmove(res, src, copy_kByte);
  memmove(expected, src2, copy_kByte);
  ck_assert_mem_eq(res, expected, check_kByte);
}
END_TEST

Suite *test_s21_memmove(void) {
  Suite *s = suite_create("\033[45m-=S21_MEMMOVE=-\033[0m");
  TCase *tc = tcase_create("memmove_tc");

  tcase_add_test(tc, memmove_1);
  tcase_add_test(tc, memmove_2);
  tcase_add_test(tc, memmove_3);

  suite_add_tcase(s, tc);
  return s;
}
