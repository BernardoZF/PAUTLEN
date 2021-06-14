/******************************************************************************/
/*  SECCION DEFINICIONES                                                      */
/******************************************************************************/

%{
    /* Directivas include para las acciones */
    #include <stdio.h>
    #include <stdlib.h>

    #include "alfa.h"
    #include "y.tab.h"

   

    /* Definicion de variables */
    int row = 1;
    int col = 1;
    int err_morf = 0;
%}

%option nodefault
%option noyywrap
%option nounput noinput

DIGITO [0-9]
LETRA [a-zA-Z]
NUMERO {DIGITO}+
ALFANUMERICO ({DIGITO}|{LETRA})
COLA_IDENTIFICADOR {ALFANUMERICO}+

COMENTARIO "//".*\n

/******************************************************************************/
/*  SECCION REGLAS                                                            */
/******************************************************************************/

%%

{COMENTARIO}|"\n"   {col=0; row++;}
[ \t\r]             {col+=yyleng;}

 /* Palabras reservadas */

main    {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAIN;}
int     {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_INT;}
boolean {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_BOOLEAN;}
array   {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ARRAY;}
function    {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FUNCTION;}
if      {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IF;}
else    {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_ELSE;}
while   {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_WHILE;}
scanf   {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_SCANF;}
printf  {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_PRINTF;}
return  {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_RETURN;}

 /* Simbolos */

";"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
","         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"("         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
")"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"["         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"]"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"{"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"}"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"="         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"+"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"-"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"/"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"*"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
"&&"        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_AND;}
"||"        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_OR;}
"!"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_NOT;}
"=="        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!="        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"<="        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
">="        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
"%="        {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_MODULO;}
"<"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}
">"         {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return yytext[0];}

  /* Constantes */

true    {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_TRUE;}
false   {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); return TOK_FALSE;}
{NUMERO}    {col+=yyleng; fprintf(yyout, ";D:\t%s\n", yytext); yylval.atributos.valor_entero=atoi(yytext); return TOK_CONSTANTE_ENTERA;}

 /* Identificadores */
{LETRA}({LETRA}|{COLA_IDENTIFICADOR})*  {
                                            if(yyleng > MAX_LONG_ID) {
                                                col+=1;
                                                fprintf(stderr, "****Error en [lin %d, col %d]: Identificador demasiado largo (%s)\n", row, col, yytext);
                                                err_morf=1;
                                                return TOK_ERROR;
                                            }
                                            col+=yyleng;
                                            fprintf(yyout, ";D:\t%s\n", yytext);
                                            strcpy(yylval.atributos.lexema, yytext);
                                            return TOK_IDENTIFICADOR;
                                        }


 /* Errores */
.   {
        col+=yyleng;
        err_morf=1;
        fprintf(stderr, "****Error en [lin %d, col %d]: Simbolo no permitido (%s)\n", row, col, yytext);
        return TOK_ERROR;
    }
%%

/******************************************************************************/
/*  SECCION FUNCIONES DE USUARIO                                              */
/******************************************************************************/