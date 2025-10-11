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

#define NIL -1
#define INF -10

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
        G->adjacent[i] = newList();
    }
    G->color = malloc((n+1) * sizeof(char));
    for (int i = 1; i < n + 1; i++) {
        G->color[i] = 'W';
    }
    G->parent = malloc((n+1) * sizeof(int));
    for (int i = 1; i < n + 1; i++) {
        G->parent[i] = NIL;
    }
    G->distance = malloc((n+1) * sizeof(int));
    for (int i = 1; i < n + 1; i++) {
        G->distance[i] = INF;
    }

    return(G);
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adjacent[i]));
    }

    free((*pG)->adjacent);
    (*pG)->adjacent = NULL;

    free((*pG)->color);
    (*pG)->color = NULL;
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->distance);
    (*pG)->distance = NULL;

    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G) {
    return(G->order);
}
