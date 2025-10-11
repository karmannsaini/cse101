/*
Karmann Saini
CruzID:2034335
pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"


int main(void) {
    Graph G = newGraph(6);

    // test getOrder
    if (getOrder(G) == 6) {
        printf("getOrder correctly outputs returns the number of vertices.\n");
    } else {
        printf("getOrder returns and incorrect number of vertices.\n");
    }

    // test if newGraph sets undirectedEdges = 0
    if (getNumEdges(G) == 0) {
        printf("newGraph correctly sets undirectedEdges = 0.\n");
    } else {
        printf("newGraph does not set undirectedEdges = 0.\n");
    }

    // test if newGraph sets directedEdges = 0
    if (getNumArcs(G) == 0) {
        printf("newGraph correctly sets directedEdges = 0.\n");
    } else {
        printf("newGraph does not set directedEdges = 0.\n");
    }

    // test if newGraph sets source = NIL
    if (getSource(G) == NIL) {
        printf("newGraph correctly sets source = NIL.\n");
    } else {
        printf("newGraph does not set sourec = NIL.\n");
    }

}