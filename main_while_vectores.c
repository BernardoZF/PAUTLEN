/**
* main {
*  int m;
*  int [4] v;
*  m = 0;
*  while ( m &lt;= 4 ){
*    printf m;
*    v[m] = m*10;
*    m = m + 1;
*  }
*}
*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"
int main (int argc, char ** argv)
{
if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}
int etiqueta = 0;
int getiqueta = 0;
int etiquetas[MAX_ETIQUETAS];
int cima_etiquetas=-1;
FILE * fd_asm;
fd_asm = fopen(argv[1],"w");
escribir_subseccion_data(fd_asm);
escribir_cabecera_bss(fd_asm);

declarar_variable(fd_asm,"m", 1, 1);

declarar_variable(fd_asm, "v", 1, 4);
escribir_segmento_codigo(fd_asm);
escribir_inicio_main(fd_asm);

escribir_operando(fd_asm,"0",0);
asignar(fd_asm,"m",0);

getiqueta++;
cima_etiquetas++;
etiquetas[cima_etiquetas]=getiqueta;

etiqueta = etiquetas[cima_etiquetas];
while_inicio(fd_asm, etiqueta);

escribir_operando(fd_asm,"m",1);
escribir_operando(fd_asm,"4",0);
menor_igual(fd_asm,1,0,etiqueta);

etiqueta = etiquetas[cima_etiquetas];
while_exp_pila(fd_asm, 0, etiqueta);

escribir_operando(fd_asm,"m",1);
escribir(fd_asm,1,ENTERO);

escribir_operando(fd_asm,"m",1);


escribir_operando(fd_asm,"10",0);
multiplicar(fd_asm,1,0);
escribir_operando(fd_asm,"m",1);
escribir_elemento_vector(fd_asm,"v", 4, 1);
asignarDestinoEnPila(fd_asm,0);

escribir_operando(fd_asm,"m",1);
escribir_operando(fd_asm,"1",0);
sumar(fd_asm,1,0);
asignar(fd_asm,"m",0);

etiqueta = etiquetas[cima_etiquetas];
while_fin(fd_asm, etiqueta);

cima_etiquetas--;
escribir_fin(fd_asm);
fclose(fd_asm);
}
