Karmann Saini | kasisain | 2034335

pa3

List.c:                 The implementation of the List ADT, which is a doubly linked list. It defines all the operations declared in List.h.

List.h:                 The interface for the List ADT, containing function prototypes and type definitions.

Graph.c:                The implementation of the Graph ADT, representing a graph with an adjacency list. It defines all the graph operations and the DFS algorithm. For Visit() I chose to implement the method of giving it it's own local copy of time, having DFS pass it the current value of time, and then finally returning the new value of time after Visit() is complete.

Graph.h:                The interface for the Graph ADT, containing function prototypes and type definitions for a graph.

GraphTest.c:            A test client for the Graph ADT. It tests all ADT operations to ensure they function correctly and that memory is handled properly.

FindComponents.c:       The main client program for this project. It reads from an input file, assembles a graph G, prints the adjacency list, runs DFS on G and G^T, finds all strongly connected components of G and then prints those in topologically sorted order to an output file.

Makefile:               A build file used to compile the project, run tests, and remove binary files.

README.md:              This file lists all the files submitted for the assignment and provides a brief description of each one.