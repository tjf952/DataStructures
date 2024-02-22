#include "include/graph.h"

void str_print(void* a)
{
    printf("%s", *(char **)a);
}

int main(void)
{
    const char** data = calloc(7, sizeof(char*));

    data[0] = "Superman";
    data[1] = "Batman";
    data[2] = "Wonder Woman";
    data[3] = "Flash";
    data[4] = "Green Lantern";
    data[5] = "Aquaman";
    data[6] = "Martian Manhunter";

    /*** GRAPH TESTING START ***/

    graph_t* graph = graph_init(7, str_print);

    edge_t* edge = graph_find_edge(graph, 0, 2);
    printf("\nEdge between vertex %d and %d: ", 0, 2);
    if (NULL != edge)
    {
        printf("[dst: %d | weight: %d]\n", edge->dst, edge->weight);
    }
    else
    {
        printf("NULL\n");
    }

    graph_set_vertex(graph, 0, &data[0]);
    graph_set_vertex(graph, 1, &data[1]);
    graph_set_vertex(graph, 2, &data[2]);
    graph_set_vertex(graph, 3, &data[3]);
    graph_set_vertex(graph, 4, &data[4]);
    graph_set_vertex(graph, 5, &data[5]);
    graph_set_vertex(graph, 6, &data[6]);

    graph_print(graph);

    void* vertex_data = graph_find_vertex(graph, 1);
    printf("\nVertex %d data: ", 1);
    if (NULL != vertex_data)
    {
        str_print(vertex_data);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    vertex_data = graph_find_vertex(graph, 9);
    printf("Vertex %d data: ", 9);
    if (NULL != vertex_data)
    {
        str_print(vertex_data);
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }

    graph_add_edge(graph, 0, 1, 1);
    graph_add_edge(graph, 0, 4, 3);
    graph_add_edge(graph, 1, 2, 5);
    graph_add_edge(graph, 1, 3, 3);
    graph_add_edge(graph, 1, 4, 1);
    graph_add_edge(graph, 2, 3, 1);
    graph_add_edge(graph, 3, 4, 1);
    graph_add_edge(graph, 5, 6, 3);

    graph_print(graph);

    int path_weight = graph_dijkstra(graph, 0, 2);
    printf("\nMinimum path weight between %d and %d: %d\n", 0, 2, path_weight);

    edge = graph_find_edge(graph, 1, 0);
    printf("\nEdge between vertex %d and %d: ", 1, 0);
    if (NULL != edge)
    {
        printf("[dst: %d | weight: %d]\n", edge->dst, edge->weight);
    }
    else
    {
        printf("NULL\n");
    }

    edge = graph_find_edge(graph, 1, 6);
    printf("Edge between vertex %d and %d: ", 1, 6);
    if (NULL != edge)
    {
        printf("[dst: %d | weight: %d]\n", edge->dst, edge->weight);
    }
    else
    {
        printf("NULL\n");
    }

    graph_remove_edge(graph, 1, 4);
    graph_remove_edge(graph, 2, 3);
    graph_remove_edge(graph, 0, 6);

    graph_print(graph);

    graph_clear_vertex(graph, 1);

    graph_print(graph);

    graph_destroy(&graph);

    graph_print(graph);

    /*** GRAPH TESTING END ***/

    printf("\n");
    free(data);
}