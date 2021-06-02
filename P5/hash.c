#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#define HASH_INI 5381
#define HASH_FACTOR 33

/* Define un elemento tipo de la tabla hash */
struct s_Ht_item {
  char *key;
  simbolo *value;
};

struct s_LinkedList {
  Ht_item *item;
  LinkedList *next;
};

struct s_HashTable {
  Ht_item **items;
  LinkedList **overflow_buckets; /* Lista de elementos que han colisionado */
  int size;
};

unsigned long hash(HashTable *Ht, const char *str) {
  int i;
  unsigned long h = HASH_INI;

  for (i = 0; str[i]; i++) {
    h = h * HASH_FACTOR + str[i];
  }

  return h % Ht->size;
}

/******************************************************************************/
/* LINKED LIST                                                                */
/******************************************************************************/
LinkedList *allocate_list() {
  LinkedList *list = NULL;

  list = (LinkedList *)malloc(sizeof(LinkedList));

  return list;
}

LinkedList *linkedlist_insert(LinkedList *list, Ht_item *item) {
  LinkedList *node = NULL;
  LinkedList *temp = NULL;

  if (!list) {
    return NULL;
  }

  temp = list;
  /* Buscamos el ultimo nodo */
  while (temp->next) {
    temp = temp->next;
  }

  /* Insertamos el nuevo nodo */
  node = allocate_list();
  node->item = item;
  node->next = NULL;
  temp->next = node;

  return list;
}

Ht_item *linkedlist_remove(LinkedList *list) {

  LinkedList *node = NULL;
  LinkedList *temp = NULL;
  Ht_item *it = NULL;

  if (!list) {
    return NULL;
  }

  /* El ultimo elemento debe borrarse mediante la funcion
   * free_overflow_buckets.*/
  if (!list->next) {
    return NULL;
  }

  node = list->next;
  temp = list;
  temp->next = NULL;
  list = node;

  memcpy(temp->item, it, sizeof(Ht_item));
  free(temp->item->key);
  free(temp->item->value);
  free(temp->item);
  free(temp);

  return it;
}

LinkedList* get_LinkedList_next(LinkedList *list) {
  return list->next;
}

Ht_item* get_LinkedList_item(LinkedList *list) {
  return list->item;
}

static void free_linkedlist(LinkedList *list) {
  LinkedList *temp = list;
  while (list) {
    temp = list;
    list = list->next;
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
  }
}

/******************************************************************************/
/* HASH TABLE                                                                 */
/******************************************************************************/
LinkedList **create_overflow_buckets(HashTable *table) {
  int i;
  LinkedList **buckets = NULL;

  buckets = (LinkedList **)calloc(table->size, sizeof(LinkedList *));
  for (i = 0; i < table->size; i++) {
    buckets[i] = NULL;
  }

  return buckets;
}

void free_overflow_buckets(HashTable *table) {
  int i;
  LinkedList **buckets = NULL;

  buckets = table->overflow_buckets;
  for (i = 0; i < table->size; i++) {
    free_linkedlist(buckets[i]);
  }

  free(buckets);
}

Ht_item *item_create(const char *key, simbolo *value) {
  Ht_item *item = NULL;

  item = (Ht_item *)malloc(sizeof(Ht_item));
  item->key = (char *)malloc(strlen(key) + 1);
  item->value = value;

  strcpy(item->key, key);

  return item;
}

void item_free(Ht_item *item) {
  free(item->key);
  liberar_simbolo(item->value);
  free(item);
}

Ht_item* item_copy(Ht_item *item) {

  Ht_item* copy = NULL;
  simbolo* simbolo_copy = NULL;

  simbolo_copy = copy_simbolo(item->value);
  copy = item_create(item->key, simbolo_copy);

  return copy;
}

simbolo* get_Htitem_value(Ht_item *ht) {
  return ht->value;
}

HashTable *ht_create(int size) {
  int i;
  HashTable *table = NULL;

  table = (HashTable *)malloc(sizeof(HashTable));
  table->size = size;
  table->items = (Ht_item **)calloc(table->size, sizeof(Ht_item *));
  for (i = 0; i < table->size; i++)
    table->items[i] = NULL;
  table->overflow_buckets = create_overflow_buckets(table);

  return table;
}

void ht_free(HashTable *table) {
  int i;
  Ht_item *item = NULL;

  for (i = 0; i < table->size; i++) {
    item = table->items[i];
    if (item != NULL) {
      item_free(item);
    }
  }

  free_overflow_buckets(table);
  free(table->items);
  free(table);
}

void handle_collision(HashTable *table, unsigned long index, Ht_item *item) {
  LinkedList *head = table->overflow_buckets[index];

  if (head == NULL) {
    head = allocate_list();
    head->item = item;
    table->overflow_buckets[index] = head;
  } else {
    table->overflow_buckets[index] = linkedlist_insert(head, item);
  }
}

Ht_item* ht_search(HashTable *table, const char *key) {
  int index;
  Ht_item *item = NULL;
  LinkedList *head = NULL;

  index = hash(table, key);
  item = table->items[index];
  head = table->overflow_buckets[index];

  while (item != NULL) {
    if (strcmp(item->key, key) == 0)
      return item;
    if (head == NULL)
      return NULL;
    item = head->item;
    head = head->next;
  }

  return NULL;
}

STATUS ht_insert(HashTable *table, const char *key, simbolo *value) {
  unsigned long index;
  Ht_item *item = NULL;
  Ht_item *current_item = NULL;

  if (ht_search(table, key)) {
    return ERR;
  }

  item = item_create(key, value);
  index = hash(table, key);

  current_item = table->items[index];
  if (current_item == NULL) {
    table->items[index] = item;
  } else {
    handle_collision(table, index, item);
  }

  return OK;
}

void ht_delete(HashTable *table, const char *key) {
  int index;
  Ht_item *item = NULL;
  LinkedList *head = NULL;
  LinkedList *node = NULL;
  LinkedList *curr = NULL;
  LinkedList *prev = NULL;

  index = hash(table, key);
  item = table->items[index];
  head = table->overflow_buckets[index];

  if (item == NULL) {
    return;
  } else {
    /* Caso 1: Elemento en la tabla items */
    if (strcmp(item->key, key) == 0) {
      if (!head) {
        table->items[index] = NULL;
        item_free(item);
        return;
      } else {
        item_free(item);
        node = head;
        head = head->next;
        node->next = NULL;
        table->items[index] = item_create(node->item->key, node->item->value);
        free_linkedlist(node);
        table->overflow_buckets[index] = head;
        return;
      }
    }

    /* Caso 2: Elemento en la tabla de colisiones */
    curr = head;
    prev = NULL;

    while (curr) {
      if (strcmp(curr->item->key, key) == 0) {
        /* Primer elemento de la lista de colisiones */
        if (prev == NULL) {
          node = head;
          head = head->next;
          table->overflow_buckets[index] = head;
          free_linkedlist(node);
          return;
        } else {
          /* Resto de elementos de la lista de colisiones */
          prev->next = curr->next;
          curr->next = NULL;
          free_linkedlist(curr);
          table->overflow_buckets[index] = head;
          return;
        }
      }
      prev = curr;
      curr = curr->next;
    }
  }
}

LinkedList* get_Htitems(HashTable *table) {

  int i;
  LinkedList *head = NULL;
  Ht_item* copy = NULL;

  for (i = 0; i < table->size; i++) {
    if (table->items[i]) {
      if (!head) {
        head = allocate_list();
        head->item = item_copy(table->items[i]);
        head->next = NULL;
      } else {
        copy = item_copy(table->items[i]);
        head = linkedlist_insert(head, copy);
      }
      if (table->overflow_buckets[i]) {
        copy = item_copy(table->overflow_buckets[i]->item);
        head = linkedlist_insert(head, copy);
      }
    }
  }

  return head;
}