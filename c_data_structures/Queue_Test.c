#include "include/queue.h"

void int_print(void* a)
{
    printf("%d", *(int *)a);
}

int main(void)
{
    int** data = calloc(10, sizeof(int*));

    for (int i = 0; i < 10; ++i)
    {
        data[i] = calloc(1, sizeof(int));
        *data[i] = i;
    }

    /*** QUEUE TESTING START ***/

    queue_t* q = queue_init(int_print);

    queue_print(q);

    queue_push(q, data[0]);

    queue_print(q);

    queue_empty(q);
    queue_print(q);

    queue_push(q, data[2]);
    queue_push(q, data[4]);
    queue_push(q, data[6]);
    queue_push(q, data[8]);

    queue_print(q);

    printf("\nIndex of %d: %d\n", *data[4], queue_find(q, data[4]));
    printf("\nIndex of %d: %d\n", *data[9], queue_find(q, data[9]));

    queue_pop(q);
    queue_pop(q);
    queue_pop(q);

    queue_print(q);

    queue_destroy(&q);

    queue_print(q);

    /*** QUEUE TESTING END ***/

    printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        free(data[i]);
    }
    free(data);
}