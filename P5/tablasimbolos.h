#ifndef __TABLASIMBOLOS_H_
#define __TABLASIMBOLOS_H_

#include "hash.h"
#include "simbolo.h"
#include "alfa.h"

typedef struct s_tabla_simbolos tabla_simbolos;

/* Crea e inicializa las estructuras necesarias para una tabla de simbolos. */
tabla_simbolos *ts_crear();
/* Libera los recursos asociados a una tabla de simbolos. */
void ts_free(tabla_simbolos *p_ts);
/* Crea e inserta un simbolo con la informacion asociada que se pasa como parametros.
 * Si se ha abierto un scope previamente insertara en la tabla de simbolos local y
 * no permite introducir vectores en la misma. */
STATUS ts_insert(tabla_simbolos *p_ts, const char* lexema, CATEGORIA cat, TIPO t, CLASE cl, int adic1, int adic2);
/* Busca en la tabla de simbolos activa un simbolo con el lexema del argumento. Devuelve
 * NULL si no lo encuentra. */
simbolo* ts_search(tabla_simbolos *p_ts, const char* lexema);
/* Activa la tabla de simbolos local e inserta un simbolo con el lexema introducido. */
STATUS ts_open_scope(tabla_simbolos *p_ts, const char* lexema, TIPO t);
/* Desactiva la tabla de simbolos local activa. Si no hay tabla de simbolos local activa
 * devuelve error. */
STATUS ts_close_scope(tabla_simbolos *p_ts);
/* Devuelve todos los simbolos que tiene actualmente la tabla de simbolos activa. */
LinkedList* ts_get_simbolos(tabla_simbolos *p_ts);

#endif