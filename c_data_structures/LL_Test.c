#include "include/linked_list.h"

int int_comp(void* a, void* b)
{
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    if (int_a == int_b)
    {
        return 0;
    }
    else if (int_a > int_b)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

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

    /*** ll TESTING START ***/

    ll_t* ll = ll_init(int_comp, int_print);

    ll_print(ll);

    ll_add(ll, data[0]);
    ll_add(ll, data[2]);

    ll_print(ll);
    
    ll_empty(ll);

    ll_print(ll);

    ll_add(ll, data[5]);
    ll_add(ll, data[1]);
    ll_add(ll, data[6]);
    ll_add(ll, data[4]);
    ll_add(ll, data[3]);

    ll_print(ll);

    printf("\nIndex of %d: %d\n", *data[4], ll_find(ll, data[4]));
    printf("\nIndex of %d: %d\n", *data[6], ll_find(ll, data[6]));
    printf("\nIndex of %d: %d\n", *data[9], ll_find(ll, data[9]));

    ll_remove(ll, 3);
    ll_remove(ll, 0);

    printf("\n[Testing for illegal remove] ");
    ll_remove(ll, 10);
    printf("\n");

    ll_print(ll);

    ll_insert(ll, 0, data[8]);
    ll_insert(ll, 2, data[7]);

    printf("\n[Testing for illegal insert] ");
    ll_insert(ll, -1, data[9]);
    printf("\n");

    ll_print(ll);
    
    ll_sort(ll);

    ll_print(ll);

    ll_reverse(ll);

    ll_print(ll);

    ll_destroy(&ll);

    ll_print(ll);

    /*** ll TESTING END ***/

    printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        free(data[i]);
    }
    free(data);
}