/***
* Karmann Saini
* kasisain 
* 2025 Fall CSE101 pa3 
* FindComponents.c
* Client module
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

void printComponentList(FILE* out, List L) {
    if (length(L) == 0) {
        fprintf(out, "()");
        return; 
    }
    
    fprintf(out, "(");
    moveFront(L);
    fprintf(out, "%d", get(L));
    
    while (position(L) != -1) {
        moveNext(L);
        if (position(L) != -1) {
            fprintf(out, ", %d", get(L));
        }
    }
    fprintf(out, ")");
}

int main(int argc, char* argv[]) {
    FILE *in_file, *out_file;
    int n; 
    int u, v;

    // check command line arguments and open files
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "FindComponents Error: Unable to open input file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    out_file = fopen(argv[2], "w");
    if (out_file == NULL) {
        fclose(in_file); 
        fprintf(stderr, "FindComponents Error: Unable to open output file %s.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // read the initial vertex count n
    if (fscanf(in_file, "%d", &n) != 1 || n < 1) {
        fprintf(stderr, "FindComponents Error: Invalid initial graph size n.\n");
        fclose(in_file);
        fclose(out_file);
        exit(EXIT_FAILURE);
    }

    // initialize Graph G
    Graph G = newGraph(n);

    while(fscanf(in_file, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        } else {
            addArc(G, u, v);
        }
    }

    // Print Adjacency List
    fprintf(out_file, "Adjacency list representation of G:\n");
    printGraph(out_file, G);
    fprintf(out_file, "\n");

    List S = newList();

    // fill S with all vertices
    for (int i = 1; i < getOrder(G) + 1; i++) {
        append(S, i);
    }

    DFS(G, S);

    // declare transpose graph T
    Graph T = transpose(G);

    // 2nd dfs run on transpose graph
    DFS(T, S);

    // determine how many scc's were discovered
    int sccCount = 0;

    for (int i = 1; i < getOrder(T) + 1; i++) {
        if (getParent(T, i) == NIL) {
            sccCount++;
        }
    }

    fprintf(out_file, "G contains %d strongly connected components:\n", sccCount);

    List* Comp = calloc(sccCount, sizeof(List));
    List S_temp;

    // Loop to extract each component list
    for (int i = 1; i <= sccCount; i++) {
        // Move to the end of the remaining list S
        moveBack(S);

        // where parent is NIL is where we need to be
        while (getParent(T, get(S)) != NIL) {
            movePrev(S);
        }

        // S = the component, S_temp = the remainder.
        S_temp = split(S); 

        
        Comp[i-1] = S;

        
        S = S_temp; 
    }

    // topologically sorted
    for (int i = 0; i < sccCount; i++) {
        fprintf(out_file, "Component %d: ", i + 1);
        printComponentList(out_file, Comp[i]);
        fprintf(out_file, "\n");
    }
    fprintf(out_file, "\n"); 

    // cleanup
    for (int i = 0; i < sccCount; i++ ) {
        freeList(&Comp[i]);
    }
    free(Comp);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T); 
    
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}