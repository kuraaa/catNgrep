rebuild: clean s21_cat

s21_cat: cat.o catfunc.o
	gcc -Wall -Wextra -Werror cat.o catfunc.o -o s21_cat
	rm -rf *.o

cat.o: cat.c clean_obj
	gcc -Wall -Wextra -Werror -c cat.c

catfunc.o: catfunc.c clean_obj
	gcc -Wall -Wextra -Werror -c catfunc.c

s21_cat_testfunc: rebuild
	sh test_func_cat.sh s21_cat

s21_cat_testleak: rebuild
	sh test_leak_cat.sh s21_cat

clean_obj:
	rm -rf *.o

clean: clean_obj
	rm -rf s21_cat