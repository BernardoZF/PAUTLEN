
#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

#include "hash.h"

#define SIZE 128

/* Tabla de simbolos */
typedef struct
{
    TABLA_HASH *contexto_global;
    TABLA_HASH *contexto_local;
} TablaSimbolos;

STATUS Ambitoglobal_create();
void Ambito_delete();
STATUS symbol_insert(SIMBOLO *simb_info);
SIMBOLO *buscarSimbolo(const char *lex);
STATUS crearAmbitoLocal(const char *lex, SIMBOLO *simb_info);
STATUS cerrarAmbitoLocal();
int is_local(const char *lex);
int exist_local();

#endif
