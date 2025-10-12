/*
Karmann Saini
CruzID:2034335
pa2
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"


// int main(void) {
//     Graph G = newGraph(6);

//     // test getOrder
//     if (getOrder(G) == 6) {
//         printf("getOrder correctly outputs returns the number of vertices.\n");
//     } else {
//         printf("getOrder returns and incorrect number of vertices.\n");
//     }

//     // test if newGraph sets undirectedEdges = 0
//     if (getNumEdges(G) == 0) {
//         printf("newGraph correctly sets undirectedEdges = 0.\n");
//     } else {
//         printf("newGraph does not set undirectedEdges = 0.\n");
//     }

//     // test if newGraph sets directedEdges = 0
//     if (getNumArcs(G) == 0) {
//         printf("newGraph correctly sets directedEdges = 0.\n");
//     } else {
//         printf("newGraph does not set directedEdges = 0.\n");
//     }

//     // test if newGraph sets source = NIL
//     if (getSource(G) == NIL) {
//         printf("newGraph correctly sets source = NIL.\n");
//     } else {
//         printf("newGraph does not set sourec = NIL.\n");
//     }

// }

int main(int argc, char* argv[]){
   int u, v, s, max, min, d, n, offset;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 

   // encoded graph 
   char graphData[] = "100 77 86 20 18 4 44 16 13 64 73 21 41 82 100 100 65 74 92 "
                      "60 96 97 90 64 89 99 64 7 23 3 53 17 66 76 67 21 68 78 93 "
                      "50 31 63 94 50 45 23 20 65 72 3 4 87 24 25 33 44 5 37 87 87 "
                      "18 65 31 31 1 84 3 80 16 64 52 84 56 56 86 83 49 72 67 90 8 "
                      "22 96 51 73 71 62 36 62 92 43 19 34 84 17 75 91 35 82 29 33 "
                      "25 23 65 89 92 58 31 22 71 33 34 10 30 24 27 44 26 8 99 56 "
                      "25 40 47 12 69 84 2 11 43 59 99 23 34 1 3 39 42 43 87 6 50 "
                      "55 83 92 62 53 90 15 69 31 45 24 34 45 8 45 8 21 98 36 50 19 "
                      "21 71 82 1 77 65 55 15 73 28 85 5 37 49 96 3 37 84 90 81 94 "
                      "98 90 73 98 97 89 34 80 66 70 30 26 2 20 59 5 66 74 22 80 76 "
                      "62 32 62 61 50 16 52 73 69 4 97 81 46 90 30 11 94 25 83 64 65 "
                      "62 12 39 28 50 30 84 72 68 38 52 43 65 60 81 8 4 82 34 55 10 "
                      "44 41 57 61 9 10 14 15 48 49 54 55 79 80 88 89 95 96 75 63 "
                      "78 79 0 0";
   char* data = graphData;

   // Build graph G
   sscanf(data, " %d%n", &n, &offset); 
   Graph G = newGraph(n);
   data += offset;
   while( sscanf(data, " %d %d%n", &u, &v, &offset)==2 ){
      if( u*v==0 ) break;
      addEdge(G, u, v);
      data += offset;
   }

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(v=2; v<=n; v++){
         d = getDist(G, v);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(v=2; v<=n; v++){
      d = get(E);
      if( d==min ){
         append(C, v);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, v);
      }
      if( d==max ){
         append(P, v);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, v);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}