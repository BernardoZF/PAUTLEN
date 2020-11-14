#include <stdio.h>
#include "generacion.h"

int main (int argc, char ** argv)
{
/*

	int x;
	int y;
	int z;
	boolean b1;
	int j;

	scanf x;
	scanf z;
	scanf b1;
	printf !b1;
	j = - x;
	printf j;
	printf x+z;
	printf z;



*/
	FILE * salida;
	int cuantos_no = 0;


	if (argc != 2) {fprintf (stdout, "ERROR POCOS ARGUMENTOS\n"); return -1;}


	salida = fopen(argv[1],"w");


	escribir_subseccion_data(salida);
	escribir_cabecera_bss(salida);
	declarar_variable(salida, "x", ENTERO, 1);
	declarar_variable(salida, "y", ENTERO, 1);
	declarar_variable(salida, "z", ENTERO, 1);
	declarar_variable(salida, "b1", BOOLEANO, 1);
	declarar_variable(salida, "j", ENTERO, 1);


	escribir_segmento_codigo(salida);
	escribir_inicio_main(salida);

	leer(salida,"x",ENTERO);
	leer(salida,"z",ENTERO);
	leer(salida,"b1",BOOLEANO);

	escribir_operando(salida,"b1",1);
	no(salida,1,cuantos_no++);
	escribir(salida,0,BOOLEANO);

/*-----------AQUI PETA AL EJECUTAR EL .ASM (core dumped)*/
	escribir_operando(salida,"x",1);
	cambiar_signo(salida,1);
	asignar(salida, "j",0);
	escribir_operando(salida,"j",1);
	escribir(salida,1,ENTERO);

	escribir_operando(salida,"x",1);
	escribir_operando(salida,"z",1);

	sumar(salida, 1, 1);
	escribir(salida,0,ENTERO);
	escribir_operando(salida,"z",1);
	escribir(salida,1,ENTERO);

	escribir_fin(salida);

	fclose(salida);
	return 0;


}
