//-----------------------------------------------------------------------------
// GraphClient.c
// Determines the connected components of an (undirected) graph using DFS.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"


int main(int argc, char* argv[]){

   int i, u, v, n, offset;

   // encoded graph 
   char graphData[] = "12 1 2 1 8 2 8 2 9 8 9 3 4 3 10 4 10 5 6 5 7 6 7 5 11 7 12 0 0";
   char* data = graphData;

   // Build Graph G
   sscanf(data, " %d%n", &n, &offset); 
   Graph G = newGraph(n);
   data += offset;
   while( sscanf(data, " %d %d%n", &u, &v, &offset)==2 ){
      if( u*v==0 ) break;
      addEdge(G, u, v);
      data += offset;
   }
   fprintf(stdout, "\n");
   printGraph(stdout, G);

   // Build List S
   List S = newList();
   for( i=1; i<=n; i++ ){
      append(S, i);
   }

   DFS(G, S);

   // trace DFS 
   /*
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   */

   // Count connected components
   int numComp = 0;
   for( moveFront(S); position(S)>=0; moveNext(S) ){
      if( getParent(G, get(S))==NIL ){
         numComp++;
      }
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "# connected components = %d\n", numComp);
   printList(stdout, S);
   fprintf(stdout, "\n");

   // Print connected components
   List* Comp = calloc(numComp, sizeof(List));
   List T;
   for( i=0; i<numComp; i++ ){
      moveBack(S);
      while( getParent(G, get(S))!=NIL ){
         movePrev(S);
      }
      T = split(S);
      Comp[i] = S;
      S = T;
   }
   for( i=0; i<numComp; i++ ){
      fprintf(stdout, "%d: ", i+1);
      printList(stdout, Comp[i]);
      fprintf(stdout, "\n");
   }
   fprintf(stdout, "\n");

   // free stuff
   for( i=0; i<numComp; i++ ) freeList(&Comp[i]);
   free(Comp);
   freeList(&S);
   freeGraph(&G);

   return(EXIT_SUCCESS);
}