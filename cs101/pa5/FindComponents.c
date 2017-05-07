/*
 * FindComponents.c
 * Daniel Boles
 * dawboles
 * pa5
 * description: This file contains main. 
 *
*/

#include "Graph.h"
#include <string.h>
#include <stdlib.h>
int main (int argc, char* argv[]){
  int vertex = 0;
  int vert1 = 0;
  int vert2 = 0;

//Check command line for correct number of arguments, Quit with a usage message to stderr if more than or less
//than two strings are given on the command line.
  if(argc != 3){
    fprintf(stderr,"Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  // open file to read/write
  FILE* input = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");

  if(input==NULL){
    fprintf(stderr,"Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if(output==NULL){
    fprintf(stderr,"Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  fscanf(input, "%d", &vertex); // the number of vertices in the graph, the first number
 
//Creates a new graph
//Assemble a graph object G using newGraph() and addArc(). Refer to pa5 pdf comments pg3
  Graph G = newGraph(vertex);
  while(fgetc(input) != EOF){       // while there is still intger to get in input file
      fscanf(input, "%d", &vert1);  // take input from file 1st one
      fscanf(input, "%d", &vert2);  // take input from file 2nd one
    if(vert1 == 0 && vert2 == 0) break;   // terminate if dummy line "0 0"
    addArc(G, vert1, vert2);       
  }

  //Put vertex numbers, however many,  into List S in increasing order starting at 1.
  List S = newList();
  for(int k = 1; k <= vertex; k++){
    append(S,k);
  }

  //Print the adjacency list representation of G to the output file. Refer to pa5 pdf comments pg3
  fprintf(output, "Adjacency list representation of G:\n");
  printGraph(output, G);  // print out its adjacency list representation
  fprintf(output, "\n");

  //Run DFS on G and tranpose of G , processing the vertices in the second call by decreasing finish times from
  //the first call.  Refer to pa5 pdf comments pg3
  DFS(G,S);
  Graph Trans = transpose(G);
  DFS(Trans,S);

  //Determine the strong components of G.  Refer to pa5 pdf comments pg3
  int nSCC = 0;     // # of strongly connected components
  for(moveFront(S);index(S)>=0;moveNext(S)){
    if(getParent(Trans,get(S))==NIL){ // if there is a root
      nSCC++;
    }
  }
  fprintf(output,"G contains %d strongly connected components:\n", nSCC);

  //Allocate mem for array list to hold nSCCs
  List* A = calloc(nSCC+1, sizeof(List));
  for(int i = 1; i <= nSCC; i++){
    A[i] = newList();
  }

  int i = nSCC;
  //Get the number of strongly connected components 
  for(moveFront(S); index(S) >= 0; moveNext(S)){
    if(getParent(Trans, get(S)) == NIL){
      i--;
      A[i] = newList();
    }
    if(i == nSCC) 
      break;
    append(A[i], get(S));
  }

  //Print the strong components of G to the output file in topologically sorted order. Refer to pa5 pdf comments pg3     
  for(i = 0; i < nSCC; i++){
    fprintf(output, "Component %d: ", i+1);
    printList(output, A[i]);
    fprintf(output, "\n");
    freeList(&A[i]);  // free memory
  }

  // free memory
  freeGraph(&G);   
  freeGraph(&Trans);
  free(A);
  freeList(&S); 
  
  // close the files
  fclose(input); fclose(output);  
  return(0);
}