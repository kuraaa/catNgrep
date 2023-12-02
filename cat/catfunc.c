#include "catfunc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void numall(FILE *file) {
  int count = 1;
  char *line = NULL;
  size_t len;
  ssize_t read = getline(&line, &len, file);
  while (read != -1) {
    printf("%6d\t", count++);
    printf("%s", line);
    read = getline(&line, &len, file);
  }
  free(line);
};

void numnonblanck(FILE *file) {
  int count = 1;
  char *line = NULL;
  size_t len;
  ssize_t read = getline(&line, &len, file);
  while (read != -1) {
    if (line[0] != '\n') {
      printf("%6d\t", count++);
      printf("%s", line);
    } else {
      printf("%s", line);
    }
    read = getline(&line, &len, file);
  }
  free(line);
};

void squeezeblancks(FILE *file) {
  int countsqz = 0;
  char *line = NULL;
  size_t len;
  ssize_t read = getline(&line, &len, file);
  while (read != -1) {
    if (line[0] == '\n') {
      countsqz++;
    } else {
      countsqz = 0;
    }
    if (countsqz <= 1) printf("%s", line);
    read = getline(&line, &len, file);
  }
  free(line);
};

void show_unprinted(FILE *file, int mode) {
  int ch;
  int flag = 1;
  while (!feof(file) && !ferror(file)) {
    ch = getc(file);
    if (ch != EOF) {
      if (((ch >= 0) && (ch < 9)) || ((ch > 10) && (ch < 32))) {
        putchar('^');
        putchar(ch + 64);
        flag = 0;
      }
      if (ch == 127) {
        putchar('^');
        putchar(ch - 64);
        flag = 0;
      }
      if ((ch > 127) && (ch < 160)) {
        putchar('-');
        putchar('M');
        putchar('^');
        putchar(ch % 128 + 64);
        flag = 0;
      }
      if ((ch == 9) && (mode == 2)) {
        printf("^I");
        flag = 0;
      }
      if ((ch == '\n') && (mode == 1)) {
        printf("$");
      }
      if (flag) {
        putchar(ch);
      } else {
        flag = 1;
      }
    }
  }
};