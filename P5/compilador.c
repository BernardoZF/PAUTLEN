#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
FILE* yyasm;

int main(int argc, char **argv) {

  int ret;

  if (argc < 3) {
    fprintf(stderr, "Formato: %s <file.in> <file.out> [file.debug]", argv[0]);
    exit(EXIT_FAILURE);
  }

  yyin = fopen(argv[1], "r");
  if (yyin == NULL) {
    fprintf(stderr, "Fallo de fopen() en el archivo %s", __FILE__);
    exit(EXIT_FAILURE);
  }

  yyasm = fopen(argv[2], "w");
  if (yyasm == NULL) {
    fprintf(stderr, "Fallo de fopen() en el archivo %s", __FILE__);
    exit(EXIT_FAILURE);
  }

  if (argv[3] != NULL) {
    yyout = fopen(argv[3], "a");
    if (yyin == NULL) {
      fprintf(stderr, "Fallo de fopen() en el archivo %s", __FILE__);
      exit(EXIT_FAILURE);
    }
  }

  ret = yyparse();
  if (ret != 0) {
    /* Borramos el fichero asm si hay un error para que el script de
     * compilacion no trate de compilar el archivo asm incorrecto*/
    remove(argv[2]);
  }

  fclose(yyin);
  fclose(yyasm);
  if (yyout != NULL) {
    fclose(yyout);
  }

  return EXIT_SUCCESS;