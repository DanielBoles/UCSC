/*
 * List.h
 * Daniel Boles
 * dawboles
 * pa2
 * description: This is the header file for a doubly linked list ADT. This consists of a node which points
 * forward and backward and creates a chain of elements 
 *
*/

typedef struct ListObject* List;
// Constructors-Destructors --------------------------------------------------- 
List newList(void); 
void freeList(List* pL);  
// Access functions ----------------------------------------------------------- 
int length(List L); 
int index(List L); 
int front(List L); 
int back(List L); 
int get(List L); 
int equals(List A, List B);  
// Manipulation procedures ---------------------------------------------------- 
void clear(List L); 
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L); 
void moveNext(List L); 
void prepend(List L, int data); 
void append(List L, int data); 
void insertBefore(List L, int data); 
void insertAfter(List L, int data); 
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);  
// Other operations ----------------------------------------------------------- 
void printList(FILE* out, List L); 
List copyList(List L); 