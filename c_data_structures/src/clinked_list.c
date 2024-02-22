#include "../include/clinked_list.h"

/*
* Constructor for NODE
* data: void* argument to act as template
* returns: a new node object
*/
static cll_node_t* cll_node_init(void* data)
{
    cll_node_t* node = calloc(1, sizeof(cll_node_t));

    if (NULL == node)
    {
        fprintf(stderr, "[Error: cll_node_init() failed]\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    
    return node;
}

/*
* Deconstructor for NODE
* n: an existing node object
* returns: none
*/
static void cll_node_destroy(cll_node_t* n)
{
    if (NULL == n)
    {
        return;
    }

    free(n);
    n = NULL;
}

/*
* Constructor for CLL
* comp_func: a function that compares two cll_node data values
* returns: a new cll object
*/
cll_t* cll_init(fp_comp comp_func, fp_print print_func)
{
    if (NULL == comp_func || NULL == print_func)
    {
        fprintf(stderr, "[Error: comp_func or print_func are NULL]\n");
        return NULL;
    }

    cll_t* cll = calloc(1, sizeof(cll_t));

    if (NULL == cll)
    {
        fprintf(stderr, "[Error: cll_init() failed]\n");
        return NULL;
    }

    cll->last = NULL;
    cll->size = 0;
    cll->node_compare = comp_func;
    cll->node_print = print_func;

    return cll;
}

/*
* Deconstructor for CLL
* list: an existing cll object
* returns: none
*/
void cll_destroy(cll_t** list)
{
    if (NULL == list || NULL == *list)
    {
        return;
    }

    cll_empty(*list);
    free(*list);
    *list = NULL;
}

/*
* Finds the first occurence of the specified data
* list: an existing cll object
* data: value to find in cll
* returns: index in cll or -1 if not found
*/
int cll_find(cll_t* list, void* data)
{
    if (NULL == list || NULL == list->last)
    {
        return -1;
    }

    if (list->last->data == data)
    {
        return list->size - 1;
    }

    int i = 0;
    cll_node_t* ref = list->last;

    while (ref->next != list->last)
    {
        ref = ref->next;

        if (ref->data == data)
        {
            return i;
        }

        ++i;
    }

    return -1;
}

/*
* Inserts new node at ending of cll object
* list: an existing cll object
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int cll_add(cll_t* list, void* data)
{
    if (NULL == list)
    {
        fprintf(stderr, "[Error: NULL list]\n");
        return -1;
    }

    cll_node_t* node = cll_node_init(data);

    if (NULL == node)
    {
        return -1;
    }

    if (NULL == list->last)
    {
        list->last = node;
        node->next = list->last;
    }
    else
    {
        node->next = list->last->next;
        list->last->next = node;
        list->last = node;
    }

    list->size += 1;
    return 1;
}

/*
* Inserts node at index loc in reference to last
* cll is as follows: [0] -> [1] -> ... -> [n-2] -> [n-1 (last)] -> wraps
* list: an existing cll object
* loc: index to insert at
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int cll_insert(cll_t* list, int loc, void* data)
{   
    if (NULL == list)
    {
        fprintf(stderr, "[Error: NULL list]\n");
        return -1;
    }

    if (loc > list->size || loc < 0)
    {
        fprintf(stderr, "[Error: loc %d is out of bounds]", loc);
        return -1;
    }

    if (NULL == list->last || loc == list->size)
    {
        cll_add(list, data);
    }
    else
    {
        int i;
        cll_node_t* ref = list->last;
        cll_node_t* node = cll_node_init(data);

        if (NULL == node)
        {
            return -1;
        }

        for (i = 0; i < loc; ++i)
        {
            ref = ref->next;
        }

        node->next = ref->next;
        ref->next = node;

        list->size += 1;
    }

    return 1;
}

/*
* Removes node at selected index loc in referece to last
* cll is as follows: [0] -> [1] -> ... -> [n-2] -> [n-1 (last)] -> wraps
* list: an existing cll object
* loc: index to remove at
* returns: void* data from deleted node
*/
void* cll_remove(cll_t* list, int loc)
{
    if (NULL == list)
    {
        fprintf(stderr, "[Error: NULL list]\n");
        return NULL;
    }

    if (loc > list->size - 1 || loc < 0)
    {
        fprintf(stderr, "[Error: loc %d is out of bounds]", loc);
        return NULL;
    }

    int i;
    void* data;
    cll_node_t* ref = list->last;
    cll_node_t* temp = NULL;

    if (list->size == 1)
    {
        data = list->last->data;
        cll_node_destroy(list->last);
        list->last = NULL;
    }
    else
    {
        for (i = 0; i < loc; ++i)
        {
            ref = ref->next;
        }

        if (ref->next == list->last)
        {
            list->last = ref;
        }

        temp = ref->next;
        ref->next = temp->next;
        data = temp->data;
        
        cll_node_destroy(temp);
    }

    list->size -= 1;

    return data;
}

/*
* Removes and frees all nodes from CLL
* list: an exisitng cll object
* returns: none
*/
void cll_empty(cll_t* list)
{
    if (NULL == list)
    {
        return;
    }

    while (NULL != list->last)
    {
        cll_remove(list, 0);
    }
}

/*
* Sorts cll by swapping data
* list: an existing cll object
* returns: none
*/
void cll_sort(cll_t* list)
{
    if (NULL == list || list->size < 2)
    {
        return;
    }

    cll_node_t* current = list->last->next;
    cll_node_t* index = NULL;
    void* temp;

    do
    {
        index = current->next;

        while (index != list->last->next)
        {
            if(list->node_compare(current->data, index->data) == 1)
            {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }

            index = index->next;
        }

        current = current->next;
    }
    while (current->next != list->last->next);
}

/*
* Prints the CLL from index 0 to last element
* list: an existing cll object
* returns: none
*/
void cll_print(cll_t* list)
{
    if (NULL == list || list->size < 1)
    {
        printf("\nList Size: 0 | -Empty List-\n");
        return;
    }

    printf("\nList size: %d | List: ", list->size);

    if (list->size == 1)
    {
        printf("[Data: ");
        list->node_print(list->last);
        printf("]->\n");
    }
    else
    {
        cll_node_t* ref = list->last->next;

        do
        {
            printf("[Data: ");
            list->node_print(ref->data);
            printf("]->");
            ref = ref->next;
        }
        while (ref != list->last->next);

        printf("\n");
    }
}
