#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
* Prints node data
* args: void* data
* returns: none
*/
typedef void (*fp_print)(void*);

/*
* EDGE struct
*/
typedef struct edge
{
    int dst;
    int weight;
    struct edge* next;
}
edge_t;

/*
* VERTEX struct
*/
typedef struct vertex
{
    void* data;
    edge_t* head;
}
vertex_t;

/*
* GRAPH struct
*/
typedef struct graph
{
    int capacity;
    vertex_t* adjlist;
    fp_print print_func;
}
graph_t;

graph_t* graph_init(int capacity, fp_print print_func);
void graph_destroy(graph_t** graph);

edge_t* graph_find_edge(graph_t* graph, int src, int dst);
int graph_add_edge(graph_t* graph, int src, int dst, int weight);
int graph_remove_edge(graph_t* graph, int src, int dst);
void* graph_find_vertex(graph_t* graph, int src);
int graph_set_vertex(graph_t* graph, int dst, void* data);
int graph_clear_vertex(graph_t* graph, int src);

int graph_dijkstra(graph_t* graph, int src, int dst);

void graph_print(graph_t* graph);

#endif
