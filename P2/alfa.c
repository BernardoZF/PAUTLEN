#include <stdio.h>
#include <string.h>
#include "tokens.h"

int yylex();

int main(int argc, char ** argv) {
    FILE * fout = NULL;
    extern FILE * yyin;
    extern FILE * yyout;
    extern char * yytext;
    int flag;


    yyin = fopen(argv[1], "r");
    if(!yyin) {
        return -1;
    }
    fout = fopen(argv[2], "w");
    if(!fout) {
        fclose(yyin);
        return -1;
    }
    yyout = fopen("default.txt", "w");
    if(!yyout){
      fclose(fout);
      fclose(yyin);
      return -1;
    }

    /** Bucle principal*/
    while((flag = yylex()) != 0) {
        switch(flag) {
            case TOK_MAIN:
                fprintf(fout, "TOK_MAIN\t%d\t%s\n", flag, yytext);
                break;
            case TOK_INT:
                fprintf(fout, "TOK_INT\t%d\t%s\n", flag, yytext);
              break;

            case TOK_BOOLEAN:
              fprintf(fout, "TOK_BOOLEAN\t%d\t%s\n", flag, yytext);
            break;

            case TOK_ARRAY:
              fprintf(fout, "TOK_ARRAY\t%d\t%s\n", flag, yytext);
            break;

            case TOK_FUNCTION:
              fprintf(fout, "TOK_FUNCTION\t%d\t%s\n", flag, yytext);
            break;

            case TOK_IF:
              fprintf(fout, "TOK_IF\t%d\t%s\n", flag, yytext);
            break;

            case TOK_ELSE:
              fprintf(fout, "TOK_ELSE\t%d\t%s\n", flag, yytext);
            break;

            case TOK_WHILE:
            fprintf(fout, "TOK_WHILE\t%d\t%s\n", flag, yytext);
                break;

            case TOK_SCANF:
            fprintf(fout, "TOK_SCANF\t%d\t%s\n", flag, yytext);
            break;

            case TOK_PRINTF:
              fprintf(fout, "TOK_PRINTF\t%d\t%s\n", flag, yytext);
            break;

              case TOK_RETURN:
            fprintf(fout, "TOK_RETURN\t%d\t%s\n", flag, yytext);
            break;

            case TOK_PUNTOYCOMA:
            fprintf(fout, "TOK_PUNTOYCOMA\t%d\t%s\n", flag, yytext);
            break;

            case TOK_COMA:
            fprintf(fout, "TOK_COMA\t%d\t%s\n", flag, yytext);
            break;

              case TOK_PARENTESISIZQUIERDO:
            fprintf(fout, "TOK_PARENTESISIZQUIERDO\t%d\t%s\n", flag, yytext);
            break;

            case TOK_PARENTESISDERECHO:
              fprintf(fout, "TOK_PARENTESISDERECHO\t%d\t%s\n", flag, yytext);
            break;

              case TOK_CORCHETEIZQUIERDO:
            fprintf(fout, "TOK_CORCHETEIZQUIERDO\t%d\t%s\n", flag, yytext);
            break;

            case TOK_CORCHETEDERECHO:
              fprintf(fout, "TOK_CORCHETEDERECHO\t%d\t%s\n", flag, yytext);
            break;

            case TOK_LLAVEIZQUIERDA:
              fprintf(fout, "TOK_LLAVEIZQUIERDA\t%d\t%s\n", flag, yytext);
            break;

            case TOK_LLAVEDERECHA:
            fprintf(fout, "TOK_LLAVEDERECHA\t%d\t%s\n", flag, yytext);
              break;

            case TOK_ASIGNACION:
              fprintf(fout, "TOK_ASIGNACION\t%d\t%s\n", flag, yytext);
            break;

            case TOK_MAS:
              fprintf(fout, "TOK_MAS\t%d\t%s\n", flag, yytext);
            break;

            case TOK_MENOS:
              fprintf(fout, "TOK_MENOS\t%d\t%s\n", flag, yytext);
            break;

            case TOK_DIVISION:
              fprintf(fout, "TOK_DIVISION\t%d\t%s\n", flag, yytext);
            break;

            case TOK_ASTERISCO:
              fprintf(fout, "TOK_ASTERISCO\t%d\t%s\n", flag, yytext);
            break;

            case TOK_AND:
              fprintf(fout, "TOK_AND\t%d\t%s\n", flag, yytext);
              break;

            case TOK_OR:
              fprintf(fout, "TOK_OR\t%d\t%s\n", flag, yytext);
            break;

            case TOK_NOT:
              fprintf(fout, "TOK_NOT\t%d\t%s\n", flag, yytext);
            break;

            case TOK_IGUAL:
            fprintf(fout, "TOK_IGUAL\t%d\t%s\n", flag, yytext);
            break;

            case TOK_DISTINTO:
            fprintf(fout, "TOK_DISTINTO\t%d\t%s\n", flag, yytext);
            break;

            case TOK_MENORIGUAL:
            fprintf(fout, "TOK_MENORIGUAL\t%d\t%s\n", flag, yytext);
            break;

            case TOK_MAYORIGUAL:
            fprintf(fout, "TOK_MAYORIGUAL\t%d\t%s\n", flag, yytext);
            break;


            case TOK_MENOR:
            fprintf(fout, "TOK_MENOR\t%d\t%s\n", flag, yytext);
            break;

            case TOK_MAYOR:
            fprintf(fout, "TOK_MAYOR\t%d\t%s\n", flag, yytext);
            break;

            case TOK_IDENTIFICADOR:
            fprintf(fout, "TOK_IDENTIFICADOR\t%d\t%s\n", flag, yytext);
            break;

            case TOK_CONSTANTE_ENTERA:
            fprintf(fout, "TOK_CONSTANTE_ENTERA\t%d\t%s\n", flag, yytext);
            break;

            case TOK_TRUE:
            fprintf(fout, "TOK_TRUE\t%d\t%s\n", flag, yytext);
            break;

            case TOK_FALSE:
            fprintf(fout, "TOK_FALSE\t%d\t%s\n", flag, yytext);
            break;


            case TOK_ERROR:
            fclose(yyout);
            fclose(yyin);
            fclose(fout);
            return 0;




            }
    }
    fclose(yyout);
    fclose(yyin);
    fclose(fout);
    return 0;
}
