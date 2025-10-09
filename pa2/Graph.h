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

// constructors - destructors -------------------------------------------------

// newGraph() 
// Returns a Graph having n vertices and no edges. 
Graph newGraph(int n); 

// freeGraph() 
// Frees all dynamic memory associated with Graph *pG and sets *pG to NULL. 
void freeGraph(Graph* pG);