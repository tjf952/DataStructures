#ifndef _PQUEUE_H
#define _PQUEUE_H

#include <stdio.h>
#include <stdlib.h>

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* PQ_NODE struct
*/
typedef struct pq_node
{
    void* data;
    int priority;
    struct pq_node* next;
}
pq_node_t;

/*
* PQUEUE struct
*/
typedef struct pq
{
    pq_node_t* head;
    fp_print node_print;
}
pq_t;

pq_t* pq_init(fp_print print_func);
void pq_destroy(pq_t** pq);

void* pq_peek(pq_t* pq);
int pq_enqueue(pq_t* pq, void* data, int priority);
void* pq_dequeue(pq_t* pq);
void pq_empty(pq_t* pq);

void pq_print(pq_t* pq);

#endif
