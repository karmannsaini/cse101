/*
Karmann Saini
CruzID:2034335
pa3
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// constants
#define NIL -1
#define INF -1000000
#define UNDEF -10

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
// Returns the number of (undirected) edges in G. 
int getNumEdges(Graph G);

// getNumArcs() 
// Returns the number of directed edges in G. 
int getNumArcs(Graph G);

// getParent() 
// Returns the parent of vertex u, or NIL if DFS() not yet called.
int getParent(Graph G, int u);

// getDiscover() 
// Returns the discover time of u, or UNDEF if DFS() not yet called. 
int getDiscover(Graph G, int u); 

// getFinish() 
// Returns the finish time of u, or UNDEF if DFS() not yet called. 
int getFinish(Graph G, int u);

// manipulation procedures -------------------------------------------------

// makeNull() 
// Resets G to its initial state. 
void makeNull(Graph G);

// addEdge() 
// Creates an undirected edge joining vertex u to vertex v. 
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G) 
void addEdge(Graph G, int u, int v);

// addArc() 
// Creates a directed edge joining vertex u to vertex v. 
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G) 
void addArc(Graph G, int u, int v);

// DFS() 
// Runs the Depth First Search algorithm on G.  Input List S contains the vertex 
// labels 1, .., n, where n=getOrder(G), and determines the order in which vertices  
// are processed in the main loop of DFS(). When complete, output List S contains  
// the same vertices sorted by decreasing finish times.  
// Pre: getOrder(G)==getLength(S) 
void DFS(Graph G, List S); 

// other functions -------------------------------------------------

// copyGraph() 
// Returns a copy of G. 
Graph copyGraph(Graph G); 

// transpose() 
// Returns the transpose of Graph G. 
Graph transpose(Graph G); 

// printGraph() 
// Prints the adjacency list representation of G to FILE* out. 
void printGraph(FILE* out, Graph G);