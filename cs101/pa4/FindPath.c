/*
 * FindPath.c
 * Daniel Boles
 * dawboles
 * pa4
 * description: This file contains main. 
 *
*/

#include "Graph.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int vertNum = 0;	
	int vert1 = 0;
	int vert2 = 0;
	if(argc != 3){
		printf("Error: Invalid inputs for main");
		exit(1);
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Error: Invalid input file for read: %s\n", argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Error: Invalid out file for write: %s\n", argv[2]);
		exit(1);
	}
	fscanf(in, "%d", &vertNum);
	Graph G = newGraph(vertNum);
	while(fgetc(in) != EOF){
		fscanf(in, "%d %d", &vert1, &vert2);
		if(vert1 == 0 && vert2 == 0){
			break;
		}
		addEdge(G, vert1, vert2);
	
	}
	printGraph(out, G);
	int source;
	int distance;
	while(fgetc(in) != EOF){
		fscanf(in, "%d %d", &source, &distance);
		if(source == 0 && distance == 0){
			break;
		}
		List new = newList();
		fprintf(out, "\n");
		BFS(G, source);
		getPath(new, G, distance);
		fprintf(out, "The distance from %d to %d is ", source, distance);
		if(getDist(G, distance) == INF){
			fprintf(out, "Infinity\n");
			fprintf(out, "No %d-%d path exists\n", source, distance);
		}
		else{
			fprintf(out, "%d\n", length(new)-1);
			fprintf(out, "A shortest %d-%d path is: ", source, distance);
			printList(out, new);
			fprintf(out, "\n");
		}
		freeList(&new);
	}
	fprintf(out, "\n");
	freeGraph(&G);
	fclose(in);
	fclose(out);
	return(0);
}