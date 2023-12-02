rebuildgrep: cleangrep s21_grep

s21_grep: s21_grep_main.o s21_grep_func.o
	gcc -Wall -Wextra -Werror s21_grep_main.o s21_grep_func.o -o grep/s21_grep
	rm -rf *.o

s21_grep_main.o: grep/s21_grep_main.c clean_objgrep
	gcc -Wall -Wextra -Werror -c grep/s21_grep_main.c

s21_grep_func.o: grep/s21_grep_func.c clean_objgrep
	gcc -Wall -Wextra -Werror -c grep/s21_grep_func.c

clean_objgrep:
	rm -rf *.o

cleangrep: clean_objgrep
	rm -rf grep/s21_grep

rebuildcat: cleancat s21_cat

s21_cat: cat.o catfunc.o
	gcc -Wall -Wextra -Werror cat.o catfunc.o -o cat/s21_cat
	rm -rf *.o

cat.o: cat/cat.c clean_objcat
	gcc -Wall -Wextra -Werror -c cat/cat.c

catfunc.o: cat/catfunc.c clean_objcat
	gcc -Wall -Wextra -Werror -c cat/catfunc.c

clean_objcat:
	rm -rf *.o

cleancat: clean_objcat
	rm -rf cat/s21_cat