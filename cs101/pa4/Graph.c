/*
 * Graph.c
 * Daniel Boles
 * dawboles
 * pa4
 * description: This is the source file for the graph ADT. 
 *
*/

#include "Graph.h"
#include <stdlib.h>


/*** Constructors-Destructors ***/ 
struct GraphObj{
	List *arr;
	int *color;
	int *parent;
	int *dist;
	int order;
	int size;
	int source;
} GraphObj;

Graph newGraph(int n){
	Graph new = malloc(sizeof(struct GraphObj));
	new->arr = calloc(n+1, sizeof(List));
	new->color = calloc(n+1, sizeof(int));
	new->parent = calloc(n+1, sizeof(int));
	new->dist = calloc(n+1, sizeof(int));
	new->source = NIL;
	new->order = n;
	new->size = 0;
	for(int i = 0; i < n+1; i++){
		new->arr[i] = newList();
		new->color[i] = White;
		new->parent[i] = NIL;
		new->dist[i] = INF;
	}
	return new;
}

void freeGraph(Graph* pG){
	Graph old = *pG;
	for(int i = 0; i < (old->order) + 1; i++){
		freeList(&(old->arr[i]));
	}
	free(old->arr);
	free(old->color);
	free(old->parent);
	free(old->dist);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/ 
int getOrder(Graph G){
	return G->order;
}
int getSize(Graph G){
	return G->size;
} 
int getSource(Graph G){
	return G->source;
} 
int getParent(Graph G, int u){
	if(u<1 || u > getOrder(G)){
		printf("Error: Invalid parent parameter");
		return 0;
	}
	return G->parent[u];
} 
int getDist(Graph G, int u){
	if(getSource(G)==NIL){
		return INF;
	}
	if(u > getOrder(G) || u < 1){
		printf("Error: Invalid parameter for getDist");
		return 0;
	}
	else return G->dist[u];
} 
void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		printf("Source = NIL. Call BFS() first.");
	}
	if(u > getOrder(G) || u < 1){
		printf("Error: Invalid parameter for getPath");
		return;
	}
	int source = G->source;
	if(u==source){
		prepend(L,source);
		return;
	}
	else if(G->parent[u] == NIL){
		append(L, NIL);
	}
	else{
		prepend(L,u);
		getPath(L, G, G->parent[u]);
	}
}

/*** Manipulation procedures ***/ 
void makeNull(Graph G){
	for(int i = 0; i < G->order + 1; i++){
		clear(G->arr[i]);
	}
	G->size = 0;
}
// Insertion sort taken from pa2

void insertionSort(List L, int item){
	if(length(L) == 0){
		append(L, item);
		return;
	}
	for(moveFront(L); index(L) >= 0; moveNext(L)){
		int element = get(L);
		if(item < element){
			insertBefore(L, item);
			break;
		}
	}
	if(index(L) == -1){
		append(L, item);
	}
}

void addEdge(Graph G, int u, int v){
	if(u > getOrder(G) || v > getOrder(G) || v < 1 || u < 1){
		printf("Error: Invalid preconditions for addEdge");
		printf("%d %d\n", u, v);
		return;
	}
	insertionSort(G->arr[u], v);
	insertionSort(G->arr[v], u);
	G->size++;
}
void addArc(Graph G, int u, int v){
	if(u > getOrder(G) || v > getOrder(G) || v < 1 || u < 1){
		printf("Error: Invalid preconditions for addArc");
		printf("%d %d\n", u, v);
		return;
	}
	insertionSort(G->arr[u], v);
	G->size++;
}
void BFS(Graph G, int s){

	if(s < 1 || s >getOrder(G)){
		printf("Error: Invalid parameters for BFS");
		exit(1);
	}

   	for(int j = 0; j < getOrder(G) + 1; j++){
		if(j != s){
			G->color[j] = White;
			G->dist[j] = INF;
			G->parent[j] = NIL;
		}
	}
	G->source = s;
	G->color[s] = Grey;
	G->dist[s] = 0;
	G->parent[s] = NIL;
	List new = newList();
	int u;
	prepend(new, s);
	while(length(new) > 0){
   		u = back(new);
   		deleteBack(new);
   		List adj = G->arr[u];
		for(moveFront(adj); index(adj) >= 0; moveNext(adj)){
			int vertex = get(adj);
			if(G->color[vertex] == White){
				G->color[vertex] = Grey;
				G->dist[vertex] = G->dist[u] + 1;
				G->parent[vertex] = u;
				prepend(new, vertex);
			}
		}
		G->color[u] = Black;
	}

	freeList(&new);
}

/*** Other operations ***/ 
void printGraph(FILE* out, Graph G){
	if(out == NULL || G == NULL){
		printf("Error: Invalid parameters for printGraph");
		return;
	}
	for(int i = 1; i<getOrder(G) + 1; i++){
		fprintf(out, "%d: ", i);
		printList(out, G->arr[i]);
		fprintf(out, "\n");
	}

}
