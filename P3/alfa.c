#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

  FILE * fout = NULL;

int main(int argc, char ** argv)
{
  extern FILE * yyin;
  extern FILE * yyout;
  extern char * yytext;



  if (argc!= 3){
		printf("Especifica fichero de entrada y de salida");
		return 0;
	}

	if ((yyin = fopen(argv[1],"r")) == NULL){
		printf("Error al abrir el fichero de entrada");
	}

	if ((fout = fopen(argv[2],"w")) == NULL){
		printf("Error al abrir el fichero de salida");
	}

	yyout = fopen("default.txt","w");

	yyparse();

	fclose(yyin);
	fclose(yyout);
	fclose(fout);
}
