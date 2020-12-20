#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablasimbolos.h"

TablaSimbolos *table = NULL;

STATUS Ambitoglobal_create(){
    TablaSimbolos * table_aux = NULL;
    table_aux = (TablaSimbolos *)calloc(1, sizeof(TablaSimbolos));
    //Control de errores
    if (table_aux == NULL){
      return ERROR;
    }

    table_aux->contexto_global = tablahash_init(SIZE);

    //Control de ERRORores
    if (!table_aux->contexto_global)
    {
        //Liberamos memoria
        free(table);
        return ERROR;
    }
    //Inicializamos campos
    table_aux->contexto_local = NULL;
    //Igualamos la tabla
    table = table_aux;
  return OK;
}

void Ambito_delete(){
    //Control de errores
    if (table == NULL){
      return;
    }

    tablahash_free(table->contexto_global);

    //Si no hay contexto local liberamos la tabla
    if (table->contexto_local != NULL){
      tablahash_free(table->contexto_local);
    }
    //Liberamos memoria
    free(table);
}

STATUS symbol_insert(SIMBOLO * simb_info)
{
    TABLA_HASH *thash = NULL;

    //Control de errores
    if (!table || !simb_info){
        return ERROR;
    }
    //Si hay contexto_local lo añadimos a la tabla hash
    if (table->contexto_local){
      thash = table->contexto_local;
    }

    //Si no, le añadimos el contexto global
    else{
      thash = table->contexto_global;
    }
    //Insertamos el símbolo y retornamos el resultado.
    return insert_simbolo(thash, simb_info->lexema, simb_info->cat, simb_info->tipo, simb_info->clase, simb_info->extra_info1, simb_info->extra_info2);;
}

SIMBOLO *buscarSimbolo(const char *lex)
{
  //Inicializamos Símbolo
    SIMBOLO * simb = NULL;

    //Control de errores
    if (table == NULL || lex ==NULL || table->contexto_global == NULL){
        printf("ERROR EN BUSCAR SIMBOLO");
        return NULL;
    }
    printf("busqueda de simbolo iniciada\n");
    //Si existe contexto local
    if (table->contexto_local != NULL){
        //Buscamos símbolo
        printf("busqueda local entrando \n");
        simb = find_simbolo(table->contexto_local, lex);
        printf("salida de ambito local\n");

        //Lo devolvemos si existe
        if (simb){
            return simb;
        }
    }
    printf("busqueda en tabla global\n");
    if(table->contexto_global)
      simb = find_simbolo(table->contexto_global, lex);
    if(!simb){
      return NULL;
    }
    //En caso contrario buscamos el símbolo y devolvemos el resultado
    return simb;
}

STATUS crearAmbitoLocal(const char *lex, SIMBOLO * simb){

  int flag = 0;
  //Control de errores
    if (table == NULL || simb == NULL){
        return ERROR;
    }
    //Comprobamos si existe ámbito local
    if (table->contexto_local != NULL){
        return ERROR;
    }
    //Creamos la tabla y la guardamos en contexto local
    table->contexto_local = tablahash_init(SIZE);

    //Control de errores
    if (table->contexto_local == NULL){
        return ERROR;
    }

    //Insertamos el símbolo en el contexto global
    flag = insert_simbolo(table->contexto_global, simb->lexema, simb->cat, simb->tipo, simb->clase, simb->extra_info1, simb->extra_info2);
    //Control de errores
    if (flag == ERROR){
      //Liberamos memoria
        tablahash_free(table->contexto_local);
        table->contexto_local = NULL;
        return ERROR;
    }

    //Insertamos el símbolo en el contexto local
    flag = insert_simbolo(table->contexto_local, simb->lexema, simb->cat, simb->tipo, simb->clase, simb->extra_info1, simb->extra_info2);
    //Control de errores
    if (flag == ERROR){
      //Liberamos memoria
        tablahash_free(table->contexto_local);
        table->contexto_local = NULL;
        return ERROR;
    }

    return OK;
}

STATUS cerrarAmbitoLocal(){
  //Control de errores
    if (table== NULL){
        return ERROR;
    }
  //Comprobamos si existe contexto local
    if (table->contexto_local == NULL){
        return ERROR;
    }
    //Liberamos recursos y ponemos contexto local a NULL
    tablahash_free(table->contexto_local);
    table->contexto_local = NULL;
    return OK;
}

int is_local(const char *lex){

    SIMBOLO * simb = NULL;
    //Control de errores
    if (table==NULL || lex == NULL){
      return ERROR;
    }
    //Comprobamos si existe contexto local
    if (table->contexto_local){
      //Buscamos el símbolo
        simb = find_simbolo(table->contexto_local, lex);
        //Si lo encontramos retornamos 1, es decir, es local
        if (simb){
            return 1;
        }
    }
    //Comprobamos ahora si el símbolo está en el contexto global
    simb = find_simbolo(table->contexto_global, lex);

    //Si lo encontramos retornamos 0, es decir, no es local
    if (simb){
        return 0;
    }
    //En caso contrario retornamos error
    return -1;
}

int exist_local (){
    //Si existe, devolvemos 1, 0 en caso contrario
    if (table->contexto_local != NULL){
        return 1;
    }

    return 0;
}
