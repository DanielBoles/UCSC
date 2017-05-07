/*
 * Graph.h
 * Daniel Boles
 * dawboles
 * pa4
 * description: This is the header file for the graph ADT. 
 *
*/
#ifndef __GRAPH_H_DEF__ 
#define __GRAPH_H_DEF__

#include <stdio.h>
#include "List.h"

#define White 0
#define Grey 1
#define Black 2
#define NIL 0
#define INF 99999

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
Graph newGraph(int n); 
void freeGraph(Graph* pG);

/*** Access functions ***/ 
int getOrder(Graph G); 
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); 
int getDist(Graph G, int u); 
void getPath(List L, Graph G, int u);  

/*** Manipulation procedures ***/ 
void makeNull(Graph G); 
void addEdge(Graph G, int u, int v); 
void addArc(Graph G, int u, int v); 
void BFS(Graph G, int s);   

/*** Other operations ***/ 
void printGraph(FILE* out, Graph G); 

#endif