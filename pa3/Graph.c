/*
Karmann Saini
CruzID:2034335
pa3
*/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// private GraphObj type
typedef struct GraphObj{
    int order;
    int undirectedEdges;
    int directedEdges;

    List* adjacent;
    char* color;
    int* parent;
    int* distance;
    int* discoveryTime;
    int* finishTime;

} GraphObj;

// constructors - destructors -------------------------------------------------

Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->order = n;
    G->undirectedEdges = 0;
    G->directedEdges = 0;
    G->discoveryTime = UNDEF;

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

// access functions -------------------------------------------------

int getOrder(Graph G) {
    return(G->order);
}

int getNumEdges(Graph G) {
    return(G->undirectedEdges);
}

int getNumArcs(Graph G) {
    return(G->directedEdges);
}

//a parent of a vertex may be NIL
int getParent(Graph G, int u) {
    if (1 > u || u > getOrder(G)) {
        printf("Graph Error: calling getParent() with a vertex index out of range.\n");
        exit(EXIT_FAILURE);
    }

    if (G->source == NIL) {
        return(NIL);
    } else {
        return(G->parent[u]);
    }
}

int getDiscover(Graph G, int u) {

}

int getFinish(Graph G, int u) {
    //if dfs not called, return UNDEF, otherwiser return finish time of U
}

// manipulation proccedures -------------------------------------------------

void makeNull(Graph G){
    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->adjacent[i]);
        G->color[i] = 'W';
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->undirectedEdges = 0;
    G->directedEdges = 0;
    G->source = NIL;
}

void addEdge(Graph G, int u, int v) {
    if (1 > u || u > getOrder(G) || 1 > v || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() with a vertex index out of range.\n");
        exit(EXIT_FAILURE);
    }

    // add v to u adjacency list
    List L_u = G->adjacent[u];
    if (length(L_u) == 0) {
        append(L_u, v);
    } else {
        moveFront(L_u);
        while(position(L_u) != -1 && get(L_u) < v) {
            moveNext(L_u);
        }
        if (position(L_u) == -1) {
            append(L_u, v);
        } else {
            insertBefore(L_u, v);
        }
    }

    // add u to v adjacency list
    List L_v = G->adjacent[v];
    if (length(L_v) == 0) {
        append(L_v, u);
    } else {
        moveFront(L_v);
        while(position(L_v) != -1 && get(L_v) < u) {
            moveNext(L_v);
        }
        if (position(L_v) == -1) {
            append(L_v, u);
        } else {
            insertBefore(L_v, u);
        }
    }
    
    G->undirectedEdges++;
}

void addArc(Graph G, int u, int v) {
    if (1 > u || u > getOrder(G) || 1 > v || v > getOrder(G)) {
        printf("Graph Error: calling addArc() with a vertex index out of range.\n");
        exit(EXIT_FAILURE);
    }

    // temp var to hold adjacency list for vertex u
    List L_u = G->adjacent[u];
    if (length(L_u) == 0) {
        append(L_u, v);
    } else {
        moveFront(L_u);
        while(position(L_u) != -1 && get(L_u) < v) {
            moveNext(L_u);
        }
        if (position(L_u) == -1) {
            append(L_u, v);
        } else {
            insertBefore(L_u, v);
        }
    }

    G->directedEdges++;
}

void DFS(Graph G, List s) {
    for (int i = 1; i < getOrder(G) + 1; i++) {
        G->color[i] = 'W';
        G->parent[i] = NIL;
    }
    // local var time
    int time = 0;

    // main loof of DFS
    for (int i = 1; i < getOrder(G) + 1; i++) {
        if (G->color[i] == 'W')
            time = Visit(G, i, time);
    }
}

int Visit(Graph G, int x, int time) {
    G->discoveryTime[x] = ++time;
    G->color[x] = 'G';
    for (int y = 1; y < length(G->adjacent[x]); y++) {
        if (G->color[y] == 'W') {
            G->parent[y] = x;
            time = Visit(G, y, time);
        }
    }
    G->color[x] = 'B';
    G->finishTime[x] = ++time;
    return time;
}

// other operations -----------------------------------------------------------

Graph copyGraph(Graph G);

Graph transpose(Graph G);

void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: (", i);
        
        List L = G->adjacent[i];
        if (L != NULL && length(L) > 0) {  
            moveFront(L);
            fprintf(out, "%d", get(L));
            while (position(L) != -1) {
                moveNext(L);
                if (position(L) != -1) {
                    fprintf(out, ", %d", get(L));
                }
            }
        }
        
        fprintf(out, ")\n");
    }
}