#include "include/pqueue.h"

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

    /*** PQUEUE TESTING START ***/

    pq_t* pq = pq_init(int_print);

    pq_print(pq);

    pq_enqueue(pq, data[0], 1);

    pq_print(pq);

    pq_empty(pq);
    pq_print(pq);

    pq_enqueue(pq, data[9], 2);
    pq_enqueue(pq, data[1], 1);
    pq_enqueue(pq, data[2], 1);
    pq_enqueue(pq, data[3], 1);
    pq_enqueue(pq, data[4], 4);
    pq_enqueue(pq, data[5], 3);
    pq_enqueue(pq, data[6], 2);
    pq_enqueue(pq, data[7], 4);
    pq_enqueue(pq, data[8], 3);

    pq_print(pq);

    void* peek = pq_peek(pq);
    printf("\nHead of Priority Queue: ");
    if (NULL != peek)
    {
        int_print(peek);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    pq_dequeue(pq);
    pq_dequeue(pq);
    pq_dequeue(pq);

    pq_print(pq);

    pq_enqueue(pq, data[0], 1);
    pq_dequeue(pq);
    pq_dequeue(pq);
    pq_enqueue(pq, data[1], 3);

    pq_print(pq);

    pq_destroy(&pq);

    pq_print(pq);

    /*** PQUEUE TESTING END ***/

    printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        free(data[i]);
    }
    free(data);
}