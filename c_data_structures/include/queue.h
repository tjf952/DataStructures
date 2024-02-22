#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* QNODE struct
*/
typedef struct queue_node
{
    void* data;
    struct queue_node* next;
}
queue_node_t;

/*
* QUEUE struct
*/
typedef struct queue
{
    queue_node_t* head;
    queue_node_t* tail;
    fp_print node_print;
}
queue_t;

queue_t* queue_init(fp_print print_func);
void queue_destroy(queue_t** q);

int queue_find(queue_t* q, void* data);
int queue_push(queue_t* q, void* data);
void* queue_pop(queue_t* q);
void queue_empty(queue_t* q);

void queue_print(queue_t* q);

#endif
