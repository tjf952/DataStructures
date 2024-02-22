#include "../include/queue.h"

/*
* Constructor for QNODE
* data: void* argument to act as a template
* returns: a new queue_node object
*/
static queue_node_t* queue_node_init(void* data)
{
    queue_node_t* qn = calloc(1, sizeof(queue_node_t));

    if (NULL == qn)
    {
        fprintf(stderr, "[Error: queue_node_init() failed]\n");
        return NULL;
    }

    qn->data = data;
    qn->next = NULL;

    return qn;
}

/*
* Deconstructor for QNODE
* qn: an existing node object
* returns: none
*/
static void queue_node_destroy(queue_node_t* qn)
{
    if (NULL == qn)
    {
        return;
    }

    free(qn);
    qn = NULL;
}

/* 
* Constructor for QUEUE
* returns: a new queue object
*/
queue_t* queue_init(fp_print print_func)
{
    if (NULL == print_func)
    {
        fprintf(stderr, "[Error: print_func is NULL]\n");
        return NULL;
    }

    queue_t* q = calloc(1, sizeof(queue_t));

    if (NULL == q)
    {
        fprintf(stderr, "[Error: queue_init() failed]\n");
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->node_print = print_func;

    return q;
}

/*
* Deconstructor for QUEUE
* q: an existing queue object
* returns: none
*/
void queue_destroy(queue_t** q)
{
    if (NULL == q || NULL == *q)
    {
        return;
    }

    queue_empty(*q);
    free(*q);
    *q = NULL;
}

/*
* Finds the first occurence of the specified data
* q: an existing queue object
* data: value to find in queue
* returns: the index of the value in the queue or -1 if not found
*/
int queue_find(queue_t* q, void* data)
{
    if (NULL == q)
    {
        return -1;
    }

    int i = 0;
    queue_node_t* temp = q->head;

    while (NULL != temp)
    {
        if (temp->data == data)
        {
            return i;
        }
        temp = temp->next;
        i += 1;
    }

    return -1;
}

/*
* Inserts a new node into back of queue
* q: an existing queue object
* data: void* argument to be passed to new node
* returns: 1 on success or -1 on failure
*/
int queue_push(queue_t* q, void* data)
{
    if (NULL == q)
    {
        fprintf(stderr, "[Error: NULL queue]\n");
        return -1;
    }

    queue_node_t* qn = queue_node_init(data);

    if (NULL == qn)
    {
        return -1;
    }

    if (NULL == q->tail)
    {
        q->head = qn;
        q->tail = qn;
    }
    else
    {
        q->tail->next = qn;
        q->tail = qn;
    }

    return 1;
}

/*
* Removes node from front of queue
* q: an existing queue object
* returns: void* data from deleted node
*/
void* queue_pop(queue_t* q)
{
    if (NULL == q || NULL == q->head)
    {
        return NULL;
    }

    queue_node_t* qn = q->head;
    void* data = qn->data;
    q->head = q->head->next;

    if (NULL == q->head)
    {
        q->tail = NULL;
    }

    queue_node_destroy(qn);
    return data;
}

/*
* Removes and frees all nodes from queue
* q: an exisitng queue object
* returns: none
*/
void queue_empty(queue_t* q)
{
    if (NULL == q)
    {
        return;
    }

    while (q->head)
    {
        queue_pop(q);
    }
}

/*
* Prints the queue from head to tail
* q: an existing queue object
* returns: none
*/
void queue_print(queue_t* q)
{
    if (NULL == q || NULL == q->head)
    {
        printf("\nQueue: -Empty Queue-\n");
        return;
    }
    
    queue_node_t* temp = q->head;
    printf("\nQueue: ");

    while (temp)
    {
        printf("[Data: ");
        q->node_print(temp->data);
        printf("]->");
        temp = temp->next;
    }

    printf("[NULL]\n");
}
