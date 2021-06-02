  
#ifndef _ALFA_H
#define _ALFA_H

#define MAX_LONG_ID 100
#define MAX_TAMANIO_VECTOR 64
#define TH_SIZE 50000
#define MAX_ETIQUETAS 256

/* Tipos de retorno de una funcion */
typedef enum { ERR = -1, OK = 0 } STATUS;

/* Categoria de un simbolo: variable, parametro de funcion o funcion */
typedef enum { VARIABLE=1, PARAMETRO, FUNCION } CATEGORIA;

/* Tipo de un dato: solo se trabajara con enteros y booleanos */
typedef enum { ENTERO=1, BOOLEAN } TIPO;

/* Clase de un simbolo: pueden ser variables atomicas (escalares) o listas/arrays (vectores) */
typedef enum { ESCALAR=1, VECTOR } CLASE;

/* Atributos que pueden utilizar los simbolos no terminales de la gramatica */
typedef struct {
  char lexema[MAX_LONG_ID + 1]; /* Identificadores */
  TIPO tipo; /* Comprobacion de tipos basicos */
  int valor_entero; /* Constantes enteras */
  int es_direccion; /* Indica si es direccion de memoria o constante */
  int etiqueta; /* Sentencias condicionales e iterativas */
} tipo_atributos;

#endif
