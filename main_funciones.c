/**
* main{
*   int z;
*   function int doble(int arg)
*   {
*     int auxArg;
*     auxArg = arg;
*     return 2*arg;
*    }
*   z=2;
*   printf doble(z);
* }
*/

#include "generacion.h"

int main (int argc, char ** argv)
{
FILE * fd_asm;

fd_asm = fopen(argv[1],"w");
escribir_subseccion_data(fd_asm);
escribir_cabecera_bss(fd_asm);

declarar_variable(fd_asm,"z", 1, 1);
escribir_segmento_codigo(fd_asm);


declararFuncion(fd_asm,"doble",1);

escribirParametro(fd_asm,0,1);
escribirVariableLocal(fd_asm,1);
asignarDestinoEnPila(fd_asm,1);

escribir_operando(fd_asm,"2",0);
escribirParametro(fd_asm,0,1);
multiplicar(fd_asm,0,1);

retornarFuncion(fd_asm,0);
escribir_inicio_main(fd_asm);

escribir_operando(fd_asm,"2",0);
asignar(fd_asm,"z",0);
escribir_operando(fd_asm,"z",1);

operandoEnPilaAArgumento(fd_asm,1);
llamarFuncion(fd_asm,"doble",1);

escribir(fd_asm,0,ENTERO);
escribir_fin(fd_asm);
fclose(fd_asm);
return 0;
}
