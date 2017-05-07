/*
 * Graph.h
 * Daniel Boles
 * dawboles
 * pa5
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
#define UNDEF 9999

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
Graph newGraph(int n); 
void freeGraph(Graph* pG);

/*** Access functions ***/ 
int getOrder(Graph G); 
int getSize(Graph G); 
int getSource(Graph G); 
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/ 
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/ 
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G); 

#endif