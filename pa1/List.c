#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


// Constructors-Destructors ---------------------------------------------------

List NewList() {                                        // Does it need conditional
    List L;
    L = malloc(sizeof(ListObj));
    // Check precon: malloc must not return NULL
    if (L == NULL) {
        printf("List Error: newList: failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    assert(L!=NULL);
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->position = -1;
    return(L);
};

void freeList(List* pL) {
    if (*pL == NULL) {              // tantalo uses if (*pL != NULL) is this better?, if (pL != NULL && *pL != NULL)
        printf("List Error: freeList: failed to de-allocate memory");
        exit(EXIT_FAILURE);
    }
    while (length(*pL) > 0) { //while (!isEmpty(*pL))
        deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
}

// Access functions ----------------------------------------------------------- 
 
int length(List L) {
    if (L == NULL) {
        printf("List Error: length: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    return L->length;
};

int position(List L) {
    if (L == NULL) {
        printf("List Error: position: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    return L->position; 
}

ListElement front(List L) {
    if (L == NULL) {
        printf("List Error: front(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: front(): empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

ListElement back(List L) {
    if (L == NULL) {
        printf("List Error: back()): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: back(): empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
} 
 
ListElement get(List L) {
    if (L == NULL) {
        printf("List Error: get(): NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: get(): empty List\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: get(): position is negative");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    if (A == NULL) {
        printf("List Error: equals(): NULL List A Reference\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("List Error: equals(): NULL List B Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(A) != length(B)) {
        return false;
    }

    Node* currentA = A->front;
    Node* currentB = B->front;

    while (currentA != NULL && currentB != NULL) {
        if(currentA->data != currentB->data) {
            return false;
        }
        currentA = currentA->next;
        currentB = currentB->next;
    }

    return true;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
    if (L == NULL) {
        printf("List Error: clear(): NULL List Reference");
        exit(EXIT_FAILURE);
    }
    while (L->front != NULL) {
        deletFront(L);
    }
    L->length = 0;
    L-> position = -1;
    L->cursor = NULL;
}

void set(List L, ListElement x) {
    if (L == NULL) {
        printf("List Error: set(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: set(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: set(): position is not valid\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: moveFront(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        printf("List Error: moveFront(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
    L->position = 0;
}

void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: moveBack(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        printf("List Error: moveBack(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
    L->position = length(L) - 1;
}

void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: movePrev(): NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->front) {
        L->cursor = L->cursor->previous;
    } else if (L->cursor == NULL && L->cursor != L->front) {
        L->cursor = NULL;
    }
}

void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: moveNext(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next
    } else if (L->cursor == NULL  && L->cursor != L->back) {
        L->cursor = NULL
    }
}

void prepend(List L, ListElement data);

void append(List L, ListElement data);

void insertBefore(List L, ListElement data);

void insertAfter(List L, ListElement data);

void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: deleteFront(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        printf("List Error: deleteFront(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    
    Node* current = L->front;
    // If the list is only 1 long, special behavior b/c the list is now empty
    if (L->length == 1) {
        L->front = NULL;
        L->back = NULL;
    } else {
        L->front = current->next;
        L->front->previous = NULL;
    }

    free(current);
    L->length -= 1;
}

void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: deleteBack(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        printf("List Error: deleteBack(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    
    Node* current = L->back;

    if (L->length == 1) {
        L->front = NULL;
        L->back = NULL;
    } else {
        L->back = current->previous;
        L->back->next = NULL;
    }

    free(current);
    L->length -= 1;
} 

void delete(List L);

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L);

List copyList(List L);

List join(List A, List B);

List split(List L);

// blah blah blah