/*
 * Fichero que prueba el funcionamiento de la tabla de símbolos, formada
 * mediante dos tablas hash que siguen el formato especificado en hash.c.
 * El programa lee de un fichero de entrada las tareas a realizar en la
 * tabla de símbolos, y devuelve en otro fichero el resultado de las
 * mismas según la implementación solicitada.
 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tablasimbolos.h"

#define MAX_LINE 30

int wordcount(char *str) {
	int i, n = 1;
	for(i = 0; str[i] != '\0'; i++) if(str[i] == ' ') n++;
	return n;
}

int main(int argc, char const *argv[]) {
  SIMBOLO * s;
  FILE *entrada;
  FILE *salida;
  char * line = NULL;
  size_t len;
  int opt = -1;
  char lex[MAX_LINE];

  if (argc != 3){
    printf("\nError: proporcionar ficheros de entrada y salida como argumentos\n");
    return 0;
  }

  entrada = fopen(argv[1], "r");
  /*CDE*/
  salida = fopen(argv[2], "w");
  /*CDE*/

  if(Ambitoglobal_create() == ERROR){
    /*liberar memoria*/
    printf("ERROR AL CREAR LA TABLA DE SIMBOLOS");
    return 0;
  }

  while( getline(&line, &len, entrada) != -1){
    if(wordcount(line)==1){
      sscanf(line, "%s", lex);
      s = buscarSimbolo(lex);
      if(s == NULL){
        fprintf(salida, "%s\t-1\n",lex);
      }else{
        fprintf(salida, "%s\t%d\n", s->lexema, s->extra_info1);
      }
    }else{
      sscanf(line, "%s %d", lex, &opt);
      if(opt>=0){
        s = simbolo_init(lex, VARIABLE, ENTERO, ESCALAR, opt, -1);
        if(symbol_insert(s) == ERROR){
          fprintf(salida, "-1\t%s\n", s->lexema);
        }else{
          fprintf(salida, "%s\n", s->lexema);
        }
        simbolo_free(s);
      }else{
        if(opt == -999){
          cerrarAmbitoLocal();
          fprintf(salida, "cierre\n");
        }else{
          s = simbolo_init(lex, FUNCION, ENTERO, ESCALAR, opt, 0);
          if(crearAmbitoLocal(lex, s) == ERROR){
            fprintf(salida, "-1\t%s\n", s->lexema);
          }else{
            fprintf(salida, "%s\n", s->lexema);
          }
          simbolo_free(s);
        }
      }
    }

  }

  fclose(entrada);
  fclose(salida);
  Ambito_delete();
  free(line);
  printf("\n");

  return 0;
}
