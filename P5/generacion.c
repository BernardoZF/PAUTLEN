#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generacion.h"


void escribir_subseccion_data(FILE* fpasm)
{
	fprintf(fpasm, "segment .data\n");
	fprintf(fpasm, "\t_msg_error_div db  \"Error, división por 0\", 0 \n");
	fprintf(fpasm, "\t_msg_error_vector db  \"Indice del vector fuera de rango\", 0 \n");
}

void escribir_cabecera_bss(FILE* fpasm)
{
	fprintf(fpasm, "segment .bss\n");
	fprintf(fpasm, "\t__esp resd 1\n");
}

void declarar_variable(FILE* fpasm, char * nombre,  int tipo,  int tamano)
{
		fprintf(fpasm, "\t_%s resd %d\n", nombre, tamano);
}

void escribir_segmento_codigo(FILE* fpasm){
	fprintf(fpasm, "segment .text\n");

	/*Exporto la etiqueta main...*/
	fprintf(fpasm, "\tglobal main\n");

	/*... y las funciones de la biblioteca alfalib.o*/
	fprintf(fpasm, "\textern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean, print_endofline, print_blank, print_string, alfa_malloc, alfa_free, ld_float\n");

}

void escribir_inicio_main(FILE* fpasm)
{
	/*La etiqueta main*/
	fprintf(fpasm, "main:\n");

	/*La sentencia que guarda el puntero de pila en su variable*/
fprintf(fpasm, "\tmov dword [__esp], esp\n");

}
void escribir_fin(FILE* fpasm)
{
	fprintf(fpasm, "\tjmp fin\n");
	fprintf(fpasm, "error_div_cero:\n");
	fprintf(fpasm, "\tpush dword _msg_error_div\n");
	fprintf(fpasm, "\tcall print_string\n");
	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");
	fprintf(fpasm, "\tjmp fin\n");


	fprintf(fpasm, "error_vector:\n");
	fprintf(fpasm, "\tpush dword _msg_error_vector\n");
	fprintf(fpasm, "\tcall print_string\n");
	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");

	fprintf(fpasm, "fin:\n");
	fprintf(fpasm, "\tmov dword esp, [__esp]\n");
	fprintf(fpasm, "\tret\n");

}

void escribir_operando(FILE* fpasm, char* nombre, int es_var)
{

	if (es_var == 0){ /* cuando es 0 hace referencia a un numero*/
		fprintf(fpasm,"\tpush dword %s\n", nombre);
	}else{ /* cuando es 1 hace referencia a una variable*/
		fprintf(fpasm,"\tpush dword _%s\n", nombre);
	}
}

void asignar(FILE* fpasm, char* nombre, int es_variable)
{

	fprintf(fpasm, "\tpop eax\n");

	if(es_variable>0){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}
	fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);

}


void sumar(FILE* fpasm, int es_variable_1, int es_variable_2)
{

	fprintf( fpasm, "\tpop dword eax\n ");
	fprintf( fpasm, "\tpop dword ebx\n ");

	if(es_variable_2>0){
		fprintf( fpasm, "\tmov eax, [eax]\n ");
	}
	if(es_variable_1>0){
	fprintf( fpasm, "\tmov ebx, [ebx]\n ");
	}

	fprintf(fpasm, "\tadd eax, ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");

}
void restar(FILE* fpasm, int es_referencia_1, int es_referencia_2)
{

	fprintf( fpasm, "\tpop dword eax\n ");
	fprintf( fpasm, "\tpop dword ebx\n ");

	if(es_referencia_2>0){
		fprintf( fpasm, "\tmov dword eax, [eax]\n ");
	}
	if(es_referencia_1>0){
	fprintf( fpasm, "\tmov dword ebx, [ebx]\n ");
	}
	fprintf(fpasm, "\tsub eax, ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");

}


void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2)
{

	/*Extraemos los argumentos y los preparamos para la multiplicación*/

	fprintf( fpasm, "\tpop dword eax\n ");
	fprintf( fpasm, "\tpop dword ebx\n ");

	if( es_variable_1>0){
			fprintf( fpasm, "\tmov dword ebx, [ebx]\n ");
	}
	if( es_variable_2>0){
    	fprintf( fpasm, "\tmov dword eax, [eax]\n ");
	}


	fprintf( fpasm, "\timul ebx \n");

	fprintf( fpasm, "\tpush dword eax \n");
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2)
{

	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");


	if (es_variable_1>0) {
		fprintf(fpasm, "\tmov dword eax, [eax]\n");
	}
	if (es_variable_2>0) {
		fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp ebx, 0\n");
	fprintf(fpasm, "\tje error_div_cero\n");

	fprintf(fpasm, "\tcdq\n\tidiv ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");
}

void modulo(FILE* fpasm, int es_variable_1, int es_variable_2)
{

	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");


	if (es_variable_1>0) {
		fprintf(fpasm, "\tmov dword eax, [eax]\n");
	}
	if (es_variable_2>0) {
		fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
	}

	fprintf(fpasm, "\txor edx, edx\n");

	fprintf(fpasm, "\tcmp ebx, 0\n");
	fprintf(fpasm, "\tje error_div_cero\n");

	fprintf(fpasm, "\tcdq\n\tidiv ebx\n");

	/* Se guarda edx en vez de eax porque es aqui donde se guarda el modulo */
	fprintf(fpasm, "\tpush dword edx\n");
}


void o(FILE* fpasm, int es_variable1, int es_variable2)
{
	fprintf(fpasm, "\tpop dword ebx\n"); /*extraemos la segunda variable*/
	if(es_variable2 >0){
		fprintf(fpasm, "\tmov dword ebx, [ebx]\n");  /*comprobamos si la segunda*/
/*variable es un valor o una
posición de memoria*/
	}

	fprintf(fpasm, "\tpop dword eax\n"); /*extraemos la primera variable*/
	if(es_variable1 >0){
		fprintf(fpasm, "\tmov dword eax, [eax]\n");  /*comprobamos si la primera*/
/*variable es un valor o una
posición de memoria*/
	}

	fprintf(fpasm, "\tor eax, ebx\n"); /*operación (el resultado se guarda en eax)*/
	fprintf(fpasm, "\tpush dword eax\n");
}


void y(FILE* fpasm, int es_variable1, int es_variable2)
{
	fprintf(fpasm, "\tpop dword ebx\n"); /*extraemos la segunda variable*/
	if(es_variable2 > 0){
		fprintf(fpasm, "\tmov dword ebx, [ebx]\n");  /*comprobamos si la segunda*/
/*variable es un valor o una
posición de memoria*/
	}

	fprintf(fpasm, "\tpop dword eax\n"); /*extraemos la primera variable*/
	if(es_variable1 > 0){
		fprintf(fpasm, "\tmov dword eax, [eax]\n");  /*comprobamos si la primera*/
/*variable es un valor o una
posición de memoria*/
	}

	fprintf(fpasm, "\tand eax, ebx\n"); /*operación (el resultado se guarda en eax)*/
	fprintf(fpasm, "\tpush dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_variable)
{

/*Guardamos la referencia a memoria de nuestra variable en el registro eax*/
fprintf(fpasm,"\tpop dword eax\n");

/*Guardamos el contenido de la posición de memoria en el registro eax*/
if(es_variable > 0){
	fprintf(fpasm,"\tmov dword eax, [eax]\n");
}


/*Negamos el contenido del operando*/
fprintf(fpasm, "\tneg eax\n");

/*Guardamos en pila el resultado obtenido*/
fprintf(fpasm, "\tpush dword eax\n");

}

void no(FILE* fpasm, int es_variable, int cuantos_no)
{

fprintf(fpasm, "\tpop eax\n");
if(es_variable > 0) fprintf(fpasm, "\tmov eax, [eax]\n");
fprintf(fpasm, "\tcmp eax, 0\n");
fprintf(fpasm, "\tje _uno%d\n", cuantos_no);
fprintf(fpasm, "\tpush dword 0\n");
fprintf(fpasm,"\tjmp _fin_not%d\n",cuantos_no);

fprintf(fpasm, "_uno%d:	push dword 1\n", cuantos_no);
fprintf(fpasm, "_fin_not%d:\n", cuantos_no);
}


void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}
	
	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tje near _igual_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_igual_%d\n", etiqueta);
	fprintf(fpasm, "_igual_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_igual_%d:\n", etiqueta);
	
}

void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}
	
	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tjne near _distinto_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_distinto_%d\n", etiqueta);
	fprintf(fpasm, "_distinto_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_distinto_%d:\n", etiqueta);
	
}

void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}

	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tjle near _menor_igual_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_menor_igual_%d\n", etiqueta);
	fprintf(fpasm, "_menor_igual_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_menor_igual_%d:\n", etiqueta);
	
}

void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}
	
	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tjge near _mayor_igual_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_mayor_igual_%d\n", etiqueta);
	fprintf(fpasm, "_mayor_igual_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_mayor_igual_%d:\n", etiqueta);
	
}

void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}
	
	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tjl near _menor_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_menor_%d\n", etiqueta);
	fprintf(fpasm, "_menor_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_menor_%d:\n", etiqueta);
	
}

void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {
	
	// Sacamos las variables de pila
	fprintf(fpasm, "\tpop dword edx\n\tpop dword eax\n");

	// Comprobamos si los operandos son referencias o valores explicitos
	if (es_variable2) {
		fprintf(fpasm, "\tmov edx, dword [edx]\n");
	}
	if (es_variable1) {
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}
	
	/*Implementado como en las diapositivas, no estoy seguro del todo de si he nombrado bien las 
		etiquetas ni si he puesto bien la sintaxis de los jump*/
		
	fprintf(fpasm, "\tcmp eax, edx\n");
	fprintf(fpasm, "\tjg near _mayor_%d\n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\tjmp near _fin_mayor_%d\n", etiqueta);
	fprintf(fpasm, "_mayor_%d:\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "_fin_mayor_%d:\n", etiqueta);
	
}


void leer(FILE* fpasm, char* nombre, int tipo)
{
	fprintf(fpasm, "\tpush dword _%s\n", nombre);
	if(tipo==BOOLEANO)
		fprintf(fpasm, "\tcall scan_boolean\n");
	else if (tipo==ENTERO)
		fprintf(fpasm, "\tcall scan_int\n");

	fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo)
{
	if(es_variable > 0){
		fprintf(fpasm, "\tpop eax\n");
		fprintf(fpasm, "\tmov eax, [eax]\n");
		fprintf(fpasm, "\tpush dword eax\n");
	}
	if(tipo==BOOLEANO){
		fprintf(fpasm, "\tcall print_boolean\n");
	}
	if (tipo==ENTERO)
		fprintf(fpasm, "\tcall print_int\n");

	fprintf(fpasm, "\tadd esp, 4\n");
	fprintf(fpasm, "\tcall print_endofline\n");

}



/*** IFS & WHILE ***/
void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta)
{

	fprintf(fpasm, "\tpop eax\n");

	if(exp_es_variable>0){
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
		}

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje   _fin_then%d\n", etiqueta);
}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta)
{

	fprintf(fpasm, "\tpop eax\n");

	if(exp_es_variable>0){
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
		}

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje   _fin_if%d\n", etiqueta);
}

void ifthen_fin(FILE * fpasm, int etiqueta)
{
	fprintf(fpasm, "_fin_if%d: \n", etiqueta);
}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta)
 {
	 fprintf(fpasm, "\tjmp   _fin_if_else%d \n", etiqueta);
	 fprintf(fpasm, "_fin_then%d: \n", etiqueta);
 }

void ifthenelse_fin( FILE * fpasm, int etiqueta)
{
	fprintf(fpasm, "_fin_if_else%d: \n", etiqueta);
}

void while_inicio(FILE * fpasm, int etiqueta)
{
	fprintf(fpasm, "_while_start%d: \n", etiqueta);
}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta)
{
	fprintf(fpasm, "\tpop eax \n");
	if(exp_es_variable>0){
		fprintf(fpasm,"\tmov eax, [eax]\n");
	}
	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje _fin_while%d\n", etiqueta );
}


void while_fin( FILE * fpasm, int etiqueta)
{
	fprintf(fpasm, "\t jmp   _while_start%d \n", etiqueta);
	fprintf(fpasm, "\t_fin_while%d: \n", etiqueta );
}


void escribir_elemento_vector(FILE *fpasm, char *nombre_vector, int tam_max, int exp_es_direccion)
{
    fprintf(fpasm,";; escribir_elemento_vector\n");

    obtener_operando(fpasm, exp_es_direccion);

    fprintf(fpasm, "cmp eax, 0\n");

    fprintf(fpasm, "jl near ior_err_handler\n");

    fprintf(fpasm, "cmp eax, %d\n", tam_max - 1);

    fprintf(fpasm, "jg near ior_err_handler\n");

    fprintf(fpasm, "mov dword edx, _%s\n", nombre_vector);

    fprintf(fpasm, "lea eax, [edx + eax*4]\n");

    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void asignarElementoVector(FILE *fpasm, int es_variable) {

    fprintf(fpasm,";; asignarElementoVector\n");

    /* Primer extraigo el valor */
    obtener_operando(fpasm, es_variable);

    /* Segundo obtengo la direccion */
    fprintf(fpasm, "pop dword edx\n");

    fprintf(fpasm, "mov dword [edx], eax\n");
    fprintf(fpasm,"\n");
}

/* MANIPULACION DE FUNCIONES */

void declararFuncion(FILE *fpasm, char *nombre_funcion, int num_var_loc)
{
    fprintf(fpasm,";; declararFuncion\n");

    fprintf(fpasm, "_%s:\n", nombre_funcion);
    fprintf(fpasm, "push dword ebp\n");
    fprintf(fpasm, "mov dword ebp, esp\n");
    fprintf(fpasm, "sub esp, %d\n", 4 * num_var_loc);
    fprintf(fpasm,"\n");
}

void retornarFuncion(FILE *fpasm, int es_variable)
{
    fprintf(fpasm,";; retornarFuncion\n");

    obtener_operando(fpasm, es_variable);
    fprintf(fpasm, "mov dword esp, ebp\n");
    fprintf(fpasm, "pop dword ebp\n");
    fprintf(fpasm, "ret\n");
    fprintf(fpasm,"\n");
}

void escribirParametro(FILE *fpasm, int pos_parametro, int num_total_parametros)
{
    int posicion = 0;

    /* Calculo la posicion del parametro a poner en la cima de la pila */
    posicion = 4 * (1 + (num_total_parametros - pos_parametro));

    fprintf(fpasm,";; escribirParametro\n");

    fprintf(fpasm, "lea eax, [ebp+ %d]\n", posicion);
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void escribirVariableLocal(FILE *fpasm, int posicion_variable_local)
{

    int posicion = 0;

    posicion = 4 * posicion_variable_local;

    fprintf(fpasm,";; escribirVariableLocal\n");

    fprintf(fpasm, "lea eax, [ebp - %d]\n", posicion);
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}


void asignarDestinoEnPila(FILE *fpasm, int es_varible)
{
    fprintf(fpasm,";; asignarDestinoEnPila\n");

    /* Primero obtengo la direccion */
    fprintf(fpasm, "pop dword edx\n");

    /* Ahora extraigo el valor */
    obtener_operando(fpasm, es_varible);

    fprintf(fpasm, "mov dword [edx], eax\n");
    fprintf(fpasm,"\n");
}

void operandoEnPilaAArgumento(FILE *fd_asm, int es_variable)
{
    fprintf(fd_asm,";; operandoEnPilaAArgumento\n");

    if (es_variable)
    {
        fprintf(fd_asm, "pop dword eax\n");
        fprintf(fd_asm, "mov dword eax, [eax]\n");
        fprintf(fd_asm, "push dword eax\n");
    }
    fprintf(fd_asm,"\n");
}

void llamarFuncion(FILE *fd_asm, char *nombre_funcion, int num_argumentos)
{
    fprintf(fd_asm,";; llamarFuncion\n");

    fprintf(fd_asm, "call _%s\n", nombre_funcion);
    limpiarPila(fd_asm, num_argumentos);
    fprintf(fd_asm, "push dword eax\n");
    fprintf(fd_asm,"\n");
}

void limpiarPila(FILE *fd_asm, int num_argumentos)
{
    fprintf(fd_asm,";; limpiarPila\n");

    fprintf(fd_asm, "add esp, %d\n", 4 * num_argumentos);
    fprintf(fd_asm,"\n");
}