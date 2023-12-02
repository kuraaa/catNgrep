typedef struct Grep_flags {
  char e, i, v, c, l, n, h, s, f, o, count_files;
  char arr_reg_str[1024][256];
  int ind_reg_str;
  void (*regsetter)();
  void (*set_regs_from_file)();
} grep_flags;

void set_regs_from_file(grep_flags *grep_flags, char *file_name);
void regsetter(grep_flags *grep_flags, char *reg_str);

char find_match(grep_flags *grep_flags, char *buf_str);
void print_str(char *buf_str, grep_flags *grep_flags, char *file_name,
               int finded_num_str);

void searching(int argc, char **argv, grep_flags *grep_flags);
void set_flags(int argc, char **argv, grep_flags *grep_flags);