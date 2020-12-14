%{
#include <stdio.h>
#include "y.tab.h"

int linea = 1;
int columna = 1;
int flag = 0;
extern FILE * fout;
%}

%option noyywrap

DIGITO [0-9]
LETRA [a-zA-Z]
IDENTIFICADOR {LETRA}({DIGITO}|{LETRA})*
ENTERO {DIGITO}+
COMENTARIO "//".*\n
%%
{COMENTARIO}          {linea++; columna = 1;}
{ENTERO}              {yylval.atributos.valor_entero=atoi(yytext);columna +=yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_CONSTANTE_ENTERA;}
"main"                {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_MAIN;}
"int"                 {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_INT;}
"boolean"             {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_BOOLEAN;}
"array"               {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_ARRAY;}
"function"            {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_FUNCTION;}
"if"                  {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_IF;}
"else"                {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_ELSE;}
"while"               {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_WHILE;}
"scanf"               {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_SCANF;}
"printf"              {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_PRINTF;}
"return"              {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_RETURN;}
";"                   {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_PUNTOYCOMA;}
","                   {columna += yyleng; fprintf(fout, ";D:\t,\n");return TOK_COMA;}
"("                   {columna += yyleng; fprintf(fout, ";D:\t(\n");return TOK_PARENTESISIZQUIERDO;}
")"                   {columna += yyleng; fprintf(fout, ";D:\t)\n");return TOK_PARENTESISDERECHO;}
"["                   {columna += yyleng; fprintf(fout, ";D:\t[\n");return TOK_CORCHETEIZQUIERDO;}
"]"                   {columna += yyleng; fprintf(fout, ";D:\t]\n");return TOK_CORCHETEDERECHO;}
"{"                   {columna += yyleng; fprintf(fout, ";D:\t{\n");return TOK_LLAVEIZQUIERDA;}
"}"                   {columna += yyleng; fprintf(fout, ";D:\t}\n");return TOK_LLAVEDERECHA;}
"="                   {columna += yyleng; fprintf(fout, ";D:\t=\n");return TOK_ASIGNACION;}
"+"                   {columna += yyleng; fprintf(fout, ";D:\t+\n");return TOK_MAS;}
"-"                   {columna += yyleng; fprintf(fout, ";D:\t-\n");return TOK_MENOS;}
"/"                   {columna += yyleng; fprintf(fout, ";D:\t/\n");return TOK_DIVISION;}
"*"                   {columna += yyleng; fprintf(fout, ";D:\t*\n");return TOK_ASTERISCO;}
"&&"                  {columna += yyleng; fprintf(fout, ";D:\t&&\n");return TOK_AND;}
"||"                  {columna += yyleng; fprintf(fout, ";D:\t||\n");return TOK_OR;}
"!"                   {columna += yyleng; fprintf(fout, ";D:\t!\n");return TOK_NOT;}
"=="                  {columna += yyleng; fprintf(fout, ";D:\t==\n");return TOK_IGUAL;}
"!="                  {columna += yyleng; fprintf(fout, ";D:\t!=\n");return TOK_DISTINTO;}
"<="                  {columna += yyleng; fprintf(fout, ";D:\t<=\n");return TOK_MENORIGUAL;}
">="                  {columna += yyleng; fprintf(fout, ";D:\t>=\n");return TOK_MAYORIGUAL;}
"<"                   {columna += yyleng; fprintf(fout, ";D:\t<\n");return TOK_MENOR;}
">"                   {columna += yyleng; fprintf(fout, ";D:\t>\n");return TOK_MAYOR;}
"true"                {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_TRUE;}
"false"               {columna += yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_FALSE;}
[ \t\r]+              {columna += yyleng;}
\n                    {columna = 1; linea++;}
{IDENTIFICADOR}       {
                          if(yyleng > 100){
                            flag = 1;
                            fprintf(stderr, "****Error en [lin %d, col %d]: identificador demasiado largo (%s)\n", linea, columna, yytext);
                            return TOK_ERROR;
                          }else{
                            columna+=yyleng;
                            fprintf(fout, ";D:\t%s\n", yytext);
                            return TOK_IDENTIFICADOR;
                            }
                          }
.                     {flag = 1 ;fprintf(stderr, "****Error en [lin %d, col %d]: simbolo no permitido (%s)\n", linea, columna, yytext); return TOK_ERROR;}
%%
