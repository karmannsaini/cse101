/*
Karmann Saini
CruzID:2034335
pa2
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// constants
#define NIL -1
#define INF -10

typedef struct GraphObj* Graph;

// constructors - destructors -------------------------------------------------

// newGraph() 
// Returns a Graph having n vertices and no edges. 
Graph newGraph(int n); 

// freeGraph() 
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL. 
void freeGraph(Graph* pG);

// access functions -------------------------------------------------

// getOrder() 
// Returns the number of vertices in G. 
int getOrder(Graph G);

// getNumEdges() 
// Returns the number of edges in G. 
int getNumEdges(Graph G);

// getNumArcs() 
// Returns the number of Arcs in G. 
int getNumArcs(Graph G);

// getSource() 
// Returns the source vertex in the most recent call to BFS(), or NIL if 
// BFS() has not yet been called. 
int getSource(Graph G);

// getParent 
// Returns the parent of vertex u in the most recently constructed BFS tree 
// or returns NIL if BFS() has not yet been called. 
// Pre: 1 <= u <= getOrder(G) 
int getParent(Graph G, int u);

// getDist() 
// Returns the distance from the source vertex to u if BFS() has been called, 
// otherwise returns INF. 
// Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u); 