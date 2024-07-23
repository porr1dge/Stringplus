CC = gcc
FLAGS = -Wall -Werror -Wextra -g
FILE_STRING =s21_memcmp.c s21_memset.c s21_strchr.c s21_strcspn.c s21_strlen.c \
			 s21_strncpy.c s21_strspn.c s21_to_lower.c s21_insert.c s21_memcpy.c \
			 s21_strcmp.c s21_strerror.c s21_strncat.c s21_strpbrk.c s21_strstr.c \
			 s21_to_upper.c s21_memchr.c s21_memmove.c s21_strcat.c s21_strcpy.c \
			 s21_strncmp.c s21_strrchr.c s21_strtok.c s21_trim.c s21_sprintf.c s21_sscanf.c

FILE_TEST = test_s21_memcmp.c test_s21_memset.c test_s21_strchr.c test_s21_strcspn.c test_s21_strlen.c \
			 test_s21_strncpy.c test_s21_strspn.c test_s21_to_lower.c test_s21_insert.c test_s21_memcpy.c \
			 test_s21_strcmp.c test_s21_strerror.c test_s21_strncat.c test_s21_strpbrk.c test_s21_strstr.c \
			 test_s21_to_upper.c test_s21_memchr.c test_s21_memmove.c test_s21_strcat.c test_s21_strcpy.c \
			 test_s21_strncmp.c test_s21_strrchr.c test_s21_strtok.c test_s21_trim.c test_s21_sprintf.c test_s21_sscanf.c test.c
OBJECTS=$(FILE_STRING:.c=.o)

all: s21_string.a

s21_string.a:
	$(CC) $(FLAGS) -c $(FILE_STRING)
	ar rcs s21_string.a $(OBJECTS)
	ranlib s21_string.a
	rm -rf *.o

clean:
	rm -rf s21_string.a $(OBJECTS)
	rm -rf a.out a.out* 
	rm -rf tests/test *.info *.gcno *.gcda report
	rm -rf tests/*.info tests/*.gcno tests/*.gcda

test: s21_string.a
	cd tests && $(CC) $(FLAGS) ../s21_string.a $(FILE_TEST)  -lcheck -o test
	cd tests && ./test

gcov_report: add_coverage rebuild
# $(CC) --coverage a_tests.c $(T_FILES) $(H_FILES) $(F_FILES) s21_math.a -L. s21_math.a -lcheck -lm -lpthread -o ./tests.out
# ./tests.out
#	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out

add_coverage:
	$(eval FLAGS += --coverage)

rebuild: clean test

