/*
 * List.c
 * Daniel Boles
 * dawboles
 * pa2
 * description: This is the c file for a doubly linked list ADT. This consists of a node which points
 * forward and backward and creates a chain of elements 
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"


// Constructors-Destructors ---------------------------------------------------


typedef struct nodeObject{
	int data;
	struct nodeObject* prev;
	struct nodeObject* next;
}nodeObject;

typedef nodeObject* node;

node Node(int data){
	node newNode = malloc(sizeof(nodeObject));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

typedef struct ListObject{
	node head;
	node tail;
	node cursor;
	int length;
	int index;
} ListObject;

typedef struct ListObject* List;

List newList(){
	List newlist = malloc(sizeof(ListObject));
	assert(newlist != NULL);
	newlist->head = NULL; 
	newlist->tail = NULL;
	newlist->cursor = NULL;
	newlist->length = 0;
	newlist->index = -1;
	return newlist;
}

void freeList(List* pL){
	if(*pL == NULL){
		printf("Error: Cannot free from NULL List\n");
	}
	else{
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
	return;
}

// Access functions ----------------------------------------------------------- 

int length(List L){
	if(L == NULL){
		printf("Error: Cannot take length of NULL List\n");
		return -1;
	}
	return L->length;
}

int index(List L){
	if(L == NULL){
		printf("Error: Cannot take index of NULL List\n");
		return -1;
	}
	return L->index;
} 

int front(List L){
	if(L == NULL){
		printf("Error: Cannot find front of NULL List\n");
		return -1;
	}
	if(L->length > 0){
		return L->head->data;
	}

	return -1;
}

int back(List L){
	if(L == NULL){
		printf("Error: Cannot find back of NULL List\n");
		return -1;
	}
	if(L->length > 0){
		return L->tail->data;
	}
	return -1;
}

int get(List L){
	if(L == NULL){
		printf("Error: Cannot get data of NULL List\n");
		return -1;
	}
	if(L->length > 0){
		if(L->index >= 0){
			return L->cursor->data;
		}
	}
	return -1;
}

int equals(List A, List B){
	if(A == NULL || B == NULL){
		printf("Error: Cannot check equals of NULL List\n");
		return -1;
	}
	node right = A->head;
	node left = B->head;
	if(length(A) != length(B)){
		return 0;
	}
	for(int i=0; i<length(A); i++){
		if(right->data != left->data){
			return 0;
		}
		right = right->next;
		left = left->next;
	}
	free(right);
	free(left);
	return 1;
}

// Manipulation procedures ---------------------------------------------------- 

void clear(List L){
	if(L == NULL){
		printf("Error: Cannot clear NULL List\n");
		return;
	}
	L->cursor = L->tail;
	while(L->cursor){
		node hold = L->cursor;
		L->cursor = L->cursor->prev;
		free(hold);
	}
	L->head = NULL;
	L->tail = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
} 

void moveFront(List L){
	if(L == NULL){
		printf("Error: Cannot move to front of NULL List\n");
		return;
	}
	if(length(L) == 1){
		return;
	}
	L->cursor = L->head;
	L->index = 0;
	return;
}

void moveBack(List L){
	if(L == NULL){
		printf("Error: Cannot move to back of NULL List\n");
		return;
	}
	if(length(L) == 1){
		return;
	}
	L->cursor = L->tail;
	L->index = length(L)-1;
	return;
}

void movePrev(List L){
	if(L == NULL){
		printf("Error: Cannot move prev of NULL List\n");
		return;
	}
	L->index--;
	L->cursor = L->cursor->prev;
}

void moveNext(List L){
	if(L == NULL){
		printf("Error: Cannot move prev of NULL List\n");
		return;
	}
	if(L->cursor == L->tail){
		L->cursor = L->cursor->next;
		L->index = -1;
	}
	else{
		L->cursor = L->cursor->next;
		L->index++;
	}
}

void prepend(List L, int data){
	if(L == NULL){
		printf("Error: Cannot prepend to a NULL List\n");
		return;
	}
	node node = malloc(sizeof(struct nodeObject));
	node->data = data;
	node->next = L->head;
	if(length(L)==0){
		L->tail = node;
	}
	else{
		L->head->prev = node;
	}
	if(L->index > -1){
		L->index++;
	}
	L->head = node;
	L->length++;
}

void append(List L, int data){
	if(L == NULL){
		printf("Error: Cannot append to a NULL List\n");
		return;
	}
	node node = malloc(sizeof(struct nodeObject));
	node->data = data;
	node->prev = L->tail;
	if(length(L)==0){
		L->head = node;
		L->cursor = node;
		L->index = 0;
	}
	else{
		L->tail->next = node;
	}
	L->tail = node;
	L->length++;
}

void insertBefore(List L, int data){
	if(L == NULL){
		printf("Error: Cannot insert before to a NULL List\n");
		return;
	}
	if(L->length > 0 && L->index >= 0){
		node node = malloc(sizeof(struct nodeObject));
		node->data = data;
		node->prev = L->cursor->prev;
		node->next = L->cursor;
		if(node->prev != NULL){
			L->cursor->prev->next = node;
		}
		else{
			L->head = node;
		}
		L->index++;
		L->cursor->prev = node;
		L->length++;
	}
}

void insertAfter(List L, int data){
	if(L == NULL){
		printf("Error: Cannot insert after to a NULL List\n");
		return;
	}
	if(L->length > 0 && L->index >= 0){
		node node = malloc(sizeof(struct nodeObject));
		node->data = data;
		node->prev = L->cursor;
		node->next = L->cursor->next;
		if(node->next != NULL){
			L->cursor->next->prev = node;
		}
		else{
			L->tail = node;
		}
		L->cursor->next = node;
		L->length++;
	}
}

void deleteFront(List L){
	if(L == NULL){
		printf("Error: Cannot delete front of a NULL List\n");
		return;
	}
	if(L->length >0){
		if(L->cursor == L->head){
			L->cursor = NULL;
		}
		if(L->head == L->tail){
			L->tail = NULL;
		}
		L->head = L->head->next;
		if(L->index != -1){
			L->index--;
		}
		L->length--;
	}
}

void deleteBack(List L){
	if(L == NULL){
		printf("Error: Cannot delete back of a NULL List\n");
		return;
	}
	if(L->length >0){
		if(L->cursor == L->tail){
			L->cursor = NULL;
		}
		if(L->head == L->tail){
			L->head = NULL;
		}
		L->tail = L->tail->prev;
		if(L->index == L->length - 1){
			L->index = -1;
		}
		L->length--;
	}
}

void delete(List L){
	if(L == NULL){
		printf("Error: Cannot delete back of a NULL List\n");
		return;
	}
	if(L->cursor == NULL || L->index == -1){
		printf("Error: passing a NULL pointer in a non NULL List\n");
		return;
	}
	if(L->length > 0 && L->index >= 0){
		if(L->cursor == L->head){
			deleteFront(L);
		}
		if(L->cursor == L->tail){
			deleteBack(L);
		}
		else{
			node hold = L->cursor;
			L->cursor->next->prev = L->cursor->prev;
			L->cursor->prev->next = L->cursor->next;
			L->cursor = NULL;
			L->index = -1;
			L->length--;
			free(hold);
		}
	}
}

// Other operations ----------------------------------------------------------- 

void printList(FILE* out, List L){
	if(L == NULL){
		printf("Error: Cannot print a NULL List\n");
		return;
	}
	if(out == NULL){
		printf("Error: passing a NULL FILE pointer in a non NULL List\n");
		return;
	}
	node hold = L->head;
	for(;hold != NULL; hold = hold->next){
		fprintf(out, "%d ", hold->data);
	}
	free(hold);

}

List copyList(List L){
	if(L == NULL){
		printf("Error: Cannot copy a NULL List\n");
		return NULL;
	}
	List newCopy = malloc(sizeof(ListObject));
	append(newCopy, L->head->data);
	L->cursor = L->head->next;
	while(L->cursor){
		append(newCopy, L->cursor->data);
		L->cursor = L->cursor->next;
	}
	newCopy->index = -1;
	L->cursor = L->head;
	newCopy->length = L->length;
	return newCopy;
}