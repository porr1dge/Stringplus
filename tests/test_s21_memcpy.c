#include "test.h"

START_TEST(memcpy_1) {
  s21_size_t n = 5;
  char b1[1024] = "";
  char b2[1024] = "";
  char str_2_2[1024] = "aboba t\0est!!";
  ck_assert_pstr_eq(memcpy(b1, str_2_2, n), s21_memcpy(b2, str_2_2, n));
}
END_TEST

START_TEST(memcpy_2) {
  char src[] = "aboba";
  s21_size_t kByte = 0;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);
  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

START_TEST(memcpy_3) {
  char src[] = "123";
  s21_size_t kByte = 1;
  char res[kByte + 8];
  char expected[kByte + 8];
  s21_memcpy(res, src, kByte);
  memcpy(expected, src, kByte);
  ck_assert_mem_eq(res, expected, kByte);
}
END_TEST

Suite *test_s21_memcpy(void) {
  Suite *s = suite_create("\033[45m-=S21_MEMCPY=-\033[0m");
  TCase *tc = tcase_create("memcpy_tc");

  tcase_add_test(tc, memcpy_1);
  tcase_add_test(tc, memcpy_2);
  tcase_add_test(tc, memcpy_3);

  suite_add_tcase(s, tc);
  return s;
}
