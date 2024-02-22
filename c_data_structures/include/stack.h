#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* STACK struct
*/
typedef struct stack
{
    void** array;
    int top;
    int capacity;
    fp_print print_func;
}
stack_t;

stack_t* stack_init(int capacity, fp_print print_func);
void stack_destroy(stack_t** stack);

int stack_find(stack_t* stack, void* data);
void* stack_peek(stack_t* stack);
int stack_push(stack_t* stack, void* data);
void* stack_pop(stack_t* stack);
void stack_empty(stack_t* stack);

void stack_print(stack_t* stack);

#endif
