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
    }
    fclose(yyout);
    fclose(yyin);
    fclose(fout);
    return 0;
}
