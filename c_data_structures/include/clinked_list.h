#ifndef _CLINKED_LIST_H
#define _CLINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

/*
* Compares two node data values
* args: void* data
* returns: -1 if arg1 < arg2; 0 if arg1 = arg2; 1 if arg1 > arg2
*/
typedef int (*fp_comp)(void*, void*);

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* CLL_NODE struct
*/
typedef struct cll_node
{
    void* data;
    struct cll_node* next;
}
cll_node_t;

/*
* CLINKED_LIST struct
*/
typedef struct cll
{
    cll_node_t* last;
    int size;
    fp_comp node_compare;
    fp_print node_print;
}
cll_t;

cll_t* cll_init(fp_comp comp_func, fp_print print_func);
void cll_destroy(cll_t** list);

int cll_find(cll_t* list, void* data);
int cll_add(cll_t* list, void* data);
int cll_insert(cll_t* list, int loc, void* data);
void* cll_remove(cll_t* list, int loc);
void cll_empty(cll_t* list);

void cll_sort(cll_t* list);
void cll_print(cll_t* list);

#endif
