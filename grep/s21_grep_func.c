#include "s21_grep_func.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_line(char **argv, grep_flags *grep_flags, char *str,
                int finded_num_str, int tmp_optind) {
  if (!grep_flags->c && !grep_flags->l) {
    if (grep_flags->count_files < 2) {
      if (grep_flags->n) {
        printf("%d:%s\n", finded_num_str, str);
      } else {
        printf("%s\n", str);
      }
    } else {
      if (grep_flags->n) {
        if (grep_flags->h) {
          printf("%d:%s\n", finded_num_str, str);
        } else {
          printf("%s:%d:%s\n", argv[tmp_optind], finded_num_str, str);
        }
      } else {
        if (grep_flags->h) {
          printf("%s\n", str);
        } else {
          printf("%s:%s\n", argv[tmp_optind], str);
        }
      }
    }
  }
}

void print_file(char **argv, grep_flags *grep_flags, int count_matches,
                int tmp_optind, char was_find) {
  if (was_find) {
    if (grep_flags->l && !(grep_flags->c)) {
      printf("%s\n", argv[tmp_optind]);
    }
  }
  if ((grep_flags->count_files < 2) && !(grep_flags->l) && grep_flags->c) {
    printf("%d\n", count_matches);
  }
  if ((grep_flags->count_files < 2) && grep_flags->l && grep_flags->c) {
    if (count_matches) {
      printf("%d\n%s\n", count_matches / count_matches, argv[tmp_optind]);
    } else {
      printf("%d\n", count_matches);
    }
  }
  if (!(grep_flags->count_files < 2) && (grep_flags->l) && grep_flags->c) {
    if (count_matches) {
      if (grep_flags->h) {
        printf("%d\n%s\n", count_matches / count_matches, argv[tmp_optind]);
      } else {
        printf("%s:%d\n%s\n", argv[tmp_optind], count_matches / count_matches,
               argv[tmp_optind]);
      }
    } else {
      if (grep_flags->h) {
        printf("%d\n", count_matches);
      } else {
        printf("%s:%d\n", argv[tmp_optind], count_matches);
      }
    }
  }

  if (grep_flags->h) {
    if (!(grep_flags->count_files < 2) && !(grep_flags->l) && grep_flags->c) {
      printf("%d\n", count_matches);
    }
  } else {
    if (!(grep_flags->count_files < 2) && !(grep_flags->l) && grep_flags->c) {
      printf("%s:%d\n", argv[tmp_optind], count_matches);
    }
  }
}

char find_match(grep_flags *grep_flags, char *buf_str) {
  regex_t reg_ptr;
  int ignore_case_flag = 0;
  int reg_rez = 0;
  char finded = 0;

  for (int i = 0; i < grep_flags->ind_reg_str; i++) {
    // grep - i
    if (grep_flags->i) {
      ignore_case_flag = REG_ICASE;
    }
    //  grep -i
    if (regcomp(&reg_ptr, grep_flags->arr_reg_str[i], ignore_case_flag) == 0) {
      reg_rez = regexec(&reg_ptr, buf_str, 0, NULL, 0);
      regfree(&reg_ptr);
    }
    if (!reg_rez) {
      finded = 1;
    }
  }

  return finded;
}
void searching(int argc, char **argv, grep_flags *grep_flags) {
  int tmp_optind = argc - grep_flags->count_files;
  FILE *file = NULL;

  int chars = 0;
  size_t buf_size = 256;
  char *buf_str;
  buf_str = (char *)malloc(buf_size * sizeof(char));
  while (tmp_optind < argc) {
    int finded_num_str = 1;
    if ((file = fopen(argv[tmp_optind], "r")) != NULL) {
      char was_find = 0;
      int count_matches = 0;
      while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
        if (buf_str[strlen(buf_str) - 1] == '\n') {
          buf_str[strlen(buf_str) - 1] = '\0';
        }
        if (((!grep_flags->v) && (find_match(grep_flags, buf_str))) ||
            ((grep_flags->v) && (!find_match(grep_flags, buf_str)))) {
          was_find = 1;
          count_matches++;
          print_line(argv, grep_flags, buf_str, finded_num_str, tmp_optind);
        }
        finded_num_str++;  // n flag
      }
      print_file(argv, grep_flags, count_matches, tmp_optind, was_find);
    } else {
      if (!grep_flags->s) {
        printf("grep: %s: No such file or directory\n", argv[tmp_optind]);
      }
    }
    tmp_optind++;
  }

  free(buf_str);
  buf_str = NULL;

  fclose(file);
  file = NULL;
}

void set_flags(int argc, char **argv, grep_flags *grep_flags) {
  char grep_key = 0;
  while ((grep_key = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    switch (grep_key) {
      case 'e':
        grep_flags->e = 1;
        grep_flags->regsetter(grep_flags, optarg);
        break;
      case 'i':
        grep_flags->i = 1;
        break;
      case 'v':
        grep_flags->v = 1;
        break;
      case 'c':
        grep_flags->c = 1;
        break;
      case 'l':
        grep_flags->l = 1;
        break;
      case 'n':
        grep_flags->n = 1;
        break;
      case 'h':
        grep_flags->h = 1;
        break;
      case 's':
        grep_flags->s = 1;
        break;
      case 'f':
        grep_flags->f = 1;
        grep_flags->set_regs_from_file(grep_flags, optarg);
        break;
      case 'o':
        grep_flags->o = 1;
        break;
      default:
        break;
    }
  }
  if (!grep_flags->e && !grep_flags->f) {
    grep_flags->count_files = argc - optind - 1;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        grep_flags->regsetter(grep_flags, argv[i]);
        break;
      }
    }
  } else {
    grep_flags->count_files = argc - optind;
  }
}

void set_regs_from_file(grep_flags *grep_flags, char *file_name) {
  FILE *file = NULL;
  char chars = 0;
  size_t buf_size = 256;
  char *buf_str = NULL;

  if ((file = fopen(file_name, "r")) != NULL) {
    while ((chars = getline(&buf_str, &buf_size, file)) != -1) {
      char reg_tmp[255] = {0};

      if (!strcmp(buf_str, "\n")) {
        grep_flags->regsetter(grep_flags, "**");
        break;
      }
      if (strlen(buf_str) == 1) {
        grep_flags->regsetter(grep_flags, buf_str);
      }
      if (strlen(buf_str) > 1) {
        memcpy(reg_tmp, buf_str, strlen(buf_str) - 1);
        grep_flags->regsetter(grep_flags, reg_tmp);
      }
    }
  } else {
    printf("%s no file\n", file_name);
  }
  free(buf_str);
  fclose(file);
}

void regsetter(grep_flags *grep_flags, char *reg_str) {
  strcpy(grep_flags->arr_reg_str[grep_flags->ind_reg_str], reg_str);
  grep_flags->ind_reg_str++;
}