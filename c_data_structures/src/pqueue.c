#include "../include/pqueue.h"

/*
* Constructor for PQ_NODE
* data: void* argument to act as a template
* returns: a new pq_node object
*/
static pq_node_t* pq_node_init(void* data, int priority)
{
    pq_node_t* node = calloc(1, sizeof(pq_node_t));

    if (NULL == node)
    {
        fprintf(stderr, "[Error: pq_node_init() failed]\n");
        return NULL;
    }

    node->data = data;
    node->priority = priority;
    node->next = NULL;

    return node;
}

/*
* Deconstructor for PQ_NODE
* node: an existing node object pointer
* returns: none
*/
static void pq_node_destroy(pq_node_t** node)
{
    if (NULL == node || NULL == *node)
    {
        return;
    }

    free(*node);
    *node = NULL;
}

/* 
* Constructor for PQUEUE
* print_func: user made print function to print void* data
* returns: a new pq object
*/
pq_t* pq_init(fp_print print_func)
{
    if (NULL == print_func)
    {
        fprintf(stderr, "[Error: print_func is NULL]\n");
        return NULL;
    }

    pq_t* pq = calloc(1, sizeof(pq_t));

    if (NULL == pq)
    {
        fprintf(stderr, "[Error: pq_init() failed]\n");
        return NULL;
    }

    pq->head = NULL;
    pq->node_print = print_func;

    return pq;
}

/*
* Deconstructor for PQUEUE
* pq: an existing pq object pointer
* returns: none
*/
void pq_destroy(pq_t** pq)
{
    if (NULL == pq || NULL == *pq)
    {
        return;
    }

    pq_empty(*pq);
    free(*pq);
    *pq = NULL;
}

/*
* Get the highest priority element without removing it
* pq: an existing pq object
* returns: the value at the highest priority element else NULL
*/
void* pq_peek(pq_t* pq)
{
    if (NULL == pq || NULL == pq->head)
    {
        return NULL;
    }

    return pq->head->data;
}

/*
* Inserts a new node into the pq
* pq: an existing pq object
* data: void* argument to be passed to new node
* priority: priority of the node to be created
* returns: 1 on success or -1 on failure
*/
int pq_enqueue(pq_t* pq, void* data, int priority)
{
    if (NULL == pq)
    {
        fprintf(stderr, "[Error: NULL pq]\n");
        return -1;
    }

    pq_node_t* node = pq_node_init(data, priority);

    if (NULL == node)
    {
        return -1;
    }

    if (NULL == pq->head)
    {
        pq->head = node;
    }
    else if (pq->head->priority > priority)
    {
        node->next = pq->head;
        pq->head = node;
    }
    else
    {
        pq_node_t* curr = pq->head;

        while (NULL != curr->next && curr->next->priority < priority+1)
        {
            curr = curr->next;
        }

        node->next = curr->next;
        curr->next = node;
    }

    return 1;
}

/*
* Removes node with the highest priority from the pq
* pq: an existing pq object
* returns: void* data from deleted node
*/
void* pq_dequeue(pq_t* pq)
{
    if (NULL == pq || NULL == pq->head)
    {
        return NULL;
    }

    pq_node_t* temp = pq->head;
    void* data = temp->data;
    pq->head = pq->head->next;
    pq_node_destroy(&temp);

    return data;
}

/*
* Removes and frees all nodes from pq
* pq: an exisitng pq object
* returns: none
*/
void pq_empty(pq_t* pq)
{
    if (NULL == pq)
    {
        return;
    }

    while (pq->head)
    {
        pq_dequeue(pq);
    }
}

/*
* Prints the pq from head to tail
* pq: an existing pq object
* returns: none
*/
void pq_print(pq_t* pq)
{
    if (NULL == pq || NULL == pq->head)
    {
        printf("\n=== EMPTY PRIORITY QUEUE ===\n");
        return;
    }
    
    pq_node_t* temp = pq->head;
    printf("\n=== PRIORITY QUEUE ===\n");

    while (temp)
    {
        printf("[Priority: %d | Data: ", temp->priority);
        pq->node_print(temp->data);
        printf("]\n");
        temp = temp->next;
    }

    printf("[Priority: - | Data: NULL]\n======== END ========\n");
}
