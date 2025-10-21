/***
* Karmann Saini
* kasisain 
* 2025 Fall CSE101 pa3 
* GraphTest.c
* Graph test comprehensive
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

int test_count = 0;
int passed_count = 0;

void run_test(bool condition, const char* message) {
    test_count++;
    if (condition) {
        passed_count++;
        printf("  pass %d: %s\n", test_count, message);
    } else {
        printf("  fail %d: %s\n", test_count, message);
    }
}

// helper to check if a list matches an expected sequence
bool check_list_sequence(List L, int* expected, int len) {
    if (length(L) != len) return false;
    moveFront(L);
    for (int i = 0; i < len; i++) {
        if (position(L) == -1 || get(L) != expected[i]) return false;
        moveNext(L);
    }
    return true;
}

// test 1: graph creation + accessors
void test_initial_state_and_accessors() {
    printf("\n-- test 1: basic construction and accessors --\n");
    Graph G = newGraph(10);
    
    run_test(getOrder(G) == 10, "order = 10");
    run_test(getNumArcs(G) == 0 && getNumEdges(G) == 0, "no arcs or edges yet");

    run_test(getParent(G, 5) == NIL, "parent is NIL before dfs");
    run_test(getDiscover(G, 5) == UNDEF, "discover time undef");
    run_test(getFinish(G, 5) == UNDEF, "finish time undef");

    addArc(G, 1, 3);
    addArc(G, 1, 5);
    addArc(G, 2, 1);
    run_test(getNumArcs(G) == 3, "arc count = 3");


    run_test(getNumArcs(G) == 3, "arc count = 3");


    makeNull(G);
    run_test(getNumArcs(G) == 0, "makenull resets arc count");
    
    freeGraph(&G);
}

// test 2: dfs and time checking
void test_dfs_execution() {
    printf("\n-- test 2: dfs timing + order --\n");

    Graph G = newGraph(5);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 2); // makes a cycle

    List S = newList();
    for (int i = 1; i <= 5; i++) append(S, i);
    
    DFS(G, S);

    run_test(getParent(G, 3) == 2, "parent(3) = 2");
    run_test(getParent(G, 1) == NIL, "1 has NIL parent");

    run_test(getDiscover(G, 1) == 1, "discover(1) = 1");
    run_test(getFinish(G, 1) == 10, "finish(1) = 10");
    run_test(getDiscover(G, 5) == 5 && getFinish(G, 5) == 6, "discover/finish(5) ok");

    int expected_S[] = {1, 2, 3, 4, 5};
    run_test(check_list_sequence(S, expected_S, 5), "S in decreasing finish time");

    freeList(&S);
    freeGraph(&G);
}

// test 3: transpose + copygraph
void test_transpose_and_copy() {
    printf("\n-- test 3: transpose + copy --\n");

    Graph G = newGraph(3);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 1);
    
    Graph C = copyGraph(G);
    addArc(C, 1, 3); // modify copy
    run_test(getNumArcs(G) == 3 && getNumArcs(C) == 4, "copy is deep");

    Graph T = transpose(G);
    run_test(getNumArcs(T) == getNumArcs(G), "transpose arc count matches");

    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
}

int main(void) {
    test_initial_state_and_accessors();
    test_dfs_execution();
    test_transpose_and_copy();

    printf("\n========================================\n");
    printf("summary: %d tests run, %d passed, %d failed\n", 
           test_count, passed_count, test_count - passed_count);
    printf("========================================\n");
    
    return 0;
}
