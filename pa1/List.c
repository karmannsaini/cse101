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

List NewList() {                                        // Does it need conditional
    List L;
    L = malloc(sizeof(ListObj));
    // Check precon: malloc must not return NULL
    if (L == NULL) {
        printf("List Error: newList: failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->position = -1;
    return(L);
};

void freeList(List* pL) {
    if (*pL == NULL) {
        printf("List Error: freeList: failed to de-allocate memory");
        exit(EXIT_FAILURE);
    }
    while (length(*pL) > 0) {
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
        printf("List Error: front: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        printf("List Error: front: length is zero");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

ListElement back(List L) {
    if (L == NULL) {
        printf("List Error: back: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: back: length is zero");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
} 
 
ListElement get(List L) {
    if (L == NULL) {
        printf("List Error: get: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: get: length is zero");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: get: position is negative");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    moveFront(A);
    moveFront(B);

    if (A == NULL || B == NULL) {
        printf("List Error: equals: NULL List Reference");
        exit(EXIT_FAILURE);
    }
    if (length(A) != length(B)) {
        return false;
    }
    while (position(A) < length(A)) {

    }
}

// Manipulation procedures ----------------------------------------------------


void clear(List L); 

void set(List L, ListElement x);

void moveFront(List L) {
    if (L == NULL || L->length <= 0) {
        printf("List Error: moveFront: length is zero or NULL List Reference");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->front;
}

void moveBack(List L) {
    if (L == NULL || L->length <= 0) {
        printf("List Error: moveBack: length is zero or NULL List Reference");
        exit(EXIT_FAILURE);
    }
    L->cursor = L->back;
}

// void movePrev(List L) {
//     if (L == NULL || L->length <= 0) {
//         printf("List Error: movePrev: length is zero or NULL List Reference");
//         exit(EXIT_FAILURE);
//     }
//     if (L->cursor != L->front && L->cursor != NULL) {
//         L->cursor = L->cursor->previous;
//     } else if (L->cursor == L->front && L->cursor != NULL) {
//         L->cursor = NULL;
//     }
// }

void deleteFront(List L) {
    if (L == NULL || L->length <= 0) {
        printf("List Error: deleteFront: length is zero or NULL List Reference");
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
    if (L == NULL || L->length <= 0) {
        printf("List Error: deleteBack: length is zero or NULL List Reference");
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