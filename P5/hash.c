#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

SIMBOLO * simbolo_init(char *lexema, CATEGORIA cat, TIPO tipo, CLASE clase, int extrainfo1, int extrainfo2){
    SIMBOLO *s = NULL;

    if(!lexema) return NULL;

    s = (SIMBOLO*)malloc(sizeof(SIMBOLO));
    if(!s) return NULL;

    s->lexema = malloc((strlen(lexema) +1) *sizeof(char));
    strcpy(s->lexema, lexema);

    s->tipo = tipo;
    s->cat = cat;
    s->clase = clase;
    s->extra_info1 = extrainfo1;
    s->extra_info2 = extrainfo2;

    return s;
}

void simbolo_free(SIMBOLO *s){
    if(!s) return;

    free(s->lexema);
    free(s);

    return;
}

NODO * nodo_init(SIMBOLO *s){
    NODO *n = NULL;

    if(!s) return NULL;

    n = (NODO*)malloc(sizeof(NODO));
    if(!n) return NULL;

    n->info = s;
    n->next = NULL;

    return n;
}

void nodo_free(NODO *n){
  if(!n) return;

  simbolo_free(n->info);
  free(n);

  return ;

}

TABLA_HASH * tablahash_init(int tamanio){
    TABLA_HASH *t = NULL;

    if(tamanio<0) return NULL;

    t = (TABLA_HASH*)malloc(sizeof(TABLA_HASH));
    if(!t) return NULL;

    t->tam = tamanio;

    t->tabla = (NODO**)calloc(tamanio, sizeof(NODO*));
    if(!t->tabla){
        free(t);
        return NULL;
    }
    /*for(int i = 0; i< tamanio; i++){
        t->tabla[i] = NULL;
    }*/

    return t;

}

void tablahash_free(TABLA_HASH *t){
    NODO *aux;
    NODO *n;
    if(!t) return;

    for(int i = 0; i< t->tam; i++){
        if(t->tabla[i] != NULL){
            n = t->tabla[i];
           while(n->next != NULL){
               aux = n;
               n = n->next;
               nodo_free(aux);
           }
           nodo_free(n);
        }
    }

    free(t->tabla);
    free(t);

    return;

}

unsigned long hash(const char *str){
    unsigned long hash;

    if(!str) return 0;

    hash = 5381 + 33 * str[0];
    return hash;
}

SIMBOLO * find_simbolo(const TABLA_HASH *t, const char *lexema){
    NODO *n = NULL;
    int pos;
    
    if(!t || !lexema){
      return NULL;
    }

    pos = hash(lexema) % t->tam;
    n = t->tabla[pos];

    if(!n){
        return NULL;
    }

    while(strcmp(n->info->lexema, lexema)){
        if(n->next == NULL){
          return NULL;
        }
        n = n->next;
    }
    
    return n->info;
}

STATUS insert_simbolo(TABLA_HASH *t, char *lexema, CATEGORIA cat, TIPO tipo, CLASE clase, int extrainfo1, int extrainfo2){
    SIMBOLO *insert_sim = NULL;
    NODO *insert_nodo = NULL;
    NODO *aux = NULL;

    int pos;

    if(!t || !lexema || find_simbolo(t, lexema) != NULL) return ERROR;

    insert_sim = simbolo_init(lexema, cat, tipo, clase, extrainfo1, extrainfo2);
    if(insert_sim == NULL) return ERROR;

    insert_nodo = nodo_init(insert_sim);
    if(insert_nodo == NULL) return ERROR;

    pos = hash(lexema) % t->tam;

    if(t->tabla[pos] == NULL){
        t->tabla[pos] = insert_nodo;
    }else{
        aux = t->tabla[pos];
        while(aux->next != NULL){
            aux = aux->next;
        }

        aux->next = insert_nodo;
    }

    return OK;
}

void delete_simbolo(TABLA_HASH *t, const char *lexema){
    int ind;
    NODO *delete_nodo = NULL, *prev_nodo = NULL;

    if(!t || !lexema) return;

    ind = hash(lexema) % (t->tam);

    delete_nodo = t->tabla[ind];

    while(strcmp(lexema, delete_nodo->info->lexema) != 0){
        prev_nodo = delete_nodo;
        delete_nodo = delete_nodo->next;
    }

    if(!delete_nodo) return; /*No esta*/

    if(!prev_nodo){ /*Caso especial se elimina el primero*/
        t->tabla[ind] = delete_nodo->next;
    }else{ /*cualquier otro caso*/
        prev_nodo->next = delete_nodo->next;
    }

    nodo_free(delete_nodo);
    return;
}
