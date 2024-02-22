#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

/*
* Hashes void* data using table size
* args: int representing table size, void* representing data
* returns: integer hash that lies within bounds of table size
*/
typedef int (*fp_hash)(int, void*);

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* HT_NODE struct
*/
typedef struct ht_node
{
    void* data;
    struct ht_node* next;
}
ht_node_t;

/*
* HASHTABLE struct
*/
typedef struct ht
{
    int table_size;
    ht_node_t** table;
    fp_hash hash_func;
    fp_print print_func;
}
ht_t;

ht_t* ht_init(int size, fp_hash hash_func, fp_print print_func);
void ht_destroy(ht_t** ht);

ht_node_t* ht_get(ht_t* ht, int key);
int ht_search(ht_t* ht, void* data);
void* ht_remove(ht_t*ht, void* data);
int ht_insert(ht_t* ht, void* data);
void ht_empty(ht_t* ht);

void ht_print(ht_t* ht);

#endif
