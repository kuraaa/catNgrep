#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "catfunc.h"

int main(int argc, char *argv[]) {
  char *options = "b:e:n:s:t:v";
  int option;
  FILE *file;

  if ((file = fopen(argv[1], "r")) != NULL) {
    for (int i = 1; i < argc; i++) {
      if ((file = fopen(argv[i], "r")) != NULL) {
        char *line = NULL;
        size_t len;
        ssize_t read = getline(&line, &len, file);
        while (read != -1) {
          printf("%s", line);
          read = getline(&line, &len, file);
        }
        free(line);
        fclose(file);
      }
    }
  } else {
    option = getopt(argc, argv, options);
    if ((file = fopen(argv[2], "r")) != NULL) {
      for (int i = 2; i < argc; i++) {
        if ((file = fopen(argv[i], "r")) != NULL) {
          switch (option) {
            case 'b':
              numnonblanck(file);
              break;
            case 'e':
              show_unprinted(file, 1);
              break;
            case 'n':
              numall(file);
              break;
            case 's':
              squeezeblancks(file);
              break;
            case 't':
              show_unprinted(file, 2);
              break;
            case 'v':
              show_unprinted(file, 3);
              break;
          }
        }
      }
    }
    fclose(file);
  }
  option = 0;
  return 0;
}
