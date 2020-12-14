#ifndef HASH_H
#define HASH_H

typedef enum { ENTERO, BOOLEANO } TIPO;
typedef enum { VARIABLE, PARAMETRO, FUNCION } CATEGORIA;
typedef enum { ESCALAR, VECTOR } CLASE;
typedef enum { ERROR, OK } STATUS;



typedef struct SIMBOLO{
    char *lexema;
    TIPO tipo;
    CATEGORIA cat;
    CLASE clase;
    int extra_info1; /*Si el simbolo es escalar->valor, vector->longitud, funcion->num_parametros*/
    int extra_info2; /*Si el simbolo es parametro->posicion_en_la_llamada, variable->posicion_declaracion, funcion-> num_variables_locales*/
}SIMBOLO;

typedef struct NODO {
    SIMBOLO *info;
    struct NODO *next;
}NODO;

typedef struct TABLA_HASH{
    NODO **tabla;
    int tam;
}TABLA_HASH;

SIMBOLO * simbolo_init(char *lexema, CATEGORIA cat, TIPO tipo, CLASE class, int extrainfo1, int extrainfo2);
void simbolo_free(SIMBOLO *s);
NODO * nodo_init(SIMBOLO *s);
void nodo_free(NODO *n);
TABLA_HASH * tablahash_init(int tamanio);
void tablahash_free(TABLA_HASH *t);
unsigned long hash(const char *str);
SIMBOLO * find_simbolo(const TABLA_HASH *t, const char *lexema);
STATUS insert_simbolo(TABLA_HASH *t, char *lexema, CATEGORIA cat, TIPO tipo, CLASE clase, int extrainfo1, int extrainfo2);
void delete_simbolo(TABLA_HASH *t, const char *lexema);

#endif
