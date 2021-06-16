#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
FILE* yyasm;

int main(int argc, char **argv) {

  if (argc < 3) {
    fprintf(stderr, "Formato: %s <file.in> <file.out> [file.debug]", argv[0]);
    exit(EXIT_FAILURE);
  }

  yyin = fopen(argv[1], "r");
  if (yyin == NULL) {
    perror("error");
    exit(EXIT_FAILURE);
  }

  yyasm = fopen(argv[2], "w");
  if (yyasm == NULL) {
    perror("error");
    exit(EXIT_FAILURE);
  }

  if (argv[3] != NULL) {
    yyout = fopen(argv[3], "a");
    if (yyin == NULL) {
      perror("error");
      exit(EXIT_FAILURE);
    }
  }

yyparse();

  fclose(yyin);
  fclose(yyasm);
  if (yyout != NULL) {
    fclose(yyout);
  }

  return EXIT_SUCCESS;
  }
