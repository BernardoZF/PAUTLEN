%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int linea = 1;
int columna = 1;
%}

%option noyywrap

DIGITO [0-9]
LETRA [a-zA-Z]
IDENTIFICADOR {LETRA}({DIGITO}|{LETRA})*
ENTERO {DIGITO}+
COMENTARIO "//".*\n
%%
{COMENTARIO}          {linea++; columna = 1;}
{ENTERO}              {columna +=yyleng; return TOK_CONSTANTE_ENTERA;}
"main"                {columna += yyleng; return TOK_MAIN;}
"int"                 {columna += yyleng; return TOK_INT;}
"boolean"             {columna += yyleng; return TOK_BOOLEAN;}
"array"               {columna += yyleng; return TOK_ARRAY;}
"function"            {columna += yyleng; return TOK_FUNCTION;}
"if"                  {columna += yyleng; return TOK_IF;}
"else"                {columna += yyleng; return TOK_ELSE;}
"while"               {columna += yyleng; return TOK_WHILE;}
"scanf"               {columna += yyleng; return TOK_SCANF;}
"printf"              {columna += yyleng; return TOK_PRINTF;}
"return"              {columna += yyleng; return TOK_PRINTF;}
";"                   {columna += yyleng; return TOK_PUNTOYCOMA;}
","                   {columna += yyleng; return TOK_COMA;}
"("                   {columna += yyleng; return TOK_PARENTESISIZQUIERDO;}
")"                   {columna += yyleng; return TOK_PARENTESISDERECHO;}
"["                   {columna += yyleng; return TOK_CORCHETEIZQUIERDO;}
"]"                   {columna += yyleng; return TOK_CORCHETEDERECHO;}
"{"                   {columna += yyleng; return TOK_LLAVEIZQUIERDA;}
"}"                   {columna += yyleng; return TOK_LLAVEDERECHA;}
"="                   {columna += yyleng; return TOK_ASIGNACION;}
"+"                   {columna += yyleng; return TOK_MAS;}
"-"                   {columna += yyleng; return TOK_MENOS;}
"/"                   {columna += yyleng; return TOK_DIVISION;}
"*"                   {columna += yyleng; return TOK_ASTERISCO;}
"&&"                  {columna += yyleng; return TOK_AND;}
"||"                  {columna += yyleng; return TOK_OR;}
"!"                   {columna += yyleng; return TOK_NOT;}
"=="                  {columna += yyleng; return TOK_IGUAL;}
"!="                  {columna += yyleng; return TOK_DISTINTO;}
"<="                  {columna += yyleng; return TOK_MENORIGUAL;}
">="                  {columna += yyleng; return TOK_MAYORIGUAL;}
"<"                   {columna += yyleng; return TOK_MENOR;}
">"                   {columna += yyleng; return TOK_MAYOR;}
"true"                {columna += yyleng; return TOK_TRUE;}
"false"               {columna += yyleng; return TOK_FALSE;}
[ \t\r]+              {columna += yyleng;}
\n|\n\                {columna = 1; linea++;}
{IDENTIFICADOR}       {
                          if(yyleng > ID_MAX){
                            fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", linea, columna, yytext);
                            return TOK_ERROR;
                          }else{
                            columna+=yyleng;
                            return TOK_IDENTIFICADOR;
                            }
                          }
.                     {fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", linea, columna, yytext); return TOK_ERROR;}
%%
