#include "include/hashtable.h"

int int_hash(int size, void* a)
{
    int int_a = *(int *)a;

    return int_a % size;
}

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

    /*** HASHTABLE TESTING START ***/

    ht_t* ht = ht_init(5, int_hash, int_print);

    ht_print(ht);

    ht_insert(ht, data[2]);
    ht_insert(ht, data[5]);
    ht_insert(ht, data[10]);
    ht_insert(ht, data[15]);
    ht_insert(ht, data[4]);

    ht_print(ht);

    printf("\nIndex of %d: %d\n", *data[2], ht_search(ht, data[2]));
    printf("\nIndex of %d: %d\n", *data[10], ht_search(ht, data[10]));
    printf("\nIndex of %d: %d\n", *data[16], ht_search(ht, data[16]));

    ht_empty(ht);

    ht_print(ht);

    ht_insert(ht, data[7]);
    ht_insert(ht, data[13]);
    ht_insert(ht, data[9]);
    ht_insert(ht, data[3]);
    ht_insert(ht, data[6]);
    ht_insert(ht, data[8]);
    ht_insert(ht, data[17]);
    ht_insert(ht, data[12]);

    ht_print(ht);

    ht_node_t* get = ht_get(ht, 3);
    printf("\nNode at key %d: ", 3);
    if (NULL != get)
    {
        int_print(get->data);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    get = ht_get(ht, 0);
    printf("Node at key %d: ", 0);
    if (NULL != get)
    {
        int_print(get->data);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    get = ht_get(ht, 8);
    printf("Node at key %d: ", 8);
    if (NULL != get)
    {
        int_print(get->data);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    ht_remove(ht, data[6]);
    ht_remove(ht, data[17]);
    ht_remove(ht, data[8]);
    ht_remove(ht, data[19]);
    ht_remove(ht, data[0]);

    ht_print(ht);

    ht_destroy(&ht);

    ht_print(ht);

    /*** HASHTABLE TESTING END ***/

    printf("\n");

    for (int i = 0; i < 20; ++i)
    {
        free(data[i]);
    }
    free(data);
}