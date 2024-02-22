#include "../include/stack.h"

/* 
* Constructor for STACK
* capacity: maximum size for stack
* print_func: user made print function to print void* data
* returns: a new stack object
*/
stack_t* stack_init(int capacity, fp_print print_func)
{
    if (NULL == print_func)
    {
        fprintf(stderr, "[Error: print_func is NULL]\n");
        return NULL;
    }

    stack_t* stack = calloc(1, sizeof(stack_t));

    if (NULL == stack)
    {
        fprintf(stderr, "[Error: stack_init() failed]\n");
        return NULL;
    }

    stack->array = calloc(capacity, sizeof(void*));

    if (NULL == stack->array)
    {
        fprintf(stderr, "[Error: stack_init() failed due to array]\n");
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    stack->print_func = print_func;

    return stack;
}

/*
* Deconstructor for STACK
* stack: an existing stack object pointer
* returns: none
*/
void stack_destroy(stack_t** stack)
{
    if (NULL == stack || NULL == *stack)
    {
        return;
    }

    stack_empty(*stack);
    free((*stack)->array);
    (*stack)->array = NULL;
    free(*stack);
    *stack = NULL;
}

/*
* Checks if stack is full
*/
static int is_full(stack_t* stack)
{
    return stack->top == stack->capacity - 1;
}

/*
* Check is stack is empty
*/
static int is_empty(stack_t* stack)
{
    return stack->top == -1;
}

/*
* Finds the first occurence of the specified data
* stack: an existing stack object
* data: value to find in stack
* returns: the index of the value in the stack or -1 if not found
*/
int stack_find(stack_t* stack, void* data)
{
    if (NULL == stack)
    {
        fprintf(stderr, "[Error: NULL stack]\n");
        return -1;
    }

    if (is_empty(stack) == 1)
    {
        return -1;
    }

    for (int i = stack->top; i >= 0; --i)
    {
        if (data == stack->array[i])
        {
            return stack->top-i;
        }
    }

    return -1;
}

/*
* Returns the top from the stack without removing it
* stack: an existing stack object
* returns: the value at the top of the stack
*/
void* stack_peek(stack_t* stack)
{
    if (NULL == stack)
    {
        fprintf(stderr, "[Error: NULL stack]\n");
        return NULL;
    }

    if (is_empty(stack) == 1)
    {
        fprintf(stderr, "[Error: stack is empty]\n");\
        return NULL;
    }
    
    return stack->array[stack->top];
}


/*
* Inserts a new node into back of stack
* stack: an existing stack object
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int stack_push(stack_t* stack, void* data)
{
    if (NULL == stack)
    {
        fprintf(stderr, "[Error: NULL stack]\n");
        return -1;
    }

    if (is_full(stack))
    {
        fprintf(stderr, "[Error: stack is full]\n");
        return -1;
    }

    ++stack->top;
    stack->array[stack->top] = data;

    return 1;
}

/*
* Removes node from front of stack
* stack: an existing stack object
* returns: void* data from deleted node
*/
void* stack_pop(stack_t* stack)
{
    if (NULL == stack )
    {
        fprintf(stderr, "[Error: NULL stack]\n");
        return NULL;
    }

    if (is_empty(stack) == 1)
    {
        fprintf(stderr, "[Error: stack is empty]\n");
        return NULL;
    }

    void* data = stack->array[stack->top];
    --stack->top;

    return data;
}

/*
* Resets stack to an empty stack
* stack: an exisitng stack object
* returns: none
*/
void stack_empty(stack_t* stack)
{
    if (NULL == stack)
    {
        return;
    }

    stack->top = -1;
}

/*
* Prints the stack
* stack: an existing stack object
* returns: none
*/
void stack_print(stack_t* stack)
{
    if (NULL == stack)
    {
        printf("\n=== NULL STACK ===\n");
        return;
    }

    if (is_empty(stack) == 1)
    {
        printf("\n=== EMPTY STACK ===\n");
        return;
    }

    printf("\n=== STACK ===\n");

    for (int i = stack->top; i >= 0; --i)
    {
        printf("| Item %d: ", stack->top-i);
        stack->print_func(stack->array[i]);
        printf(" |\n");
    }

    printf("==== END ====\n");
}
