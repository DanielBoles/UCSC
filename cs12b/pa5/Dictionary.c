/* Author: Daniel Boles
 * Project: pa5
 * Class: 12b
 */


//include libraries and headers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"


typedef struct NodeObject{
	char* key;
	char* val;
	struct NodeObject* next;
} NodeObject;

typedef NodeObject* Node;

Node newNode(char* k, char* v){
	Node N = malloc(sizeof(Node));
	assert(N != NULL);
	N->val = v;
	N->key = k;
	N->next = NULL;
	return N;
}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

const int tableSize = 107;

typedef struct DictionaryObj{
	Node* table;
	int itemCount;
}DictionaryObj;


Dictionary newDictionary(){
	Dictionary D = malloc(sizeof(Dictionary));
	assert(D != NULL);
	D->table = calloc(tableSize, sizeof(Node));
	assert(D->table != NULL);
	D->itemCount = 0;
	return D;
}

void freeDictionary(Dictionary* pD){
	if(pD != NULL && *pD != NULL){
		makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}

int isEmpty(Dictionary D){
	if(D == NULL){
		fprintf(stderr, "%s\n", "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
    } 
    if(D->itemCount > 0){ 
       return 0; 
    } 
    return 1; 
} 

int size(Dictionary D){ 
    return D->itemCount; 
} 

Node findKey(Dictionary D, char* k){ 
    Node N; 
    N = D->table[hash(k)]; 
    while(N != NULL){ 
       if(strcmp(N->key,k)== 0) 
	        break; 
       N = N->next; 
    } 
    return N; 
} 

char* lookup(Dictionary D, char* k){ 
    if(D == NULL){ 
        fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary\n"); 
        exit(EXIT_FAILURE); 
    } 
    if(D->itemCount == 0){ 
        fprintf(stderr, "Dictionary Error: calling lookup() on empty Dictionary reference"); 
        exit(EXIT_FAILURE); 
    } 
    if(findKey(D,k) == NULL){
    	return NULL; 
    }
    else{
    	return findKey(D,k)->val; 
    }
} 
  
void insert(Dictionary D, char* k, char* v){ 
    Node N; 
    int i = hash(k); 
    if(D == NULL){ 
        fprintf(stderr, "Dictionary Error: calling insert on NULL Dictionary\n"); 
        exit(EXIT_FAILURE); 
    } 
    if( findKey(D, k) != NULL){ 
        fprintf(stderr, "Dictionary Error: calling insert() on a pre-existing key"); 
        exit(EXIT_FAILURE); 
    }  
    if(D->table[i] == NULL){ 
        D->table[i]  = newNode(k, v);        
    }else{ 
        N = newNode(k, v); 
        N->next = D->table[i]; 
        D->table[i] = N;
    } 
    D->itemCount++;  
} 

void makeEmpty(Dictionary D){ 
    for(int i = 0; i<tableSize; i++){ 
        while(D->table[i] != NULL){ 
            Node N; 
            N = D->table[i]; 
            D->table[i] = N->next; 
            freeNode(&N); 
            N = NULL; 
        } 
    }
    D->itemCount = 0;  
} 

void delete(Dictionary D, char* k){ 
    Node N; 
    Node A; 
    if(findKey(D,k) == NULL){ 
        fprintf(stderr, "errror: key not found\n"); 
        exit(EXIT_FAILURE); 
    } 
    N = findKey(D,k); 
    if(N == D->table[hash(k)] && N->next == NULL){ 
        N = NULL; 
        freeNode(&N); 
    }else if(N == D->table[hash(k)]){ 
        D->table[hash(k)] = N->next; 
        N = NULL; 
        freeNode(&N); 
    }else{ 
        A = D->table[hash(k)]; 
        while(A->next != N){ 
            A = A->next; 
        } 
        A->next = N->next; 
        freeNode(&N); 
    } 
    D->itemCount--; 
} 

void printDictionary(FILE* out, Dictionary D){ 
    Node N; 
    if(D == NULL){ 
        fprintf(stderr, "Dictionary Error: calling printDictionary() on NULL Dictionary reference\n"); 
        exit(EXIT_FAILURE); 
    } 
    for(int i = 0; i < tableSize; i++){ 
        N = D->table[i]; 
        while(N != NULL){ 
            fprintf(out, "%s %s \n" , N->key, N->val); 
            N = N->next; 
        } 
    }  
} 
 
unsigned int rotate_left(unsigned int value, int shift) { 
    int sizeInBits = 8*sizeof(unsigned int); 
    shift = shift & (sizeInBits - 1); 
    if ( shift == 0 ) 
        return value; 
    return (value << shift) | (value >> (sizeInBits - shift)); 
}   

unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554; 
    while (*input) { 
        result ^= *input++; 
        result = rotate_left(result, 5); 
    }   
    return result; 
}

int hash(char* key){ 
    return pre_hash(key)%tableSize; 
} 
 