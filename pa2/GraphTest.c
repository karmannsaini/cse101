/*
Karmann Saini
CruzID:2034335
pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

// Global test count variables
int test_count = 0;
int passed_count = 0;

// Helper function to check test results
void run_test(bool condition, const char* message) {
    test_count++;
    if (condition) {
        passed_count++;
        fprintf(stdout, "  PASS %d: %s\n", test_count, message);
    } else {
        fprintf(stdout, "  FAIL %d: %s\n", test_count, message);
    }
}

// Test Group 1: Constructors and Accessors
void test_constructors_accessors() {
    fprintf(stdout, "\n--- TEST GROUP 1: Constructors & Accessors ---\n");
    Graph G = newGraph(10);
    
    // Test newGraph() and initial state
    run_test(getOrder(G) == 10, "newGraph sets correct number of vertices.");
    run_test(getNumEdges(G) == 0, "newGraph sets initial edge count to 0.");
    run_test(getNumArcs(G) == 0, "newGraph sets initial arc count to 0.");
    run_test(getSource(G) == NIL, "newGraph sets source to NIL.");

    // Test getParent and getDist on a new graph
    run_test(getParent(G, 1) == NIL, "getParent returns NIL before BFS.");
    run_test(getDist(G, 1) == INF, "getDist returns INF before BFS.");
    
    freeGraph(&G);
    run_test(G == NULL, "freeGraph sets the pointer to NULL.");
}

// Test Group 2: Manipulation Procedures
void test_manipulation_procedures() {
    fprintf(stdout, "\n--- TEST GROUP 2: Manipulation Procedures ---\n");
    Graph G = newGraph(6);
    
    // Test addEdge()
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    run_test(getNumEdges(G) == 2, "addEdge increases edge count.");

    // Test addArc()
    addArc(G, 4, 5);
    addArc(G, 5, 6);
    run_test(getNumArcs(G) == 2, "addArc increases arc count.");
    
    // Test makeNull()
    makeNull(G);
    run_test(getNumEdges(G) == 0 && getNumArcs(G) == 0, "makeNull resets edge and arc counts.");

    freeGraph(&G);
}

// Test Group 3: BFS and getPath
void test_bfs_and_getpath() {
    fprintf(stdout, "\n--- TEST GROUP 3: BFS and getPath ---\n");
    Graph G = newGraph(6);
    
    // Build the graph from pa2.pdf example
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    
    // Test BFS from source 1
    BFS(G, 1);
    run_test(getSource(G) == 1, "BFS correctly sets the source vertex.");
    run_test(getDist(G, 5) == 2, "BFS calculates correct distance to a reachable vertex (1-5).");
    run_test(getDist(G, 4) == 2, "BFS calculates correct distance to a reachable vertex (1-4).");
    run_test(getDist(G, 1) == 0, "BFS calculates a distance of 0 to the source.");

    // Test getPath for a reachable path
    List L = newList();
    getPath(L, G, 5);
    moveFront(L);
    run_test(get(L) == 1, "getPath first vertex is source.");
    moveNext(L);
    run_test(get(L) == 2, "getPath intermediate vertex is correct.");
    moveNext(L);
    run_test(get(L) == 5, "getPath last vertex is destination.");
    run_test(length(L) == 3, "getPath returns correct path length.");
    clear(L);
    
    // Test BFS on a disconnected graph
    Graph H = newGraph(7);
    addEdge(H, 1, 4);
    addEdge(H, 2, 3);
    addEdge(H, 3, 7);
    BFS(H, 1);
    run_test(getDist(H, 7) == INF, "getDist returns INF for unreachable vertex.");
    
    // Test getPath for an unreachable vertex
    getPath(L, H, 7);
    moveFront(L);
    run_test(get(L) == NIL, "getPath returns NIL for unreachable vertex.");
    
    freeList(&L);
    freeGraph(&G);
    freeGraph(&H);
}

int main() {
    test_constructors_accessors();
    test_manipulation_procedures();
    test_bfs_and_getpath();

    fprintf(stdout, "\n==========================================================\n");
    fprintf(stdout, "SUMMARY: %d tests run, %d passed, %d failed\n", 
            test_count, passed_count, test_count - passed_count);
    fprintf(stdout, "==========================================================\n");

    return EXIT_SUCCESS;
}