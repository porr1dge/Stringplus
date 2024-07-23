#ifndef SRC_TESTS_TEST_H
#define SRC_TESTS_TEST_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../s21_string.h"

Suite *test_s21_memchr(void);
Suite *test_s21_memcmp(void);
Suite *test_s21_memcpy(void);
Suite *test_s21_memmove(void);
Suite *test_s21_memset(void);
Suite *test_s21_strcat(void);
Suite *test_s21_strncat(void);
Suite *test_s21_strchr(void);
Suite *test_s21_strcmp(void);
Suite *test_s21_strncmp(void);
Suite *test_s21_strcpy(void);
Suite *test_s21_strncpy(void);
Suite *test_s21_strcspn(void);
Suite *test_s21_strerror(void);
Suite *test_s21_strlen(void);
Suite *test_s21_strpbrk(void);
Suite *test_s21_strrchr(void);
Suite *test_s21_strspn(void);
Suite *test_s21_strstr(void);
Suite *test_s21_strtok(void);

Suite *test_s21_sscanf_c(void);
Suite *test_s21_sprintf(void);

Suite *test_s21_to_upper(void);
Suite *test_s21_to_lower(void);
Suite *test_s21_insert(void);
Suite *test_s21_trim(void);
Suite *test_s21_sscanf(void);

#endif  // SRC_TESTS_TEST_H
