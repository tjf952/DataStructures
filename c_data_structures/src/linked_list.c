#include "../include/linked_list.h"

/*
* Constructor for NODE
* data: void* argument to act as template
* returns: a new node object
*/
static ll_node_t* ll_node_init(void* data)
{
    ll_node_t* node = calloc(1, sizeof(ll_node_t));

    if (NULL == node)
    {
        fprintf(stderr, "[Error: ll_node_init() failed]\n");
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
static void ll_node_destroy(ll_node_t* n)
{
    if (NULL == n)
    {
        return;
    }

    free(n);
    n = NULL;
}

/*
* Constructor for ll
* comp_func: a function that compares two ll_node data values
* returns: a new ll object
*/
ll_t* ll_init(fp_comp comp_func, fp_print print_func)
{
    if (NULL == comp_func || NULL == print_func)
    {
        fprintf(stderr, "[Error: comp_func or print_func are NULL]\n");
        return NULL;
    }

    ll_t* ll = calloc(1, sizeof(ll_t));

    if (NULL == ll)
    {
        fprintf(stderr, "[Error: ll_init() failed]\n");
        return NULL;
    }

    ll->head = NULL;
    ll->size = 0;
    ll->node_compare = comp_func;
    ll->node_print = print_func;

    return ll;
}

/*
* Deconstructor for ll
* list: an existing ll object
* returns: none
*/
void ll_destroy(ll_t** list)
{
    if (NULL == list || NULL == *list)
    {
        return;
    }

    ll_empty(*list);
    free(*list);
    *list = NULL;
}

/*
* Finds the first occurence of the specified data
* list: an existing ll object
* data: value to find in ll
* returns: index in ll or -1 if not found
*/
int ll_find(ll_t* list, void* data)
{
    if (NULL == list || NULL == list->head)
    {
        return -1;
    }

    int i = 0;
    ll_node_t* head = list->head;

    while (head->next != NULL)
    {
        if (head->data == data)
        {
            return i;
        }

        head = head->next;
        ++i;
    }

    return -1;
}

/*
* Inserts new node at ending of ll object
* list: an existing ll object
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int ll_add(ll_t* list, void* data)
{
    if (NULL == list)
    {
        fprintf(stderr, "[Error: NULL list]\n");
        return -1;
    }

    ll_node_t* node = ll_node_init(data);

    if (NULL == node)
    {
        return -1;
    }

    if (NULL == list->head)
    {
        list->head = node;
    }
    else
    {
        ll_node_t* ref = list->head;

        while (ref->next != NULL)
        {
            ref = ref->next;
        }

        ref->next = node;
    }

    list->size += 1;
    return 1;
}

/*
* Inserts node at index loc in reference to last
* ll is as follows: [0] -> [1] -> ... -> [n-2] -> [n-1 (last)] -> wraps
* list: an existing ll object
* loc: index to insert at
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int ll_insert(ll_t* list, int loc, void* data)
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

    if (NULL == list->head || loc == list->size)
    {
        ll_add(list, data);
    }
    else
    {
        int i;
        ll_node_t* ref = list->head;
        ll_node_t* node = ll_node_init(data);

        if (NULL == node)
        {
            return -1;
        }

        if (loc == 0)
        {
            node->next = ref;
            list->head = node;
        }
        else
        {
            for (i = 0; i < loc-1; ++i)
            {
                ref = ref->next;
            }

            node->next = ref->next;
            ref->next = node;
        }

        list->size += 1;
    }

    return 1;
}

/*
* Removes node at selected index loc in referece to head
* list: an existing ll object
* loc: index to remove at
* returns: void* data from deleted node
*/
void* ll_remove(ll_t* list, int loc)
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
    ll_node_t* ref = list->head;
    ll_node_t* temp = NULL;

    if (list->size == 1)
    {
        data = ref->data;
        temp = ref;
        list->head = NULL;
    }
    else if (loc == 0)
    {
        data = ref->data;
        list->head = ref->next;
        temp = ref;
    }
    else
    {
        for (i = 0; i < loc-1; ++i)
        {
            ref = ref->next;
        }

        temp = ref->next;
        data = temp->data;
        ref->next = temp->next;
    }        
        
    ll_node_destroy(temp);
    list->size -= 1;

    return data;
}

/*
* Removes and frees all nodes from ll
* list: an exisitng ll object
* returns: none
*/
void ll_empty(ll_t* list)
{
    if (NULL == list)
    {
        return;
    }

    while (NULL != list->head)
    {
        ll_remove(list, 0);
    }
}

/*
* Sorts ll by swapping data
* list: an existing ll object
* returns: none
*/
void ll_sort(ll_t* list)
{
    if (NULL == list || list->size < 2)
    {
        return;
    }

    ll_node_t* current = list->head;
    ll_node_t* index = NULL;
    void* temp;

    do
    {
        index = current->next;

        while (NULL != index)
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
    while (NULL != current->next);
}

/*
* Reverses ll by changing having each nodes next point to prev
* list: an existing ll object
* returns: none
*/
void ll_reverse(ll_t* list)
{
    if (NULL == list || list->size < 2)
    {
        return;
    }

    ll_node_t* prev = NULL;
    ll_node_t* next = NULL;
    ll_node_t* head = list->head;

    while (NULL != head)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    list->head = prev;
}

/*
* Prints the ll from index 0 to last element
* list: an existing ll object
* returns: none
*/
void ll_print(ll_t* list)
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
        list->node_print(list->head);
        printf("]->\n");
    }
    else
    {
        ll_node_t* ref = list->head;

        do
        {
            printf("[Data: ");
            list->node_print(ref->data);
            printf("]->");
            ref = ref->next;
        }
        while (NULL != ref);

        printf("\n");
    }
}
