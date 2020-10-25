/**
* main{
* int m;
* m = 0;
* if(m>5)
*   {
*   printf 2;
*   }
* else
*   {
*   printf 3;
*   }
* }
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"

int main (int argc, char ** argv)
{

  int etiqueta = 0;
  int getiqueta = 0;
  int etiquetas[MAX_ETIQUETAS];
  int cima_etiquetas=-1;
  FILE * fd_asm;

  if (argc != 2) {
    fprintf (stdout, "ERROR POCOS ARGUMENTOS\n");
    return -1;
  }

  fd_asm = fopen(argv[1],"w");
  escribir_subseccion_data(fd_asm);
  escribir_cabecera_bss(fd_asm);


  declarar_variable(fd_asm,"m", 1, 1);
  escribir_segmento_codigo(fd_asm);
  escribir_inicio_main(fd_asm);


  escribir_operando(fd_asm,"0",0);
  asignar(fd_asm,"m",0);

  getiqueta++;
  cima_etiquetas++;
  etiquetas[cima_etiquetas]=getiqueta;
  etiqueta = getiqueta;

  escribir_operando(fd_asm,"m",1);
  escribir_operando(fd_asm,"5",0);
  mayor(fd_asm,1,0,etiqueta);
  ifthenelse_inicio(fd_asm, 0, etiqueta);


  escribir_operando(fd_asm,"2",0);
  escribir(fd_asm,0,ENTERO);

  etiqueta = etiquetas[cima_etiquetas];
  ifthenelse_fin_then(fd_asm, etiqueta);

  escribir_operando(fd_asm,"3",0);
  escribir(fd_asm,0,ENTERO);

  etiqueta = etiquetas[cima_etiquetas];
  ifthenelse_fin(fd_asm, etiqueta);
  cima_etiquetas--;
  escribir_fin(fd_asm);
  fclose(fd_asm);
}
