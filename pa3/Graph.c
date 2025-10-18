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

    bool isComplete;

} GraphObj;

// constructors - destructors -------------------------------------------------

Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->order = n;
    G->undirectedEdges = 0;
    G->directedEdges = 0;

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
    
    G->discoveryTime = malloc((n+1) * sizeof(int));
    for (int i = 1; i < n + 1; i++) {
        G->discoveryTime[i] = UNDEF;
    }

    G->finishTime = malloc((n+1) * sizeof(int));
    for (int i = 1; i < n + 1; i++) {
        G->finishTime[i] = UNDEF;
    }


    G->isComplete = false;

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
    if (1 > u || u > getOrder(G)) {     // is u even in the range of our vertices?
        printf("Graph Error: calling getDiscover() with a vertex index out of range.\n");
        exit(EXIT_FAILURE);
    }

    if (!G->isComplete) {       // DFS hasn't been run
        return UNDEF;
    } else {
        return G->discoveryTime[u];
    }
}

int getFinish(Graph G, int u) {
    if (1 > u || u > getOrder(G)) {     // is u even in the range of our vertices?
        printf("Graph Error: calling getFinish() with a vertex index out of range.\n");
        exit(EXIT_FAILURE);
    }

    if (!G->isComplete) {       // DFS hasn't been run
        return UNDEF;
    } else {
        return G->finishTime[u];
    }
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

void DFS(Graph G, List S) {
    //precondition:
    if (getOrder(G) != length(S)) {
        printf("Graph Error: DFS() called with invalid length of list\n");
        exit(EXIT_FAILURE);
    }


    for (int i = 1; i < getOrder(G) + 1; i++) {
        G->color[i] = 'W';
        G->parent[i] = NIL;
    }

    // local var time
    int time = 0;
    List order_list = copyList(S);
    clear(S);

    // main loof of DFS
    moveFront(order_list);
    while(position(order_list) != -1) {
        if (G->color[get(order_list)] == 'W') {
            time = Visit(G, get(order_list), time, S);
        }
        moveNext(order_list);
    }
    G->isComplete = true;
    freeList(&order_list);
}

int Visit(Graph G, int x, int time, List S) {
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
    append(S, x);
    return time;
}

// other operations -----------------------------------------------------------

Graph copyGraph(Graph G) {
    if (G == NULL) {
        printf("Graph Error: copyGraph(): NULL Graph Reference\n");
        exit(EXIT_FAILURE);
    }

    Graph C = newGraph(getOrder(G));

    C->order = getOrder(G);
    C->undirectedEdges = getNumEdges(G);
    C->directedEdges = getNumArcs(G);
    
    for (int i = 1; i < getOrder(G) + 1; i++) {
        freeList(&(C->adjacent[i]));
        C->adjacent[i] = copyList(G->adjacent[i]);
        C->color[i] = G->color[i];
        C->parent[i] = G->parent[i];
        C->discoveryTime[i] = G->discoveryTime[i];
        C->finishTime[i] = G->finishTime[i];
    }
    
    C->isComplete = false;

    return C;
}

Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));

    for (int u = 1; u < getOrder(G) + 1; u++) {
        moveFront(G->adjacent[u];
        
        List adjacentListG = G->adjacent[u];
        while(position(u) != -1) {
            int v = get(adjacentListG);
            addArc(T, v, u);
            moveNext(adjacentListG);
        }
    } 
    return T;
}

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