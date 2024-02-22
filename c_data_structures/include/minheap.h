#ifndef _MINHEAP_H
#define _MINHEAP_H

#include <stdio.h>
#include <stdlib.h>

// Reference: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/

/*
* MINHEAP_NODE struct
*/
typedef struct minheap_node
{
    int v;
    int dist;
}
minheap_node_t;

/*
* MINHEAP struct
*/
typedef struct minheap
{
    int size;
    int capacity;
    int* pos;
    minheap_node_t** array;
}
minheap_t;

minheap_node_t* minheap_node_init(int v, int dist);
minheap_t* minheap_init(int capacity);
void minheap_destroy(minheap_t* mp);

void minheap_swap(minheap_node_t** a, minheap_node_t** b);
void minheap_heapify(minheap_t* m, int idx);
int minheap_empty(minheap_t* m);
minheap_node_t* minheap_min(minheap_t* m);
void minheap_decrease_key(minheap_t* m, int v, int dist);
int minheap_find(minheap_t* m, int v);

#endif