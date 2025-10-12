/*
Karmann Saini
CruzID:2034335
pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

// required format: (v1, v2, v3)
void printPathList(FILE* out, List L) {
    if (length(L) == 0) {
        return; 
    }
    
    moveFront(L);
    int first_element = get(L);

    // If getPath returned NIL, the path = unreachable
    if (first_element == NIL) {
        return; 
    }

    fprintf(out, "(");
    fprintf(out, "%d", first_element); 
    
    moveNext(L); 
    while (position(L) != -1) {
        fprintf(out, ", %d", get(L));
        moveNext(L);
    }
    fprintf(out, ")");
}


int main(int argc, char* argv[]) {
    FILE *in_file, *out_file;
    int n; 
    int u, v; 

    //input and output file names
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "FindPath Error: Unable to open input file %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    out_file = fopen(argv[2], "w");
    if (out_file == NULL) {
        fclose(in_file); 
        fprintf(stderr, "FindPath Error: Unable to open output file %s.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Read initial vertex count n
    if (fscanf(in_file, "%d", &n) != 1 || n < 1) {
        fprintf(stderr, "FindPath Error: Invalid initial graph size n.\n");
        fclose(in_file);
        fclose(out_file);
        exit(EXIT_FAILURE);
    }

    Graph G = newGraph(n);

    // Read graph edges until line "0 0" is encountered.
    while (fscanf(in_file, "%d %d", &u, &v) == 2 && (u != 0 || v != 0)) {
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            addEdge(G, u, v); // Using addEdge for undirected edges.
        } else {
             // Skipping invalid edges is safer than crashing.
             fprintf(stderr, "FindPath Warning: Edge (%d, %d) ignored (out of range [1, %d]).\n", u, v, n);
        }
    }

    printGraph(out_file, G);
    fprintf(out_file, "\n"); 

    // Process all path queries.
    List path_list = newList();

    // Read source (u) and destination (v) pairs until dummy line "0 0".
    while (fscanf(in_file, "%d %d", &u, &v) == 2 && (u != 0 || v != 0)) {
        int s = u; // source
        int d = v; // destination

        if (s < 1 || s > n || d < 1 || d > n) {
             fprintf(stderr, "FindPath Warning: Skipping path query with out-of-range vertices (%d, %d).\n", s, d);
             continue;
        }

        BFS(G, s);
        int distance = getDist(G, d); 

        clear(path_list);
        getPath(path_list, G, d);

        fprintf(out_file, "The distance from %d to %d is ", s, d);
        
        // If distance is INF or getPath returned NIL, print unreachability message.
        if (distance == INF || front(path_list) == NIL) {
            fprintf(out_file, "infinity\n");
            fprintf(out_file, "No %d-%d path exists\n", s, d);
        } else {
            fprintf(out_file, "%d\n", distance);
            fprintf(out_file, "A shortest %d-%d path is: ", s, d);
            printPathList(out_file, path_list);
            fprintf(out_file, "\n");
        }
        
        fprintf(out_file, "\n"); // Blank line after each query block.
    }

    // Free memory and close files.
    freeList(&path_list);
    freeGraph(&G);
    
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}
