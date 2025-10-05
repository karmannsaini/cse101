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

List newList() {
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
    //we need to check both pL and *pL and that is why
    //a single if is being used
    if (pL != NULL && *pL != NULL) {
        while ((*pL)->length > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
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
        deleteFront(L);
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
        L->position -= 1;
    } else if (L->cursor != NULL && L->cursor == L->front) {
        L->cursor = NULL;
        L->position = -1;
    }
}

void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: moveNext(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->position += 1;
    } else if (L->cursor != NULL  && L->cursor == L->back) {
        L->cursor = NULL;
        L->position = -1;
    }
}

void prepend(List L, ListElement data) {
    if (L == NULL) {
        printf("List Error: prepend(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("List Error: prepend(): failed to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;


    if (isEmpty(L)) {
        L->front = newNode;
        L->back = newNode;
        L->cursor = NULL;
        L->position = -1;

    } else {
        L->front->previous = newNode;
        newNode->next = L->front;
        L->front = newNode;
        
        if (L->position != -1) {
            L->position += 1;
        }
    }
    L->length += 1;
}

void append(List L, ListElement data) {
    if (L == NULL) {
        printf("List Error: append(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("List Error: append(): failed to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->previous = NULL;


    if (isEmpty(L)) {
        L->front = newNode;
        L->back = newNode;
        L->cursor = NULL;
        L->position = -1;
    } else {
        L->back->next = newNode;
        newNode->previous = L->back;
        L->back = newNode;
    }
    L->length += 1;
}

void insertBefore(List L, ListElement data) {
    if (L == NULL) {
        printf("List Error: insertBefore(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: insertBefore(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: insertBefore(): position is not valid\n");
        exit(EXIT_FAILURE);
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("List Error: insertBefore(): failed to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = L->cursor;
    
    if (L->cursor->previous != NULL) {
        newNode->previous = L->cursor->previous;
        L->cursor->previous->next = newNode;
        L->cursor->previous = newNode;
    } else {
        L->cursor->previous = newNode;
        newNode->previous = NULL;
        L->front = newNode;
    }
    L->position +=1;
    L->length += 1;
}

void insertAfter(List L, ListElement data) {
    if (L == NULL) {
        printf("List Error: insertAfter(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: insertAfter(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: insertAfter(): position is not valid\n");
        exit(EXIT_FAILURE);
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("List Error: insertAfter(): failed to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->previous = L->cursor;
    
    //if the cursor was not at the back
    if (L->cursor->next != NULL) {
        newNode->next = L->cursor->next;
        L->cursor->next->previous = newNode;
        L->cursor->next = newNode;
    } else {
        L->cursor->next = newNode;
        newNode->next = NULL;
        L->back = newNode;
    }
    L->length += 1;
}

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
    
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->position = -1;
    } else if (L->position > 0) {
        L->position--;
    }
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
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->position = -1;
    }
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

void delete(List L) {
    if (L == NULL) {
        printf("List Error: delete(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: delete(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: delete(): position is not valid\n");
        exit(EXIT_FAILURE);
    }
    
    Node* current = L->cursor; //deals w dangling pointer

    if (L->cursor == L->front){
        deleteFront(L);
    } else if (L->cursor == L->back){
        deleteBack(L);
    } else {        // cursor is in middle of list
        L->cursor->previous->next = L->cursor->next;
        L->cursor->next->previous = L->cursor->previous;
        free(current);
        L->length -= 1;
    }

    L->cursor = NULL;
    L->position = -1;
}

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: printList(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (!isEmpty(L)) {
        Node* current = L->front;
        while (current != NULL) {
            fprintf(out,"%d ", current->data);
            current = current->next;
        }
    }
}

List copyList(List L){
    if (L == NULL) {
        printf("List Error: copyList(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    List N = newList();
    Node* current = L->front;

    while (current != NULL) {
        append(N, current->data);
        current = current->next;
    }

    return N;
}

List join(List A, List B) {
    if (A == NULL) {
        printf("List Error: join(): NULL List A Reference\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("List Error: join(): NULL List B Reference\n");
        exit(EXIT_FAILURE);
    }

    List C = copyList(A);

    Node* current = B->front;
    while (current != NULL) {
        append(C, current->data);
        current = current->next;
    }
    
    return C;
}

List split(List L) {
    if (L == NULL) {
        printf("List Error: split(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: split(): length is zero\n");
        exit(EXIT_FAILURE);
    }
    if (position(L) < 0) {
        printf("List Error: split(): position is not valid\n");
        exit(EXIT_FAILURE);
    }

    List S = newList();
        
    while (L->front != L->cursor) {
        Node* temp = L->front;
        L->front = L->front->next;
        if (L->front != NULL) {
            L->front->previous = NULL;
        }

        temp->next = NULL;
        temp->previous = S->back;
        if (S->back != NULL) {
            S->back->next = temp;
        }
        S->back = temp;
        if (S->front == NULL) {
            S->front = temp;
        }
        L->length--;
        S->length++;
    }

    L->position = 0;

    return S;
}

bool isEmpty(List L) {
    if (L == NULL) {
        printf("List Error: isEmpty(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length == 0);
}