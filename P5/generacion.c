#include "generacion.h"

/* FUNCIONES AUXILIARES */

/*
Obtiene los valores de la cima de la pila y los guarda en ecx y eax, en ese
orden. En caso de que se trate de una referencia, es decir, un valor de memoria,
mueve el contenido en dicha zona de memoria al registro eax y al registro ecx.
*/
void obtener_operandos(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; obtener_operandos\n");

    fprintf(fpasm, "pop dword ecx\n");
    fprintf(fpasm, "pop dword eax\n");

    if (es_variable_1 == 1)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    if (es_variable_2 == 1)
        fprintf(fpasm, "mov dword ecx, [ecx]\n");

    fprintf(fpasm,"\n");
}

/*
Obtiene el valor el valor de la cima de la pila y lo guarda en eax. En caso de
que se trate de una referencia, es decir, un valor de memoria, mueve el contenido
en dicha zona de memoria al registro eax.
*/
void obtener_operando(FILE *fpasm, int es_variable)
{
    fprintf(fpasm,";; obtener_operando\n");

    fprintf(fpasm, "pop dword eax\n");

    if (es_variable)
        fprintf(fpasm, "mov dword eax, [eax]\n");

    fprintf(fpasm,"\n");
}


/* FUNCIONES DE INICIALIZACION Y FINALIZACION DE PROGRAMAS */

void escribir_cabecera_bss(FILE *fpasm)
{
    fprintf(fpasm,";; escribir_cabecera_bss\n");

    fprintf(fpasm, "segment .bss\n");
    fprintf(fpasm, "__esp resd 1\n");
    fprintf(fpasm,"\n");
}

void escribir_subseccion_data(FILE *fpasm)
{
    fprintf(fpasm,";; escribir_subseccion_data\n");

    fprintf(fpasm, "segment .data\n");
    fprintf(fpasm, "div0_err db \"****Error de ejecucion: Division por 0\",0\n");
    fprintf(fpasm, "ior_err db \"****Error de ejecucion: Indice fuera de rango\",0\n");
    fprintf(fpasm,"\n");
}

void declarar_variable(FILE *fpasm, char *nombre, int tamano)
{
    fprintf(fpasm,";; declarar_variable\n");

    /* Todos los datos son de 32 bits */
    fprintf(fpasm, "_%s resd %d\n", nombre, tamano);
    fprintf(fpasm,"\n");
}

void escribir_segmento_codigo(FILE *fpasm)
{
    fprintf(fpasm,";; escribir_segmento_codigo\n");

    fprintf(fpasm, "segment .text\n");
    fprintf(fpasm, "global main\n");
    fprintf(fpasm, "extern print_int, print_boolean, print_string, print_blank\n");
    fprintf(fpasm, "extern print_endofline, scan_int, scan_boolean\n");
    fprintf(fpasm,"\n");
}

void escribir_inicio_main(FILE *fpasm)
{
    fprintf(fpasm,";; escribir_inicio_main\n");

    fprintf(fpasm, "main:\n");
    fprintf(fpasm, "mov dword [__esp], esp\n");
    fprintf(fpasm,"\n");
}

void escribir_fin(FILE *fpasm)
{
    fprintf(fpasm,";; escribir_fin\n");

    fprintf(fpasm, "jmp near fin\n");

    /* Gestion de errores */
    fprintf(fpasm, "div0_err_handler:\n");
    fprintf(fpasm, "push dword div0_err\n");
    fprintf(fpasm, "call print_string\n");
    fprintf(fpasm, "add esp, 4\n");
    fprintf(fpasm, "call print_endofline\n");
    fprintf(fpasm, "jmp near fin\n");

    fprintf(fpasm, "ior_err_handler:\n");
    fprintf(fpasm, "push dword ior_err\n");
    fprintf(fpasm, "call print_string\n");
    fprintf(fpasm, "add esp, 4\n");
    fprintf(fpasm, "call print_endofline\n");
    fprintf(fpasm, "jmp near fin\n");

    /* Salida del programa */
    fprintf(fpasm, "fin:\n");
    fprintf(fpasm, "mov esp, [__esp]\n");
    fprintf(fpasm, "ret\n");
}

void escribir_operando(FILE *fpasm, char *nombre, int es_variable)
{
    fprintf(fpasm,";; escribir_operando\n");

    if (es_variable)
        fprintf(fpasm, "push dword _%s\n", nombre);
    else
        fprintf(fpasm, "push dword %s\n", nombre);

    fprintf(fpasm,"\n");
}

void asignar(FILE *fpasm, char *nombre, int es_variable)
{
    fprintf(fpasm,";; asignar\n");

    obtener_operando(fpasm, es_variable);
    fprintf(fpasm, "mov dword [_%s], eax\n", nombre);
    fprintf(fpasm,"\n");
}


/* FUNCIONES ARITMÉTICO-LÓGICAS BINARIAS */

void sumar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; sumar\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    fprintf(fpasm, "add eax, ecx\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void restar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; restar\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    fprintf(fpasm, "sub eax, ecx\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void multiplicar(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; multiplicar\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    fprintf(fpasm, "imul ecx\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void dividir(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; dividir\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    /* Comprobacion division por 0*/
    fprintf(fpasm, "cmp ecx, 0\n");
    fprintf(fpasm, "je near div0_err_handler\n");

    fprintf(fpasm, "cdq\n");
    fprintf(fpasm, "idiv ecx\n");

    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void o(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; o\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    fprintf(fpasm, "or eax, ecx\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void y(FILE *fpasm, int es_variable_1, int es_variable_2)
{
    fprintf(fpasm,";; y\n");

    obtener_operandos(fpasm, es_variable_1, es_variable_2);

    fprintf(fpasm, "and eax, ecx\n");
    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void cambiar_signo(FILE *fpasm, int es_variable)
{
    fprintf(fpasm,";; cambiar_signo\n");

    obtener_operando(fpasm, es_variable);

    fprintf(fpasm, "neg eax\n");

    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}

void no(FILE *fpasm, int es_variable, int cuantos_no)
{
    fprintf(fpasm,";; no\n");

    obtener_operando(fpasm, es_variable);

    fprintf(fpasm, "cmp eax, 0\n");
    fprintf(fpasm, "je no_cero_%d\n", cuantos_no);

    fprintf(fpasm, "mov dword eax, 0\n");
    fprintf(fpasm, "jmp fin_no_%d\n", cuantos_no);

    fprintf(fpasm, "no_cero_%d:\n", cuantos_no);
    fprintf(fpasm, "mov dword eax, 1\n");

    fprintf(fpasm, "fin_no_%d:\n", cuantos_no);

    fprintf(fpasm, "push dword eax\n");
    fprintf(fpasm,"\n");
}


/* FUNCIONES COMPARATIVAS */

void igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; igual\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "je near igual_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_igual_%d\n", etiqueta);

    fprintf(fpasm, "igual_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_igual_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void distinto(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; distinto\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "jne near distinto_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_distinto_%d\n", etiqueta);

    fprintf(fpasm, "distinto_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_distinto_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void menor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; menor_igual\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "jle near menorigual_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_menorigual_%d\n", etiqueta);

    fprintf(fpasm, "menorigual_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_menorigual_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void mayor_igual(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; mayor_igual\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "jge near mayorigual_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_mayorigual_%d\n", etiqueta);

    fprintf(fpasm, "mayorigual_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_mayorigual_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void menor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; menor\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "jl near menor_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_menor_%d\n", etiqueta);

    fprintf(fpasm, "menor_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_menor_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void mayor(FILE *fpasm, int es_variable1, int es_variable2, int etiqueta)
{
    fprintf(fpasm,";; mayor\n");

    obtener_operandos(fpasm, es_variable1, es_variable2);

    fprintf(fpasm, "cmp eax, ecx\n");

    fprintf(fpasm, "jg near mayor_%d\n", etiqueta);

    fprintf(fpasm, "push dword 0\n");

    fprintf(fpasm, "jmp near fin_mayor_%d\n", etiqueta);

    fprintf(fpasm, "mayor_%d:\n", etiqueta);

    fprintf(fpasm, "push dword 1\n");

    fprintf(fpasm, "fin_mayor_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

/* FUNCIONES DE ESCRITURA Y LECTURA */

void leer(FILE *fpasm, char *nombre, int tipo, int local)
{
    fprintf(fpasm,";; leer\n");

    if (!local) {
      fprintf(fpasm, "push dword _%s\n", nombre);
    }

    if (tipo == ENTERO)
    {
        fprintf(fpasm, "call scan_int\n");
    }
    else if (tipo == BOOLEANO)
    {
        fprintf(fpasm, "call scan_boolean\n");
    }
    fprintf(fpasm, "add esp, 4\n");
    fprintf(fpasm,"\n");
}

void escribir(FILE *fpasm, int es_variable, int tipo)
{
    fprintf(fpasm,";; escribir\n");

    obtener_operando(fpasm, es_variable); /* WARNING: Puede que este mal */
    fprintf(fpasm, "push dword eax\n");
    if (tipo == ENTERO)
    {
        fprintf(fpasm, "call print_int\n");
    }
    else if (tipo == BOOLEANO)
    {
        fprintf(fpasm, "call print_boolean\n");
    }
    fprintf(fpasm, "add esp, 4\n");
    fprintf(fpasm, "call print_endofline\n");
    fprintf(fpasm,"\n");
}


/* FUNCIONES MANIPULACION DE VECTORES, FUNCIONES, BLUCLES Y ESTRUCTURAS CONDICIONALES */

/* MANIPULACION DE BUCLES Y ESTRUCTURAS CONDICIONALES */
void ifthenelse_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    fprintf(fpasm,";; ifthenelse_inicio\n");

    obtener_operando(fpasm, exp_es_variable);

    fprintf(fpasm, "cmp eax, 0\n");

    fprintf(fpasm, "je near fin_si_%d\n", etiqueta);
    fprintf(fpasm,"\n");
}

void ifthen_inicio(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    fprintf(fpasm,";; ifthen_inicio\n");

    obtener_operando(fpasm, exp_es_variable);

    fprintf(fpasm, "cmp eax, 0\n");

    fprintf(fpasm, "je near fin_si_%d\n", etiqueta);
    fprintf(fpasm,"\n");
}

void ifthen_fin(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm,";; ifthen_fin\n");

    fprintf(fpasm, "fin_si_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void ifthenelse_fin_then(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm,";; ifthenelse_fin_then\n");

    fprintf(fpasm, "jmp near fin_sino_%d\n", etiqueta);

    fprintf(fpasm, "fin_si_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void ifthenelse_fin(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm,";; ifthenelse_fin\n");

    fprintf(fpasm, "fin_sino_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void while_inicio(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm,";; while_inicio\n");

    fprintf(fpasm, "inicio_while_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}

void while_exp_pila(FILE *fpasm, int exp_es_variable, int etiqueta)
{
    fprintf(fpasm,";; while_exp_pila\n");

    obtener_operando(fpasm, exp_es_variable);

    fprintf(fpasm, "cmp eax, 0\n");

    fprintf(fpasm, "je near fin_while_%d\n", etiqueta);
    fprintf(fpasm,"\n");
}

void while_fin(FILE *fpasm, int etiqueta)
{
    fprintf(fpasm,";; while_fin\n");

    fprintf(fpasm, "jmp near inicio_while_%d\n", etiqueta);
    fprintf(fpasm, "fin_while_%d:\n", etiqueta);
    fprintf(fpasm,"\n");
}


/* MANIPULACION DE VECTORES*/

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

void modulo(FILE* fpasm, int es_variable_1, int es_variable_2)
{
  fprintf(fpasm, "\tpop dword eax\n");
	fprintf(fpasm, "\tpop dword ebx\n");


  if (es_variable_2>0) {
    fprintf(fpasm, "\tmov dword ebx, [ebx]\n");
  }
	if (es_variable_1>0) {
		fprintf(fpasm, "\tmov dword eax, [eax]\n");
	}



	fprintf(fpasm, "\tcmp ebx, 0\n");
	fprintf(fpasm, "\tje near div0_err_handler\n");


	fprintf(fpasm, "\tcdq\n\tidiv ebx\n");

	/* Se guarda edx en vez de eax porque es aqui donde se guarda el resto */
	fprintf(fpasm, "\tpush dword edx\n");
}
