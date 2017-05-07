/*
 * GraphTest.c
 * Daniel Boles
 * dawboles
 * pa4
 * description: This is the test source file for the graph ADT. 
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=12;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%3!=0 ) addEdge(G, i, i+1);
      if( i<=9  ) addEdge(G, i, i+3);
   }
   
   addEdge(G, 1, 7);
   addEdge(G, 6, 11);

   addArc(G, 2, 4);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   //check the size function
   printf("\nSize of G: %d\n", getSize(G));

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
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
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
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

/* Output:
1: 2 4 7
2: 1 3 4 5
3: 2 6
4: 1 5 7
5: 2 4 6 8
6: 3 5 9 11
7: 1 4 8 10
8: 5 7 9 11
9: 6 8 12
10: 7 11
11: 6 8 10 12
12: 9 11

Size of G: 20

Radius = 3
Central vertices: 3 5 6 7 8 9 10 11
Diameter = 4
Peripheral vertices: 1 2 4 12
*/