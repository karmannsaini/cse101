/*
Karmann Saini
CruzID:2034335
pa2
*/

#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// private GraphObj type
typedef struct GraphObj{
    int order;
    int undirectedEdges;
    int directedEdges;
    int source;

    List* adjacent;
    char* color;
    int* parent;
    int* distance;

} GraphObj;

// constructors - destructors -------------------------------------------------

Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->order = n;
    G->undirectedEdges = 0;
    G->directedEdges = 0;
    G->source = NIL;

    G->adjacent = malloc((n+1) * sizeof(List));
    for (int i = 1; i < n + 1; i++) {
        G->adjacent[i] = newList()
    }
    G->color = 'W';
    G->parent = NIL
    G->distance = INF

    return(G)
}

// List newList() {
//     List L;
//     L = malloc(sizeof(ListObj));
//     // Check precon: malloc must not return NULL
//     if (L == NULL) {
//         printf("List Error: newList: failed to allocate memory");
//         exit(EXIT_FAILURE);
//     }
//     assert(L!=NULL);
//     L->front = NULL;
//     L->back = NULL;
//     L->cursor = NULL;
//     L->length = 0;
//     L->position = -1;
//     return(L);
// };