/* Author: Daniel Boles
 * Project: Lab5
 * Class: 12m
 */


//include libraries and headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

//Declare Node and Dictionary types

typedef struct NodeObjects {
	char* key;
	char* value;
	struct NodeObjects* next;

}NodeObjects;

typedef NodeObjects* Node;


Node newNode(char* k, char* val){
	Node N = malloc(sizeof(NodeObjects));
	assert(N != NULL);
	N->key = k;
	N->value = val;
	N->next = NULL;
	return N;

}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

typedef struct DictionaryObj{
	int itemCount;
	Node head;
	Node tail;
} DictionaryObj;

Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D != NULL);
	D->head = NULL;
	D->tail = NULL;
	D->itemCount = 0;
	return D;
}


void freeDictionary(Dictionary* pD){
	if(pD != NULL && *pD != NULL){
		free(*pD);
		*pD = NULL;	
	}
}

//Begin functions to manipulate Dictionary ADT

int isEmpty(Dictionary D){
	if(D == NULL){
		return 1;
	}
	return 0;
}

int size(Dictionary D){
	if(D != NULL){
		return D->itemCount;
	}
	return 0;
}


char* lookup(Dictionary D, char* k){
	
	int i = 0;

	if(D != NULL){
		Node N = D->head;
		for(i = 0; i < D->itemCount; i++){
			if(strcmp(N->key, k) == 0){
				return N->value;
			}
			N = N->next;
		}
	}
	return NULL;
	
}	


void insert(Dictionary D, char* k, char* v){
	if(D != NULL && lookup(D,k) == NULL){
		if(D->itemCount == 0){
			D->head = newNode(k,v);
			D->tail = D->head;

		}else{
			Node N = newNode(k,v);
			D->tail->next = N;
			D->tail = N;
		}
		D->itemCount++;
	}
}
void delete(Dictionary D, char* k){
	if(D != NULL && lookup(D,k) != NULL){
		Node N = D->head;
		if(strcmp(N->key, k) == 0){
			Node Hold = D->head;
			D->head = N->next;
			freeNode(&Hold);
		}
		else{
			while(N != NULL && N->next != NULL){
				if(strcmp(N->next->key, k) == 0){
					Node Hold = N;
					Node Hold2 = N->next;
					Hold->next = Hold2->next;
					N = Hold;
					freeNode(&Hold2);
				}
				N = N->next;			
			}
		}
		D->itemCount--;
	}
}

void makeEmpty(Dictionary D){
	D->head = NULL;
	D->tail = NULL;
	D->itemCount = 0;
}

//Print function

void printDictionary(FILE* out, Dictionary D){
	Node N;
	if(D != NULL){
		for(N = D->head; N != NULL; N = N->next){
			fprintf(out, "%s %s \n", N->key, N->value);
		}
	}
}
