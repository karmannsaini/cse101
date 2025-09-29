#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// private Node type
typedef struct Node{
    ListElement data;
    struct Node* next;
    struct Node* previous;
} Node;


// private ListObj type
typedef struct ListObj{
    Node* front;
    Node* back;
    Node* cursor;
    int length;
    int position;
} ListObj;

// newList()
// Returns reference to a new empty List object.
List NewList() {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->position = -1;
    return(L);
};

// freeList() 
// Frees heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL) {
    Node* current = (*pL)->back;
    while (current != NULL) {
        Node* temp = current->previous;
        free(current);
        current = temp;
    }
    free(*pL);
    *pL = NULL;
};