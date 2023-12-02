#include <stdio.h>

#include "s21_grep_func.h"

int main(int argc, char *argv[]) {
  grep_flags grep_flags = {0};
  grep_flags.regsetter = &regsetter;
  grep_flags.set_regs_from_file = &set_regs_from_file;
  set_flags(argc, argv, &grep_flags);
  searching(argc, argv, &grep_flags);
  return 0;
}
