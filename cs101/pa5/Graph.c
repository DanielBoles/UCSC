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
	int *disc;
	int *fin;
	int order;
	int size;
} GraphObj;

int time;

Graph newGraph(int n){
	Graph new = malloc(sizeof(struct GraphObj));
	new->arr = calloc(n+1, sizeof(List));
	new->color = calloc(n+1, sizeof(int));
	new->parent = calloc(n+1, sizeof(int));
	new->disc = calloc(n+1, sizeof(int));
	new->fin = calloc(n+1, sizeof(int));
	new->order = n;
	new->size = 0;
	for(int i = 0; i < n+1; i++){
		new->arr[i] = newList();
		new->color[i] = White;
		new->parent[i] = NIL;
		new->disc[i] = UNDEF;
		new->fin[i] = UNDEF;
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
	free(old->disc);
	free(old->fin);
	free(*pG);
	*pG = NULL;
}

/*** Access functions ***/ 
int getOrder(Graph G){
	if(G == NULL){
		printf("Error: Invalid graph G in getOrder");
		exit(1);
	}
	return G->order;
}
int getSize(Graph G){
	if(G == NULL){
		printf("Error: Invalid graph G in getSize");
		exit(1);
	}
	return G->size;
}  
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Error: Invalid graph G in getParent");
		exit(1);
	}
	if(u<1 || u > getOrder(G)){
		printf("Error: Invalid parent parameter");
		return 0;
	}
	return G->parent[u];
} 

/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if(G == NULL){
		printf("Error: Invalid graph G in getDiscover");
		exit(1);
	}
	if(u<1 || u > getOrder(G)){
		printf("Error: Invalid u parameter in getDiscover");
		exit(1);	
	}
	return G->disc[u];
}
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if(G == NULL){
		printf("Error: Invalid graph G in getFinish");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Error: Invalid u parameter in getFinish");
		exit(1);	
	}
	return G->fin[u];
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
	if(G == NULL){
		printf("Error: Invalid graph G in addEdge");
		exit(1);
	}
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
	if(G == NULL){
		printf("Error: Invalid graph G in addArc");
		exit(1);
	}
	if(u > getOrder(G) || v > getOrder(G) || v < 1 || u < 1){
		printf("Error: Invalid preconditions for addArc");
		printf("%d %d\n", u, v);
		return;
	}
	insertionSort(G->arr[u], v);
	G->size++;
}
//Helper function for DFS, based on Visit from DFS
void VisitHelper(Graph G, List S, int i){
	if(G == NULL){
		printf("Error: Invalid graph G in VisitHelper");
		exit(1);
	}
	if(S == NULL){
		printf("Error: Invalid List S in VisitHelper");
		exit(1);
	}
	if(i != -1){
		G->color[i] = Grey;
		time++;
		G->disc[i] = time;
		moveFront(G->arr[i]);
		for(int j = 0; j < length(G->arr[i]);j++){
			int x = get(G->arr[i]);
			if(G->color[x] == White){
				G->parent[x] = i;
				VisitHelper(G, S, x);
			}
			moveNext(G->arr[i]);
		}
		G->color[i] = Black;
		prepend(S, i);
		time++;
		G->fin[i] = time;
	}
}
void DFS(Graph G, List S){
	if(G == NULL){
		printf("Error: Invalid graph G in Depth First Search");
		exit(1);
	}
	if(S == NULL){
		printf("Error: Invalid List S in Depth First Search");
		exit(1);
	}
	if(length(S) != getOrder(G)){
		printf("Error: Invalid parameters for DFS");
		exit(1);
	}

   	for(int j = 1; j <= getOrder(G); j++){
		G->color[j] = White;
		G->parent[j] = NIL;
	}
	time = 0;
	moveFront(S);
	List L = newList();
	while(index(S) != -1){
		int x = get(S);
		if(G->color[x] == White){
			VisitHelper(G, L, x);
		}
		moveNext(S);
	}
	moveFront(L);
	while(index(L) != -1){
		append(S, get(L));
		moveNext(L);
		deleteFront(S);
	}
	freeList(&L);

}

/*** Other operations ***/
Graph transpose(Graph G){
	if(G == NULL){
		printf("Error: Invalid graph G in transpose");
		exit(1);
	}
	Graph Transp = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->arr[i]);
		for(; index(G->arr[i]) > -1; moveNext(G->arr[i])){
			addArc(Transp, get(G->arr[i]), i);
		}
	}
	return Transp;
}
Graph copyGraph(Graph G) {
	if(G == NULL){
		printf("Error: Invalid graph G in copyGraph");
		exit(1);
	}
	Graph newCopy = newGraph(G->order);
	for(int i = 1; i < getOrder(G); i++){
		freeList(&(newCopy->arr[i]));
		newCopy->arr[i] = copyList(G->arr[i]);
	}
	return newCopy;

}
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

