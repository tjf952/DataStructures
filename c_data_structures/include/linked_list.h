#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

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
* LL_NODE struct
*/
typedef struct ll_node
{
    void* data;
    struct ll_node* next;
}
ll_node_t;

/*
* LINKED_LIST struct
*/
typedef struct ll
{
    ll_node_t* head;
    int size;
    fp_comp node_compare;
    fp_print node_print;
}
ll_t;

ll_t* ll_init(fp_comp comp_func, fp_print print_func);
void ll_destroy(ll_t** list);

int ll_find(ll_t* list, void* data);
int ll_add(ll_t* list, void* data);
int ll_insert(ll_t* list, int loc, void* data);
void* ll_remove(ll_t* list, int loc);
void ll_empty(ll_t* list);

void ll_sort(ll_t* list);
void ll_reverse(ll_t* list);
void ll_print(ll_t* list);

#endif
