%{
#include "alfa.h"
#include <stdio.h>
#include "y.tab.h"
#include "hash.h"

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
{ENTERO}              {yylval.atributos.tipo = ENTERO; yylval.atributos.valor_entero=atoi(yytext); strcpy(yylval.atributos.lexema , yytext); columna +=yyleng; fprintf(fout, ";D:\t%s\n", yytext);return TOK_CONSTANTE_ENTERA;}
function			{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_FUNCTION;}
return				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_RETURN;}
main				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_MAIN;}
boolean				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_BOOLEANO;}
array				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_ARRAY;}
printf				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_PRINTF;}
int					{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_INT;}
if					{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_IF;}
else				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_ELSE;}
while				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_WHILE;}
scanf				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_SCANF;}
false				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_FALSE;}
true				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_TRUE;}
==					{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_IGUAL;}
"!="				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_DISTINTO;}
"<="				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_MENORIGUAL;}
">="				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_MAYORIGUAL;}
"&&"				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_AND;}
"||"				{columna+=yyleng; fprintf(fout, ";D:\t%s\n", yytext); return TOK_OR;}
";"					{columna+=yyleng; fprintf(fout, ";D:\t;\n"); return yytext[0];}
"#"					{columna+=yyleng; fprintf(fout, ";D:\t#\n"); return yytext[0];}
","					{columna+=yyleng; fprintf(fout, ";D:\t,\n"); return yytext[0];}
"="					{columna+=yyleng; fprintf(fout, ";D:\t=\n"); return yytext[0];}
"("					{columna+=yyleng; fprintf(fout, ";D:\t(\n"); return yytext[0];}
")"					{columna+=yyleng; fprintf(fout, ";D:\t)\n"); return yytext[0];}
"{"					{columna+=yyleng; fprintf(fout, ";D:\t{\n"); return yytext[0];}
"}"					{columna+=yyleng; fprintf(fout, ";D:\t}\n"); return yytext[0];}
"["					{columna+=yyleng; fprintf(fout, ";D:\t[\n"); return yytext[0];}
"]"					{columna+=yyleng; fprintf(fout, ";D:\t]\n"); return yytext[0];}
":"					{columna+=yyleng; fprintf(fout, ";D:\t:\n"); return yytext[0];}
"+"					{columna+=yyleng; fprintf(fout, ";D:\t+\n"); return yytext[0];}
"-"					{columna+=yyleng; fprintf(fout, ";D:\t-\n"); return yytext[0];}
"/"					{columna+=yyleng; fprintf(fout, ";D:\t/\n"); return yytext[0];}
"*"					{columna+=yyleng; fprintf(fout, ";D:\t*\n"); return yytext[0];}
">"					{columna+=yyleng; fprintf(fout, ";D:\t>\n"); return yytext[0];}
"<"					{columna+=yyleng; fprintf(fout, ";D:\t<\n"); return yytext[0];}
"&"					{columna+=yyleng; fprintf(fout, ";D:\t&\n"); return yytext[0];}
"!"					{columna+=yyleng; fprintf(fout, ";D:\t!\n"); return yytext[0];}
"."					{columna+=yyleng; fprintf(fout, ";D:\t.\n"); return yytext[0];}
[ \t\r]+              {columna += yyleng;}
\n                    {columna = 1; linea++;}
{IDENTIFICADOR}       {
                          if(yyleng > 100){
                            flag = 1;
                            fprintf(stderr, "****Error en [lin %d, columna %d]: identificador demasiado largo (%s)\n", linea, columna, yytext);
                            return TOK_ERROR;
                          }else{
                            columna+=yyleng;
                            strcpy(yylval.atributos.lexema , yytext);
                            fprintf(fout, ";D:\t%s\n", yytext);
                            return TOK_IDENTIFICADOR;
                            }
                          }
.                     {flag = 1 ;fprintf(stderr, "****Error en [lin %d, columna %d]: simbolo no permitido (%s)\n", linea, columna, yytext); return TOK_ERROR;}
%%
