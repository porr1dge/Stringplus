#include "test.h"

START_TEST(strspn_1) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_2) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

START_TEST(strspn_3) {
  char src[] = "1234567890";
  char res[] = "0987654321";
  ck_assert_int_eq(s21_strspn(res, src), strspn(res, src));
}
END_TEST

Suite *test_s21_strspn(void) {
  Suite *s = suite_create("\033[45m-=S21_STRSPN=-\033[0m");
  TCase *tc = tcase_create("strspn_tc");

  tcase_add_test(tc, strspn_1);
  tcase_add_test(tc, strspn_2);
  tcase_add_test(tc, strspn_3);

  suite_add_tcase(s, tc);
  return s;
}
