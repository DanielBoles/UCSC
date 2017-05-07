/*
 * Lex.c
 * Daniel Boles
 * dawboles
 * pa2
 * description: Sorting algorithm for List. Contains main.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


#define STRING_MAX_LENGTH 160

// Here the lexographic sorting algorithm happens based on insertion sort.
List insertionSort(char** arr, int length){
	List list = newList();
	if(length > 0){
		append(list, 0);
		
	}
	for(int i = 1; i<length; i++){
		char *hold = arr[i];
		int j = i-1;
		moveBack(list);
		while(j > -1 && strcmp(hold, arr[get(list)]) < 1){
			j--;
			movePrev(list);

		}
		if(index(list) == -1){
			prepend(list,i);

		}
		else{
			insertAfter(list,i);

		}
	}
	return list;
}

// allocates memory to a pointer to a copy of the string.
char *strdup(const char *s){
	char *d = malloc(strlen(s) + 1);
	if(d==NULL){
		return NULL;
	}
	strcpy(d,s);
	return d;
}

// Reads the string of words and outputs an array of the words
char** read(FILE* in, int wordCount){
	char** arr = malloc(sizeof(char**) * wordCount);
	char word[STRING_MAX_LENGTH];
	int i = 0;

	while(fscanf(in, "%1023s", word) == 1){ 
		arr[i] = strdup(word);
		i++;
	}

	
	return arr;
}

// Main opens the input and output files, performs the sort on the in, then writes to
// the output file in lexographic order.
int main(int argc, char* argv[]){
	int count = 0;
	char word[STRING_MAX_LENGTH];

	if(argc != 3){
		printf("Error: incorrect number of inputs");
		exit(1);
	}

	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");

	if(in == NULL){
		fprintf(stderr,"Unable to open file %s for reading", argv[1]);
		return 1;
	}
	if(out == NULL){
		fprintf(stderr,"Unable to open file %s for writing", argv[2]);
		return 1;
	}
	while(fscanf(in, "%1023s", word) == 1){
		count++;
	}

	fclose(in);
	in = fopen(argv[1], "r");
	char** words = read(in, count);

	List newList = insertionSort(words, count);

	for(moveFront(newList); index(newList) >= 0; moveNext(newList)){
		fprintf(out, "%s ", words[get(newList)]);
	}
	fclose(in);
	fclose(out);

	for(int k = 0; k < count; k++){
		free(words[k]);
	}
	free(words);
	clear(newList);
	free(newList);

	return 0;
}