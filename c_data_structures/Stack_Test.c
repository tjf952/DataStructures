#include "include/stack.h"

void int_print(void* a)
{
    printf("%d", *(int *)a);
}

int main(void)
{
    int** data = calloc(20, sizeof(int*));

    for (int i = 0; i < 20; ++i)
    {
        data[i] = calloc(1, sizeof(int));
        *data[i] = i;
    }

    /*** QUEUE TESTING START ***/

    stack_t* stack = stack_init(5, int_print);

    stack_print(stack);

    stack_push(stack, data[0]);

    stack_print(stack);

    stack_empty(stack);

    stack_print(stack);

    stack_push(stack, data[2]);
    stack_push(stack, data[4]);
    stack_push(stack, data[6]);
    stack_push(stack, data[8]);
    stack_push(stack, data[10]);

    printf("\nTrying to do stack overrun\n");
    stack_push(stack, data[12]);

    stack_print(stack);

    printf("\nIndex of %d: %d\n", *data[4], stack_find(stack, data[4]));
    printf("\nIndex of %d: %d\n", *data[9], stack_find(stack, data[9]));

    void* top = stack_peek(stack);
    printf("\nTop of stack: ");
    int_print(top);
    printf("\n");

    stack_pop(stack);
    stack_pop(stack);
    stack_pop(stack);

    stack_print(stack);

    stack_destroy(&stack);

    stack_print(stack);

    /*** QUEUE TESTING END ***/

    printf("\n");

    for (int i = 0; i < 20; ++i)
    {
        free(data[i]);
    }
    free(data);
}