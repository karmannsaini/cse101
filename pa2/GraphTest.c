/*
Karmann Sgitaini
cruzid:2034335
pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h" // makes sure graph function prototypes are known

// global test counters
int test_count = 0;
int passed_count = 0;

// helper function to check test results
void run_test(bool condition, const char* message) {
    test_count++;
    if (condition) {
        passed_count++;
        fprintf(stdout, "  PASS %d: %s\n", test_count, message);
    } else {
        fprintf(stdout, "  FAIL %d: %s\n", test_count, message);
    }
}

// test group 1: constructors and accessors
void test_constructors_accessors() {
    fprintf(stdout, "\n--- test group 1: constructors & accessors ---\n");
    Graph G = newGraph(10);
    
    // check that newGraph sets everything up correctly
    run_test(getOrder(G) == 10, "newGraph sets correct number of vertices");
    run_test(getNumEdges(G) == 0, "newGraph starts with 0 edges");
    run_test(getNumArcs(G) == 0, "newGraph starts with 0 arcs");
    run_test(getSource(G) == NIL, "newGraph source starts as NIL");

    // check parent and distance values before bfs runs
    run_test(getParent(G, 1) == NIL, "getParent returns NIL before bfs");
    run_test(getDist(G, 1) == INF, "getDist returns INF before bfs");
    
    freeGraph(&G);
    run_test(G == NULL, "freeGraph sets the pointer to null");
}

// test group 2: manipulation functions
void test_manipulation_procedures() {
    fprintf(stdout, "\n--- test group 2: manipulation procedures ---\n");
    Graph G = newGraph(6);
    
    // test addEdge
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    run_test(getNumEdges(G) == 2, "addEdge increases edge count");
    
    // test addArc
    addArc(G, 4, 5);
    addArc(G, 5, 6);
    run_test(getNumArcs(G) == 2, "addArc increases arc count");
    
    // test makeNull
    makeNull(G);
    run_test(getNumEdges(G) == 0 && getNumArcs(G) == 0, "makeNull resets edges and arcs");

    freeGraph(&G);
}

// test group 3: bfs and getPath
void test_bfs_and_getpath() {
    fprintf(stdout, "\n--- test group 3: bfs and getPath ---\n");
    Graph G = newGraph(6);
    
    // build the graph from the pa2 example
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    
    // bfs from vertex 1 (reachable)
    BFS(G, 1);
    run_test(getSource(G) == 1, "bfs sets the correct source");
    run_test(getDist(G, 5) == 2, "bfs gives correct distance to reachable vertex (1-5)");
    
    // test getPath for a reachable path
    List L = newList();
    getPath(L, G, 5);
    
    // make sure path has valid length before checking contents
    if (length(L) > 0) {
        moveFront(L);
        run_test(get(L) == 1, "getPath starts with source vertex");
        moveNext(L);
        run_test(get(L) == 2, "getPath includes correct intermediate vertex");
        moveNext(L);
        run_test(get(L) == 5, "getPath ends with destination vertex");
        run_test(length(L) == 3, "getPath returns correct path length");
    } else {
         run_test(false, "getPath failed to return a non-empty path");
    }
    clear(L);
    
    // bfs on disconnected graph (unreachable)
    Graph H = newGraph(7);
    addEdge(H, 1, 4);
    addEdge(H, 2, 3);
    addEdge(H, 3, 7);
    BFS(H, 1); // source 1 is only connected to 4
    
    run_test(getDist(H, 7) == INF, "getDist gives INF for unreachable vertex");
    
    // test getPath for unreachable vertex
    getPath(L, H, 7);
    
    // make sure it adds NIL when unreachable
    if (length(L) > 0) {
        moveFront(L);
        run_test(get(L) == NIL, "getPath returns NIL for unreachable vertex");
    } else {
        run_test(false, "getPath didn't append NIL for unreachable vertex");
    }
    
    freeList(&L);
    freeGraph(&G);
    freeGraph(&H);
}

int main(int argc, char* argv[]){
    test_constructors_accessors();
    test_manipulation_procedures();
    test_bfs_and_getpath();

    fprintf(stdout, "\n==========================================================\n");
    fprintf(stdout, "summary: %d tests run, %d passed, %d failed\n", 
            test_count, passed_count, test_count - passed_count);
    fprintf(stdout, "==========================================================\n");

    return EXIT_SUCCESS;
}
