FLAGS = -Wall -Wextra -Werror

all: test gcov_report

re: clean all 

test: s21_string.a clean_obj
	gcc $(FLAGS) -lcheck s21_tests.c s21_string.a -o s21_tests
	./s21_tests

gcov_report: gcov_report_build
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

gcov_report_build: s21_string.a
	gcc $(FLAGS) --coverage -lcheck s21_tests.c s21_string.c s21_sprintf.c s21_sscanf.c -o gcov_report
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

s21_string.a: build_s21_string clean_obj

build_s21_string: s21_sprintf.c s21_sscanf.c s21_string.c
	gcc $(FLAGS) -c s21_string.c s21_sprintf.c s21_sscanf.c
	ar rc s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o
	ranlib s21_string.a

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf gcov_report
	rm -rf report

clean: clean_lib clean_test clean_obj
	rm -rf s21_tests
