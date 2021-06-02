#ifndef __SIMBOLO_H_
#define __SIMBOLO_H_

#include "alfa.h"

/* Informacion de un simbolo */
typedef struct s_simbolo simbolo;

simbolo *crear_simbolo(const char *lexema, CATEGORIA categoria, TIPO tipo,
    CLASE clase, int adic1, int adic2);
void liberar_simbolo(simbolo *simbolo);
char* get_simbolo_lexema(simbolo* p_s); 
CATEGORIA get_simbolo_categoria(simbolo* p_s);
TIPO get_simbolo_tipo(simbolo* p_s);
CLASE get_simbolo_clase(simbolo* p_s);
int get_simbolo_adicional1(simbolo* p_s);
int get_simbolo_adicional2(simbolo* p_s);
void set_simbolo_adicional1(simbolo* p_s, int adic1);
void set_simbolo_adicional2(simbolo* p_s, int adic2);
simbolo *copy_simbolo(simbolo* p_simbolo);

#endif