rebuild: clean s21_grep

s21_grep: s21_grep_main.o s21_grep_func.o
	gcc -Wall -Wextra -Werror s21_grep_main.o s21_grep_func.o -o s21_grep
	rm -rf *.o

s21_grep_main.o: s21_grep_main.c clean_obj
	gcc -Wall -Wextra -Werror -c s21_grep_main.c

s21_grep_func.o: s21_grep_func.c clean_obj
	gcc -Wall -Wextra -Werror -c s21_grep_func.c

s21_grep_testfunc: rebuild
	sh test_func_grep.sh s21_grep

s21_grep_testleak: rebuild
	sh test_leak_grep.sh s21_grep

clean_obj:
	rm -rf *.o

clean: clean_obj
	rm -rf s21_grep