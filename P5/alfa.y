%{
#include <stdio.h>
#include "alfa.h"
#include "hash.h"
#include "generacion.h"
#include "tablasimbolos.h"

extern int linea ;
extern int columna ;
extern int flag;
extern FILE * fout;
extern FILE * fasm;

int pos_parametro_actual = 0; /* Indica en que parametro estamos */
int num_parametros_actual = 0; /* Contador del numero de parametros */
int num_variables_locales_actual = 0; /* contador de varibles locales */
int pos_variable_local_actual = 0; /* Indica en que variable local estamos */
int hayReturn = 0; /* Indica si la funcion tiene return para cde */
int tiporeturn;
int cuantos = 0;/* esta variable es un contador para generar saltos unicos */
int num_parametros_llamada_actual = 0;
int clase_actual;
int tipo_actual;
int tamanio_vector_actual;
int etiqueta = 0;
char* pos_vector_actual;

void yyerror(char * s)
{
  if(flag == 0){
    fprintf(stdout,"****Error sintactico en [lin %d, col %d]\n", linea, columna-1);
  }
}
%}

%union
	{
	tipo_atributos atributos;
}

/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_RETURN

/* Símbolos */
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_ASTERISCO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR

/* Identificadores  */
%token <atributos> TOK_IDENTIFICADOR

/* Constantes */
%token TOK_CONSTANTE_ENTERA
%token TOK_TRUE
%token TOK_FALSE

/* Errores */
%token TOK_ERROR


%type <atributos> tipo
%type <atributos> comparacion
%type <atributos> constante
%type <atributos> clase_escalar
%type <atributos> clase_vector
%type <atributos> condicional
%type <atributos> if_else_exp
%type <atributos> if_exp
%type <atributos> exp
%type <atributos> asignacion
%type <atributos> elemento_vector
%type <atributos> constante_logica
%type <atributos> constante_entera
%type <atributos> parametros_funcion
%type <atributos> funcion
%type <atributos> resto_parametros_funcion
%type <atributos> lista_expresiones
%type <atributos> resto_lista_expresiones
%type <atributos> fn_name
%type <atributos> idpf
%type <atributos> fn_complete_name
%type <atributos> tipo_retorno
%type <atributos> sentencia_simple
%type <atributos> retorno_funcion
%type <atributos> fn_declaration
%type <atributos> bucle
%type <atributos> while
%type <atributos> while_exp

%start programa
%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_ASTERISCO TOK_DIVISION TOK_AND
%right MENOSU '!'

%%

programa : inicio TOK_MAIN TOK_LLAVEIZQUIERDA  escritura1 declaraciones funciones  escritura2 escribir_main sentencias TOK_LLAVEDERECHA escribir_fin{fprintf(fout, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");}

inicio:	{	crearAmbitoGlobal();
			pos_parametro = 0;
			num_parametros = 0;
			num_variables_locales = 0;
			pos_variable_local = 0;
			num_parametros_llamada = 0;
}

escritura1 : { escribir_subseccion_data(fasm);
					    escribir_cabecera_bss(fasm);}


escritura2 : { escribir_segmento_codigo(fasm);}

escribir_main: { escribir_inicio_main(fasm);}

escribir_fin: { escribir_fin(fasm);}

declaraciones : declaracion {fprintf(fout, ";R2:\t<declaraciones> ::= <declaracion>\n");}
              | declaracion declaraciones {fprintf(fout, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}

declaracion : clase identificadores TOK_PUNTOYCOMA {fprintf(fout ,";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}

clase : clase_escalar {  fprintf(fout, ";R5:\t<clase> ::= <clase_escalar>\n");}
      | clase_vector { fprintf(fout, ";R7:\t<clase> ::= <clase_vector>\n");}

clase_escalar : tipo {clase = ESCALAR;fprintf(fout, ";R9:\t<clase_escalar> ::= <tipo>\n");}

tipo : TOK_INT {tipo = ENTERO; fprintf(fout, ";R10:\t<tipo> ::= int\n");}
      | TOK_BOOLEAN {tipo = BOOLEANO; fprintf(fout, ";R11:\t<tipo> ::= boolean");}

clase_vector : TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO{ tam_vector = atoi($4.valor_entero);
                                                                                              if(tam_vector < 1){
                                                                                               fprintf(stdout,"****Error semantico en lin %d:\n\tEl tamanyo del vector menor a 1.\n", linea); 
                                                                                               return -1;
                                                                                              }
                                                                                                clase = VECTOR;
                                                                                               fprintf(fout, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");}

identificadores : identificador {fprintf(fout, ";R18:\t<identificadores> ::= <identificador>\n");}
                | identificador TOK_COMA identificadores {fprintf(fout, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}

funciones : funcion funciones {fprintf(fout, ";R20:\t<funciones> ::= <funciones> <funciones>\n");}
            | {fprintf(fout, ";R21:\t<funciones> ::=\n");}

funcion : TOK_FUNCTION tipo TOK_IDENTIFICADOR TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion sentencias TOK_LLAVEDERECHA {
                  fprintf(fout,";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) <declaraciones_funcion> <sentencias> \n");
                  if (buscarSimbolo($3.lexema) != NULL)
					{
						errorSemantico("La funcion ha sido declarada dos veces.\n",$1.lexema);
						return -1;
					} 
                                    strcpy($$.lexema, $3.lexema);
				            $$.tipo = $1.tipo;
                                    crearAmbitoLocal($3.lexema, crear_info_simbolo($3.lexema, FUNCION, tipo_actual, clase_actual, 0, 0));

  				
					num_variables_locales_actual = 0;
					pos_variable_local_actual = 1;
					num_parametros_actual = 0;
					pos_parametro_actual = 0;
                              
                  }

parametros_funcion : parametro_funcion resto_parametros_funcion {fprintf(fout, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
                    | {fprintf(fout, ";R24:\t<parametros_funcion> ::=\n");}

resto_parametros_funcion : TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion{fprintf(fout, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
                          | {fprintf(fout, ";R26:\t<resto_parametros_funcion>::=\n");}

parametro_funcion : tipo identificador {fprintf(fout, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}

declaraciones_funcion : declaraciones {fprintf(fout, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
                      | {fprintf(fout, ";R29:\t<declaraciones_funcion> ::=\n");}

sentencias : sentencia {fprintf(fout,";R30:\t<sentencias> ::= <sentencia>\n");}
            | sentencia sentencias {fprintf(fout, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}

sentencia : sentencia_simple TOK_PUNTOYCOMA {fprintf(fout, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
          | bloque {fprintf(fout, ";R33:\t<sentencia> ::= <bloque>\n");}

sentencia_simple : asignacion {fprintf(fout, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
                  | lectura {fprintf(fout, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
                  | escritura {fprintf(fout, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
                  | retorno_funcion {fprintf(fout, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}

bloque : condicional {fprintf(fout, ";R40:\t<bloque> ::= <condicional>\n");}
        | bucle {fprintf(fout, ";R41:\t<bloque> ::= <bucle>\n");}

asignacion : identificador TOK_ASIGNACION exp {fprintf(fout, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");}
            | elemento_vector TOK_ASIGNACION exp{fprintf(fout, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");}

elemento_vector : identificador TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {fprintf(fout, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");}

condicional : TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(fout, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");}
              | TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE  TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(fout, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");}

bucle : TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA { fprintf(fout, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");}

lectura : TOK_SCANF identificador {fprintf(fout, ";R54:\t<lectura> ::= scanf <identificador>\n");}

escritura : TOK_PRINTF exp {fprintf(fout, ";R56:\t<escritura> ::= printf <exp>\n");}

retorno_funcion : TOK_RETURN exp  {fprintf(fout, ";R61:\t<retorno_funcion> ::= return <exp>\n");}

exp : exp TOK_MAS exp { fprintf (fout, ";R72:\t<exp> ::= <exp> + <exp>\n");}
     	| exp TOK_MENOS exp   { fprintf (fout, ";R73:\t<exp> ::= <exp> - <exp>\n");}
      | exp TOK_DIVISION exp {fprintf(fout, ";R74:\t<exp> ::= <exp> / <exp>\n");}
      | exp TOK_ASTERISCO exp {fprintf(fout, ";R75:\t<exp> ::= <exp> * <exp>\n");}
      | TOK_MENOS exp %prec MENOSU   { fprintf (fout, ";R76:\t<exp> ::=  - <exp>\n");}
      | exp TOK_AND exp    {fprintf(fout, ";R77:\t<exp> ::= <exp> && <exp>\n");}
      | exp TOK_OR exp    {fprintf(fout, ";R78:\t<exp> ::= <exp> || <exp>\n");}
      | TOK_NOT exp            {fprintf(fout, ";R79:\t<exp> ::= ! <exp>\n");}
      | identificador      {fprintf(fout, ";R80:\t<exp> ::= <identificador>\n");}
      | constante        {fprintf (fout, ";R81:\t<exp> ::= <constante>\n");}
      | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {fprintf(fout, ";R82:\t<exp> ::= ( <exp> )\n");}
      | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {fprintf(fout, ";R83:\t<exp> ::= ( <comparacion> )\n");}
      | elemento_vector {fprintf(fout, ";R852:\t<exp> ::= <elemento_vector>\n");}
      | identificador TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {fprintf(fout, ";R88:\t<exp> ::= <identificador>( <lista_expresiones> )\n");}

lista_expresiones : exp resto_lista_expresiones {fprintf(fout, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
                    | {fprintf(fout, ";R90:\t<lista_expresiones> ::=\n");}

resto_lista_expresiones : TOK_COMA exp resto_lista_expresiones {fprintf(fout, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
                          | {fprintf(fout, ";R92:\t<resto_lista_expresiones> ::=\n");}

comparacion : exp TOK_IGUAL exp {fprintf(fout, ";R93:\t<comparacion> ::= <exp> ==  <exp>\n");}
              | exp TOK_DISTINTO exp {fprintf(fout, ";R94:\t<comparacion> ::= <exp> !=  <exp>\n");}
              | exp TOK_MENORIGUAL exp {fprintf(fout, ";R95:\t<comparacion> ::= <exp> <=  <exp>\n");}
              | exp TOK_MAYORIGUAL exp {fprintf(fout, ";R96:\t<comparacion> ::= <exp> >=  <exp>\n");}
              | exp TOK_MENOR exp {fprintf(fout, ";R97:\t<comparacion> ::= <exp> <  <exp>\n");}
              | exp TOK_MAYOR exp {fprintf(fout, ";R98:\t<comparacion> ::= <exp> >  <exp>\n");}


constante : constante_entera {fprintf(fout, ";R99:\t<constante> ::= <constante_entera>\n");}
            | constante_logica {fprintf(fout, ";R100:\t<constante> ::= <constante_logica>\n");}

constante_logica : TOK_CONSTANTE_ENTERA {fprintf(fout, ";R104:\t<constante_entera> ::= TOK_CONSTANTE_ENTERA\n");}

constante_logica : TOK_TRUE {fprintf(fout, ";R102:\t<constante_logica> ::= true\n");}
                   | TOK_FALSE {fprintf(fout, ";R103:\t<constante_logica> ::= false\n");}

identificador : TOK_IDENTIFICADOR {if(buscarSimbolo($1.lexema)!= NULL){
                                     fprintf(stdout, "ERROR MORFOLOGICO");
                                    }else{
                                          if(clase == ESCALAR) {
                                                simboloinit($1.lexema, VARIABLE, tipo, clase, 0, 0);
                                          }
                                          else if(clase == VECTOR){
                                                simboloinit($1.lexema, VARIABLE, tipo, clase, tam_vector, 0);
                                          }
                                          else{
                                                fprintf(stdout, "ERROR MORFOLOGICO");
                                          }
                                          
                                    }
                                    fprintf(fout, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");}


%%
