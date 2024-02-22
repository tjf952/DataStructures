#include "include/bstree.h"

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

    /*** BST TESTING START ***/

    bst_t* bst = bst_init(int_comp, int_print);

    bst_insert(bst, data[0]);
    bst_insert(bst, data[0]);
    bst_insert(bst, data[9]);

    bst_print(bst);

    bst_empty(bst);
    
    bst_print(bst);

    bst_insert(bst, data[5]);
    bst_insert(bst, data[3]);
    bst_insert(bst, data[7]);
    bst_insert(bst, data[1]);
    bst_insert(bst, data[4]);
    bst_insert(bst, data[2]);
    bst_insert(bst, data[6]);
    bst_insert(bst, data[8]);

    bst_print(bst);

    if (NULL != bst_search(bst, data[2]))
    {
        printf("\nTree contains %d\n", *data[2]);
    }
    else
    {
        printf("\nTree does not contain %d\n", *data[2]);
    }

    if (NULL != bst_search(bst, data[9]))
    {
        printf("\nTree contains %d\n", *data[2]);
    }
    else
    {
        printf("\nTree does not contain %d\n", *data[9]);
    }

    bst_delete(bst, data[5]);
    bst_delete(bst, data[3]);
    bst_delete(bst, data[0]);
    bst_delete(bst, data[1]);
    bst_delete(bst, data[5]);

    bst_print(bst);
    
    bst_destroy(&bst);

    bst_print(bst);

    /*** BST TESTING END ***/

    printf("\n");

    for (int i = 0; i < 10; ++i)
    {
        free(data[i]);
    }
    free(data);
}