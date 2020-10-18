#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"


void escribir_subseccion_data(FILE* fpasm)
{
	fprintf(fpasm, "segment .data\n");
	fprintf(fpasm, "\t_msg_error_div db  ‘Error, división por 0’ \n");
	fprintf(fpasm, "\t_msg_error_rango db \ "****Error de ejecución: fuera de rango.\", 0\n");
}

void escribir_cabecera_bss(FILE* fpasm){
	fprintf(fpasm, "segment .bss\n");
	fprintf(fpasm, "\t__esp resd 1\n");
}

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano)
{
	if(tipo == 0){
			fprintf(fpasm, "_%s resd %d", nombre, tamano);
			return;
	}
		fprintf(fpasm, "_%s resw %d", nombre, tamano);
}

void escribir_segmento_codigo(FILE* fpasm)
{
	/*Exporto la etiqueta main...*/
	fprintf(fpasm, "global main\n");

	/*... y las funciones de la biblioteca alfalib.o*/
	fprintf(fpasm, "extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean print_endofline, print_blank, print_string alfa_malloc, alfa_free, ld_float\n");

}
void escribir_inicio_main(FILE* fpasm) {
	/*La etiqueta main*/
	fprintf(fpasm, "main:\n");

	/*La sentencia que guarda el puntero de pila en su variable*/
fprintf(fpasm, "mov dword [__esp], esp\n");

}
void escribir_fin(FILE* fpasm){

fprintf(fpasm, "mov dword [__esp], esp\n");
fprintf(fpasm, "ret\n");

}

void escribir_operando(FILE* fpasm, char* nombre, int es_var){


if (es_var ){

 fprintf(fpasm,"push dword eax _nombre");
}
	 fprintf(fpasm,"push dword eax nombre");

}

void asignar(FILE* fpasm, char* nombre, int es_variable){

	fprintf(fpasm, "pop eax\n");
	if(es_variable==1){
		fprintf(fpasm, "mov eax, [eax]\n");
	}
	fprintf(fpasm, "mov dword [_%s], eax\n", nombre);

}


void sumar(FILE* fpasm, int es_variable_1, int es_variable_2){

	fprintf( fpasm, " pop dword eax\n ");
	fprintf( fpasm, " mov eax, [eax]\n ");
	fprintf( fpasm, " pop dword ebx\n ");
	fprintf( fpasm, " mov ebx, [ebx]\n ");

	fprintf(fpasm, "add eax, ebx\n");

	fprintf(fpasm, "push dword eax\n");

}
void restar(FILE* fpasm, int es_referencia_1, int es_referencia_2){

	fprintf( fpasm, " pop dword eax\n ");
	fprintf( fpasm, " mov eax, [eax]\n ");
	fprintf( fpasm, " pop dword ebx\n ");
	fprintf( fpasm, " mov ebx, [ebx]\n ");

	fprintf(fpasm, "sub eax, ebx\n");

	fprintf(fpasm, "push dword eax\n");

}


void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){

	// Extraemos los argumentos y los preparamos para la multiplicación

	fprintf( fpasm, " pop dword eax\n ");
	fprintf( fpasm, " pop dword ebx\n ");

	if( es_variable_2==1){
    	fprintf( fpasm, " mov dword eax, [eax]\n ");
	}

	if( es_variable_1==1){
    	fprintf( fpasm, " mov dword ebx, [ebx]\n ");
	}

	fprintf( fpasm, "imul ebx \n");

	// Se almacena la parte baja del resultado
	fprintf( fpasm, " push dword eax \n");

}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2){

// Extraemos los argumentos y los preparamos para la división

	printf( fpasm, " pop dword eax\n");

	if( es_variable_2==1){
    	fprintf( fpasm, " mov dword eax, [eax]\n");
	}

	fprintf( fpasm, " mov dword edx, 0\n");

	fprintf( fpasm, " pop dword ecx\n");

	if( es_variable_1==1){
    	fprintf( fpasm, " mov dword ecx, [ecx]\n");
	}

// Comprobar error por cociente 0

 /*
  fprintf( fpasm, " cmp ecx, 0\n");
	fprintf( fpasm, " jne not_zero\n");
	fprintf( fpasm, " push dword _msg_error_div\n");
	fprintf( fpasm, " call print_string\n");
	fprintf( fpasm, " jmp skip_div\n");
/* YA LO VEREMOS, HAY QUE SALTAR A UNA SECCIÓN FINAL PARA SALIR SIN "CASCAR" CON ESE MENSAJE */

// A partir de aquí continúa con la división
/*
	fprintf( fpasm, "not_zero:\n");
	fprintf( fpasm, " idiv ecx\n");

	// Se almacena el resto
	fprintf( fpasm, " push dword edx \n");
	// Se almacena el cocciente
	fprintf( fpasm, " push dword eax \n");
*/
/* FALTA CDQ */

// Si había un cero en el cociente saltamos aquí para no realizar la división
	fprintf( fpasm, "skip_div:\n");

}


void o(FILE* fpasm, int es_variable1, int es_variable2){
	fprintf(fpasm, "pop dword edx\n"); //extraemos la segunda variable
	if(es_variable2 == 1){
		fprintf(fpasm, "mov dword edx, [edx]\n");  //comprobamos si la segunda
variable es un valor o una
posición de memoria
	}

	fprintf(fpasm, "pop dword eax\n"); //extraemos la primera variable
	if(es_variable1 == 1){
		fprintf(fpasm, "mov dword eax, [eax]\n");  //comprobamos si la primera
variable es un valor o una
posición de memoria
	}

	fprintf(fpasm, "or eax, edx\n"); //operación (el resultado se guarda en eax)
	fprintf(fpasm, "push dword eax\n");
}


void y(FILE* fpasm, int es_variable1, int es_variable2){
	fprintf(fpasm, "pop dword edx\n"); //extraemos la segunda variable
	if(es_variable2 == 1){
		fprintf(fpasm, "mov dword edx, [edx]\n");  //comprobamos si la segunda
variable es un valor o una
posición de memoria
	}

	fprintf(fpasm, "pop dword eax\n"); //extraemos la primera variable
	if(es_variable1 == 1){
		fprintf(fpasm, "mov dword eax, [eax]\n");  //comprobamos si la primera
variable es un valor o una
posición de memoria
	}

	fprintf(fpasm, "and eax, edx\n"); //operación (el resultado se guarda en eax)
	fprintf(fpasm, "push dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_variable){

/*Guardamos la referencia a memoria de nuestra variable en el registro eax*/
fprintf(fpasm,"pop dword eax\n");

/*Guardamos el contenido de la posición de memoria en el registro eax*/ç
if(es_variable == 1){
	fprintf(fpasm,"mov dword eax, [eax]\n");
}


/*Negamos el contenido del operando*/
fprintf(fpasm, "neg eax\n");

/*Guardamos en pila el resultado obtenido*/
fprintf(fpasm, "push dword eax\n");

}

void no(FILE* fpasm, int es_variable, int cuantos_no){

fprintf(fpasm, "pop eax\n");
if(es_variable == 1) fprintf(fpasm, "mov eax, [eax]\n");
fprintf(fpasm, "cmp eax, 0\n");
fprintf(fpasm, "je _uno\n");
fprintf(fpasm, "push dword 0\n");
fprintf(fpasm,"jmp _fin_not%d\n",cuantos_no);

fprintf(fpasm, "_uno:	push dword 1\n");
fprintf(fpasm, "_fin_not%d:\n", cuantos_no);
/* FALTA AÑADIR NÚMERO DE ETIQUETA */
fprintf(fpasm, "pop eax\n");
fprintf(fpasm, "mov dword [_es_variable], eax\n");
}


 void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
 {
 	fprintf( fpasm, "pop dword ebx\n" );
 fprintf( fpasm, "pop dword eax\n" );

 if ( es_variable1 ) {
 	fprintf( fpasm, "mov dword ebx, [ebx]\n" );
 }

 if ( es_variable2 ) {
 	fprintf( fpasm, "mov dword eax, [eax]\n" );
 }

 fprintf( fpasm, "cmp eax, ebx\n" );
 fprintf( fpasm, "je _%d\n", etiqueta );


 }



 void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	 fprintf( fpasm, "pop dword eax\n" );
   fprintf( fpasm, "pop dword ebx\n" );

   if ( es_variable1 ) {
   	fprintf( fpasm, "mov dword eax, [eax]\n" );
   }

   if ( es_variable2 ) {
   	fprintf( fpasm, "mov dword ebx, [ebx]\n" );
   }

 fprintf( fpasm, "cmp eax, ebx\n" );
 fprintf( fpasm, "jne _%d\n", etiqueta );
 }
 void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta)
 {
 fprintf( fpasm, "pop dword eax\n" );
 fprintf( fpasm, "pop dword ebx\n" );

 if ( es_variable1 ) {
 	fprintf( fpasm, "mov dword eax, [eax]\n" );
 }

 if ( es_variable2 ) {
 	fprintf( fpasm, "mov dword ebx, [ebx]\n" );
 }

 fprintf( fpasm, "cmp ebx, eax\n" );
 fprintf( fpasm, "jbe _%d\n", etiqueta );


 }

 void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {

	 fprintf( fpasm, "pop dword eax\n" );
	 fprintf( fpasm, "pop dword ebx\n" );

	 if ( es_variable1 ) {
	  fprintf( fpasm, "mov dword eax, [eax]\n" );
	 }

	 if ( es_variable2 ) {
	  fprintf( fpasm, "mov dword ebx, [ebx]\n" );
	 }

fprintf( fpasm, "cmp ebx, eax\n" );
fprintf( fpasm, "jge _%d\n", etiqueta );

}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "pop ebx\n");
	fprintf(fpasm, "pop eax\n");

	if(es_variable1)
		fprintf(fpasm, "mov eax, [eax]\n");

	if(es_variable2)
fprintf(fpasm, "mov ebx, [ebx]\n");

	fprintf(fpasm, "cmp eax, ebx\n");
	fprintf(fpasm, "jb _%d\n", etiqueta);
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
fprintf(fpasm, "pop dword eax\n");/*es_variable1*/
	fprintf(fpasm, "pop dword ebx\n");/*es_variable2*/

	fprintf(fpasm, "mov eax, [eax]\n");
	fprintf(fpasm, "mov ebx, [ebx]\n");

	if(es_variable1){
		fprintf(fpasm, "mov eax, [eax]\n");
}
	is(es_variable2){
		fprintf(fpasm, "mov ebx, [ebx]\n");
}
	fprintf(fpasm, "cmp ebx, eax\n");/*compara eax y ebx*/
	fprintf(fpasm, "jg  _%d\n", etiqueta);
}


void leer(FILE* fpasm, char* nombre, int tipo){
	fprintf(fpasm, "push dword _%s\n", nombre);
	if(tipo==BOOLEANO)
		fprintf(fpasm, "call scan_boolean\n");
	else if (tipo==ENTERO)
		fprintf(fpasm, "call scan_int\n");

	fprintf(fpasm "add esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo){
	if(es_variable){
		fprintf(fpasm, "pop eax\n");
		fprintf(fpasm, "mov eax, [eax]\n");
		fprintf(fpasm, "push dword eax\n");
	}
	if(tipo==BOOLEANO)
		fprintf(fpasm, "call print_boolean\n");
	else if (tipo==ENTERO)
		fprintf(fpasm, "call print_int\n");
	fprintf(fpasm "add esp, 4\n");
	fprintf(fpasm, "call print_endofline\n");

}
