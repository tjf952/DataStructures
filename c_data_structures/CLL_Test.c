#include "include/clinked_list.h"

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

    /*** CLL TESTING START ***/

    cll_t* cll = cll_init(int_comp, int_print);

    cll_print(cll);

    cll_add(cll, data[0]);
    cll_add(cll, data[2]);

    cll_print(cll);
    
    cll_empty(cll);

    cll_print(cll);

    cll_add(cll, data[5]);
    cll_add(cll, data[1]);
    cll_add(cll, data[6]);
    cll_add(cll, data[4]);
    cll_add(cll, data[3]);

    cll_print(cll);

    printf("\nIndex of %d: %d\n", *data[4], cll_find(cll, data[4]));
    printf("\nIndex of %d: %d\n", *data[6], cll_find(cll, data[6]));
    printf("\nIndex of %d: %d\n", *data[9], cll_find(cll, data[9]));

    cll_remove(cll, 3);
    cll_remove(cll, 0);

    printf("\n[Testing for illegal remove] ");
    cll_remove(cll, 10);
    printf("\n");

    cll_print(cll);

    cll_insert(cll, 0, data[8]);
    cll_insert(cll, 4, data[7]);

    printf("\n[Testing for illegal insert] ");
    cll_insert(cll, -1, data[9]);
    printf("\n");

    cll_print(cll);
    
    cll_sort(cll);

    cll_print(cll);

    cll_destroy(&cll);

    cll_print(cll);

    /*** CLL TESTING END ***/

    printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        free(data[i]);
    }
    free(data);
}