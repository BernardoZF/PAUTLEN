#include <stdlib.h>
#include <string.h>

#include "simbolo.h"

/* Informacion de un simbolo */
struct s_simbolo {
  char *lexema;        /* identificador */
  CATEGORIA categoria; /* categoria */
  TIPO tipo;           /* tipo del identificador o tipo devuelto si funcion*/
  CLASE clase;         /* clase del identificador */
  int adicional1; /* valor si escalar, longitud si vector, numero de parametros
                     si funcion */
  int adicional2; /* posicion en llamada a funcion si parametro, posicion de
                     declaracion si variable local de funcion */
};

simbolo *crear_simbolo(const char *lexema, CATEGORIA categoria, TIPO tipo,
                       CLASE clase, int adic1, int adic2) {
  simbolo *p_simbolo = NULL;

  if (!lexema) {
    return NULL;
  }

  p_simbolo = (simbolo *)malloc(sizeof(simbolo));
  if (!p_simbolo) {
    return NULL;
  }

  p_simbolo->lexema = (char*)malloc(strlen(lexema) + 1);
  p_simbolo->categoria = categoria;
  p_simbolo->tipo = tipo;
  p_simbolo->clase = clase;
  p_simbolo->adicional1 = adic1;
  p_simbolo->adicional2 = adic2;

  strcpy(p_simbolo->lexema, lexema);

  return p_simbolo;
}

simbolo *copy_simbolo(simbolo* p_simbolo) {
  simbolo* copy = NULL;

  copy = crear_simbolo(p_simbolo->lexema, p_simbolo->categoria, p_simbolo->tipo, 
      p_simbolo->clase, p_simbolo->adicional1, p_simbolo->adicional2);

  return copy;
}

char* get_simbolo_lexema(simbolo* p_s) {
  return p_s->lexema;
}

CATEGORIA get_simbolo_categoria(simbolo* p_s) {
  return p_s->categoria;
}

TIPO get_simbolo_tipo(simbolo* p_s) {
  return p_s->tipo;
}

CLASE get_simbolo_clase(simbolo* p_s) {
  return p_s->clase;
}

int get_simbolo_adicional1(simbolo* p_s) {
  return p_s->adicional1;
}

int get_simbolo_adicional2(simbolo* p_s) {
  return p_s->adicional2;
}

void set_simbolo_adicional1(simbolo* p_s, int adic1) {
  p_s->adicional1 = adic1;
}

void set_simbolo_adicional2(simbolo* p_s, int adic2) {
  p_s->adicional2 = adic2;
}

void liberar_simbolo(simbolo *simbolo) {
  if (!simbolo) {
    return;
  }

  if (simbolo->lexema) {
    free(simbolo->lexema);
  }

  free(simbolo);
}