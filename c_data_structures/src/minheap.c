#include "../include/minheap.h"

/*
* Constructor for MINHEAP_NODE
*/
minheap_node_t* minheap_node_init(int v, int dist)
{
    minheap_node_t* mn = malloc(sizeof(minheap_node_t));

    mn->v = v;
    mn->dist = dist;

    return mn;
}

/*
* Constructor for MINHEAP
*/
minheap_t* minheap_init(int capacity)
{
    minheap_t* m = malloc(sizeof(minheap_t));

    m->pos = malloc(capacity * sizeof(int));
    m->size = 0;
    m->capacity = capacity;
    m->array = malloc(capacity * sizeof(minheap_node_t*));

    for (int i = 0; i < capacity; ++i)
    {
        m->array[i] = NULL;
    }

    return m;
}

/*
* Deconstructor for MINHEAP
*/
void minheap_destroy(minheap_t* m)
{
    if (m != NULL)
    {
        minheap_node_t* min = NULL;
        
        while(minheap_empty(m) == 0)
        {
            min = minheap_min(m);
            free(min);
            min = NULL;
        }

        free(m->pos);
        free(m->array);
        free(m);
    }
}

/*
* Swaps two nodes of minheap
*/
void minheap_swap(minheap_node_t** a, minheap_node_t** b)
{
    minheap_node_t* t = *a;
    *a = *b;
    *b = t;
}

/*
* Heapify minheap to update positions to satisfy structure requirements
*/
void minheap_heapify(minheap_t* m, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < m->size && m->array[left]->dist < m->array[smallest]->dist)
    {
        smallest = left;
    }

    if (right < m->size && m->array[right]->dist < m->array[smallest]->dist)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        minheap_node_t* smallest_node = m->array[smallest];
        minheap_node_t* idx_node = m->array[idx];

        m->pos[smallest_node->v] = idx;
        m->pos[idx_node->v] = smallest;

        minheap_swap(&m->array[smallest], &m->array[idx]);
        minheap_heapify(m, smallest);
    }
}

/*
* Check if minheap is empty
*/
int minheap_empty(minheap_t* m)
{
    return m->size == 0;
}

/*
* Get minimum node from minheap
*/
minheap_node_t* minheap_min(minheap_t* m)
{
    if (minheap_empty(m))
    {
        return NULL;
    }

    minheap_node_t* root = m->array[0];
    minheap_node_t* last = m->array[m->size -1];
    m->array[0] = last;

    m->pos[root->v] = m->size-1;
    m->pos[last->v] = 0;

    --m->size;
    minheap_heapify(m, 0);

    return root;
}

/*
* Decreases the dist value of a given vertex v in minheap
*/
void minheap_decrease_key(minheap_t* m, int v, int dist)
{
    int i = m->pos[v];
    m->array[i]->dist = dist;

    while (i && m->array[i]->dist < m->array[(i-1)/2]->dist)
    {
        m->pos[m->array[i]->v] = (i-1) / 2;
        m->pos[m->array[(i-1)/2]->v] = i;
        minheap_swap(&m->array[i], &m->array[(i-1)/2]);
        i = (i-1) / 2;
    }
}

/*
* Check if vertex is in minheap
*/
int minheap_find(minheap_t* m, int v)
{
    if (m->pos[v] < m->size)
    {
        return 1;
    }

    return 0;
}
