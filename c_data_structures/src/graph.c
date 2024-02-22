#include "../include/graph.h"
#include "../include/minheap.h"

/*
* Constructor for EDGE
* dst: the destination vertex
* weight: the weight of the edge 
* returns: a new edge object
*/
static edge_t* edge_init(int dst, int weight)
{
    edge_t* edge = calloc(1, sizeof(edge_t));

    if (NULL == edge)
    {
        fprintf(stderr, "[Error: edge_init() failed]\n");
        return NULL;
    }

    edge->dst = dst;
    edge->weight = weight;
    edge->next = NULL;

    return edge;
}

/*
* Deconstructor for EDGE
* edge: an existing edge object pointer
* returns: none
*/
static void edge_destroy(edge_t** edge)
{
    if (NULL == *edge)
    {
        return;
    }

    free(*edge);
    *edge = NULL;
}

/*
* Removes and frees all objects from graph
* graph: an existing graph object
* returns: none
*/
static void graph_empty(graph_t* graph)
{
    if (NULL == graph)
    {
        return;
    }

    edge_t* curr = NULL;
    edge_t* temp = NULL;

    for (int i = 0; i < graph->capacity; ++i)
    {
        curr = graph->adjlist[i].head;

        while (NULL != curr)
        {
            temp = curr;
            curr = curr->next;
            edge_destroy(&temp);
        }

        graph->adjlist[i].data = NULL;
        graph->adjlist[i].head = NULL;
    }
}

/*
* Prints dijkstra algorithm results
* dist: array holding dijkstra results
* size: size of dist
* returns: none
*/
static void dijkstra_print(int dist[], int size)
{
    printf("\n=== DIJKSTRA ===\n");
    printf("Vertex\tDistance from Source\n");

    for (int i = 0; i < size; ++i)
    {
        if (dist[i] == INT_MAX)
        {
            printf("Dst: %d\t\tDistance: INF\n", i);
        }
        else
        {
            printf("Dst: %d\t\tDistance: %d\n", i, dist[i]);
        }
    }

    printf("===== END =====\n");
} 

/* 
* Constructor for GRAPH
* capacity: max number of vertices in graph
* print_func: user made print function to print void* data
* returns: a new graph object
*/
graph_t* graph_init(int capacity, fp_print print_func)
{
    if (NULL == print_func)
    {
        fprintf(stderr, "[Error: print_func are NULL]\n");
        return NULL;
    }

    graph_t* graph = calloc(1, sizeof(graph_t));

    if (NULL == graph)
    {
        fprintf(stderr, "[Error: graph_init() failed due to graph]\n");
        return NULL;
    }

    graph->adjlist = calloc(capacity, sizeof(vertex_t));

    if (NULL == graph->adjlist)
    {
        fprintf(stderr, "[Error: graph_init() failed due to adjlist]\n");
        free(graph);
        return NULL;
    }

    for (int i = 0; i < capacity; ++i)
    {
        graph->adjlist[i].data = NULL;
        graph->adjlist[i].head = NULL;
    }

    graph->capacity = capacity;
    graph->print_func = print_func;

    return graph;
}

/*
* Deconstructor for GRAPH
* graph: an existing graph object pointer
* returns: none
*/
void graph_destroy(graph_t** graph)
{
    if (NULL == graph || NULL == *graph)
    {
        return;
    }

    graph_empty(*graph);
    free((*graph)->adjlist);
    (*graph)->adjlist= NULL;
    free(*graph);
    *graph = NULL;
}

/*
* Finds if the desired edge exists in the graph
* graph: an existing graph object
* src: the source vertex
* dst: the destination vertex
* returns: the edge if found else NULL
*/
edge_t* graph_find_edge(graph_t* graph, int src, int dst)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return NULL;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return NULL;
    }

    if (dst < 0 || dst >= graph->capacity)
    {
        fprintf(stderr, "[Error: dst vertex is out of bounds]\n");
        return NULL;
    }

    edge_t* curr = graph->adjlist[src].head;

    while (NULL != curr)
    {
        if (curr->dst == dst)
        {
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

/*
* Adds an edge between two vertices in the undirected graph
* graph: an existing graph object
* src: the source vertex
* dst: the destination vertex
* weight: the weight of the edge
* returns: 1 on success or -1 on failure
*/
int graph_add_edge(graph_t* graph, int src, int dst, int weight)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return -1;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return -1;
    }

    if (dst < 0 || dst >= graph->capacity)
    {
        fprintf(stderr, "[Error: dst vertex is out of bounds]\n");
        return -1;
    }

    if (NULL == graph->adjlist[src].data)
    {
        fprintf(stderr, "[Error: src vertex has not been created]\n");
        return -1;
    }

    if (NULL == graph->adjlist[dst].data)
    {
        fprintf(stderr, "[Error: dst vertex has not been created]\n");
        return -1;
    }

    edge_t* src_edge = edge_init(dst, weight);
    edge_t* dst_edge = edge_init(src, weight);

    if (NULL == src_edge || NULL == dst_edge)
    {
        if (NULL != src_edge)
        {
            edge_destroy(&src_edge);
        }

        if (NULL != dst_edge)
        {
            edge_destroy(&dst_edge);
        }
        
        return -1;
    }

    src_edge->next = graph->adjlist[src].head;
    graph->adjlist[src].head = src_edge;
    
    dst_edge->next = graph->adjlist[dst].head;
    graph->adjlist[dst].head = dst_edge;

    return 1;
}

/*
* Removes an edge between two vertices in the undirected graph
* graph: an existing graph object
* src: the source vertex
* dst: the destination vertex
* returns: 1 on success or -1 on failure
*/
int graph_remove_edge(graph_t* graph, int src, int dst)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return -1;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return -1;
    }

    if (dst < 0 || dst >= graph->capacity)
    {
        fprintf(stderr, "[Error: dst vertex is out of bounds]\n");
        return -1;
    }
    
    edge_t* temp = NULL;
    edge_t* curr = graph->adjlist[src].head;

    if (curr->dst == dst)
    {
        graph->adjlist[src].head = curr->next;
        edge_destroy(&curr);
    }
    else
    {
        while (NULL != curr->next)
        {
            if (curr->next->dst == dst)
            {
                temp = curr->next;
                curr->next = temp->next;
                edge_destroy(&temp);
                break;
            }
            curr = curr->next;
        }
    }

    curr = graph->adjlist[dst].head;

    if (curr->dst == src)
    {
        graph->adjlist[dst].head = curr->next;
        edge_destroy(&curr);
    }
    else
    {
        while (NULL != curr->next)
        {
            if (curr->next->dst == src)
            {
                temp = curr->next;
                curr->next = temp->next;
                edge_destroy(&temp);
                break;
            }
            curr = curr->next;
        }
    }

    return 1;
}

/*
* Finds if the desired vertex exists in the graph
* graph: an existing graph object
* src: the source vertex
* returns: the vertex data if found else NULL
*/
void* graph_find_vertex(graph_t* graph, int src)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return NULL;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return NULL;
    }

    return graph->adjlist[src].data;
}

/*
* Turns on vertex by setting it with non-void data
* graph: an existing graph object
* src: the vertex to be modified
* data: void* argument to be passed the vertex
* returns: 1 on success or -1 on failure
*/
int graph_set_vertex(graph_t* graph, int src, void* data)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return -1;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return -1;
    }

    graph->adjlist[src].data = data;

    return 1;
}

/*
* Removes all edges from vertex and unsets it
* graph: an existing graph object
* src: the vertex to be cleared
* returns: 1 on success or -1 on failure
*/
int graph_clear_vertex(graph_t* graph, int src)
{
    if (NULL == graph)
    {
        fprintf(stderr, "[Error: NULL graph]\n");
        return -1;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return -1;
    }

    while (NULL != graph->adjlist[src].head)
    {
        graph_remove_edge(graph, src, graph->adjlist[src].head->dst);
    }

    graph->adjlist[src].data = NULL;
    graph->adjlist[src].head = NULL;

    return 1;
}

/*
* Calculates the distances of the shortest path from a vertex to all
* graph: an existing graph object
* src: the source vertex
* dst: the destination vertex
* returns: weight of shortest path to dst else -1
*/
int graph_dijkstra(graph_t* graph, int src, int dst)
{
    int dist[graph->capacity];
    minheap_t* minheap = minheap_init(graph->capacity);

    if (NULL == minheap)
    {
        fprintf(stderr, "[Error: NULL minheap]\n");
        return -1;
    }

    if (src < 0 || src >= graph->capacity)
    {
        fprintf(stderr, "[Error: src vertex is out of bounds]\n");
        return -1;
    }

    for (int i = 0; i < graph->capacity; ++i)
    {
        dist[i] = INT_MAX;
        minheap->array[i] = minheap_node_init(i, dist[i]);
        minheap->pos[i] = i;
    }

    minheap->array[src]->v = src;
    minheap->array[src]->dist = dist[src];
    minheap->pos[src] = src;
    dist[src] = 0;
    minheap_decrease_key(minheap, src, dist[src]);
    minheap->size = graph->capacity;

    while (minheap_empty(minheap) == 0)
    {
        minheap_node_t* min = minheap_min(minheap);
        int u = min->v;
        edge_t* crawl = graph->adjlist[u].head;

        while (NULL != crawl)
        {
            int v = crawl->dst;

            if (minheap_find(minheap, v) && dist[u] != INT_MAX && crawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + crawl->weight;
                minheap_decrease_key(minheap, v, dist[v]);
            }

            crawl = crawl->next;
        }

        free(min);
    }

    dijkstra_print(dist, graph->capacity);
    int weight = dist[dst];
    minheap_destroy(minheap);

    return weight;
}

/*
* Prints the graph
* graph: an existing graph object
* returns: none
*/
void graph_print(graph_t* graph)
{
    if (NULL == graph)
    {
        printf("\n=== NULL GRAPH ===\n");
        return;
    }

    edge_t* curr = NULL;
    printf("\n=== GRAPH ===\n");
    printf("--- Ex: [Vertex: i (data) | Edges: (src<->dst : weight) ...] ---\n");

    for (int i = 0; i < graph->capacity; ++i)
    {
        if (NULL != graph->adjlist[i].data)
        {
            printf("Vertex: %d (", i);
            graph->print_func(graph->adjlist[i].data);
            printf(") | ");

            if (NULL != graph->adjlist[i].head)
            {
                printf("Edges: ");
                curr = graph->adjlist[i].head;

                while (NULL != curr)
                {
                    printf("(%d<->%d : %d) ", i, curr->dst, curr->weight);
                    curr = curr->next;
                }
                printf("\n");
            }
            else
            {
                printf("- No Edges -\n");
            }
        }
    }

    printf("==== END ====\n");
}
