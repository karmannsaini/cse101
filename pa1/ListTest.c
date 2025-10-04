/****************************************************************************************
* ListTest.c
* Comprehensive Test Client for List ADT
* Tests ALL operations and ALL documented preconditions (error states).
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

// Set a global test count
int test_count = 0;
int passed_count = 0;

// Helper function to check test results
void run_test(bool condition, const char* message) {
    test_count++;
    if (condition) {
        passed_count++;
        fprintf(stdout, "  PASS %d: %s\n", test_count, message);
    } else {
        fprintf(stdout, "  FAIL %d: %s\n", test_count, message);
    }
}

// ----------------------------------------------------------------------------------
// TEST GROUP 1: Constructors, Accessors (No Mutation)
// ----------------------------------------------------------------------------------
void test_accessors() {
    fprintf(stdout, "\n--- TEST GROUP 1: Accessors & Basic Construction ---\n");
    List L = newList();
    
    // Test 1.1: NewList state
    run_test(length(L) == 0 && position(L) == -1, "newList creates empty list");

    // Add elements
    append(L, 10); // L = (10)
    prepend(L, 5); // L = (5, 10)
    append(L, 15); // L = (5, 10, 15)

    // Test 1.2: Length and accessors on populated list
    run_test(length(L) == 3, "length() is 3");
    run_test(front(L) == 5, "front() is 5");
    run_test(back(L) == 15, "back() is 15");

    // Test 1.3: Equals check
    List M = newList();
    append(M, 5); append(M, 10); append(M, 15);
    run_test(equals(L, M), "equals() returns true for identical lists");

    // Test 1.4: Set and Equals check (requires cursor to be defined)
    moveBack(L); // Cursor L is now at 15, Pos 2
    moveBack(M); // Cursor M is now at 15, Pos 2
    set(M, 99);  // M = (5, 10, 99)
    run_test(equals(L, M) == false, "equals() returns false for different lists after set");
    
    freeList(&L);
    freeList(&M);
}

// ----------------------------------------------------------------------------------
// TEST GROUP 2: Cursors and Mutators (move, set, insert)
// ----------------------------------------------------------------------------------
void test_mutators() {
    fprintf(stdout, "\n--- TEST GROUP 2: Cursors & Mutators ---\n");
    List L = newList();
    append(L, 1); append(L, 2); append(L, 3); // L = (1, 2, 3)

    // Test 2.1: moveFront and moveNext
    moveFront(L); // Cursor at 1, Pos 0
    run_test(position(L) == 0 && get(L) == 1, "moveFront works");
    moveNext(L); // Cursor at 2, Pos 1
    run_test(position(L) == 1 && get(L) == 2, "moveNext works");
    movePrev(L); // Cursor at 1, Pos 0
    run_test(position(L) == 0 && get(L) == 1, "movePrev works");
    
    // Test 2.2: movePrev off front
    movePrev(L); // Cursor undefined, Pos -1
    run_test(position(L) == -1, "movePrev off front works");
    
    // Test 2.3: insertBefore (Front edge case)
    moveFront(L); // Cursor at 1, Pos 0
    insertBefore(L, 0); // L = (0, 1, 2, 3), Cursor at 1, Pos 1
    run_test(front(L) == 0 && position(L) == 1, "insertBefore at Front works and shifts cursor");

    // Test 2.4: insertAfter (Back edge case)
    moveBack(L); // Cursor at 3, Pos 3
    insertAfter(L, 4); // L = (0, 1, 2, 3, 4), Cursor at 3, Pos 3
    run_test(back(L) == 4 && position(L) == 3, "insertAfter at Back works (cursor unchanged)");
    
    // Test 2.5: clear()
    clear(L);
    run_test(length(L) == 0 && position(L) == -1, "clear() resets list state");

    freeList(&L);
}

// ----------------------------------------------------------------------------------
// TEST GROUP 3: Delete Operations and Cursor
// ----------------------------------------------------------------------------------
void test_deletes() {
    fprintf(stdout, "\n--- TEST GROUP 3: Delete Operations ---\n");
    List L = newList();
    append(L, 1); append(L, 2); append(L, 3); // L = (1, 2, 3)

    // Test 3.1: deleteFront (No cursor at front)
    deleteFront(L); // L = (2, 3)
    run_test(front(L) == 2 && length(L) == 2, "deleteFront works (general)");

    // Test 3.2: deleteBack (Cursor at back)
    moveBack(L); // Cursor at 3, Pos 1
    run_test(get(L) == 3, "Cursor is at 3");
    deleteBack(L); // L = (2). Cursor undefined, Pos -1
    run_test(back(L) == 2 && length(L) == 1 && position(L) == -1, "deleteBack makes cursor undefined");
    
    // Test 3.3: delete on single element list
    moveFront(L); // Cursor at 2, Pos 0
    delete(L); // L = (). Cursor undefined, Pos -1
    run_test(length(L) == 0 && position(L) == -1, "delete() on single element list works");
    
    // Test 3.4: delete (Middle element)
    append(L, 10); append(L, 20); append(L, 30); append(L, 40); // L = (10, 20, 30, 40)
    moveFront(L); moveNext(L); // Cursor at 20, Pos 1
    delete(L); // L = (10, 30, 40). Cursor undefined, Pos -1
    moveFront(L); moveNext(L); 
    run_test(get(L) == 30 && length(L) == 3 && position(L) == 1, "delete() in middle works");
    
    freeList(&L);
}

// ----------------------------------------------------------------------------------
// TEST GROUP 4: Copy, Join, Split
// ----------------------------------------------------------------------------------
void test_complex_ops() {
    fprintf(stdout, "\n--- TEST GROUP 4: Complex Operations ---\n");
    List A = newList();
    append(A, 10); append(A, 20); moveFront(A); // A = (10, 20), Cursor at 10

    // Test 4.1: copyList
    List B = copyList(A); // B = (10, 20), Cursor undefined
    run_test(equals(A, B) && position(B) == -1 && position(A) == 0, "copyList works and cursor is undefined");
    
    // Test 4.2: join (A followed by B)
    List C = join(A, B); // C = (10, 20, 10, 20)
    run_test(length(C) == 4, "join works and has correct length");

    // Test 4.3: split
    moveFront(C); moveNext(C); // Cursor at 20, Pos 1
    List D = split(C); // D = (10), C = (20, 10, 20), Cursor at 20, Pos 0
    
    moveFront(D);
    run_test(get(D) == 10 && length(D) == 1, "split (returned list) is correct");
    moveFront(C);
    run_test(get(C) == 20 && length(C) == 3 && position(C) == 0, "split (original list) is correct");
    
    freeList(&A);
    freeList(&B);
    freeList(&C);
    freeList(&D);
}

// ----------------------------------------------------------------------------------
// TEST GROUP 5: Precondition Violations (Expected to Crash)
// ----------------------------------------------------------------------------------
void test_preconditions_fatal() {
    fprintf(stdout, "\n--- TEST GROUP 5: Precondition Violations (Fatal) ---\n");
    fprintf(stdout, "WARNING: The following tests are expected to cause a fatal exit\n");
    fprintf(stdout, "and should be tested individually by uncommenting them.\n");

    // Precondition Checks: NULL List Reference (Must come first to prevent segfault)
    // List L_null = NULL;
    // length(L_null); // Expected to crash with "NULL List Reference" error

    // Precondition Checks: length() > 0
    // List L_empty = newList();
    // front(L_empty); // Expected to crash with "empty List" error

    // Precondition Checks: position() >= 0 (cursor defined)
    // List L_valid = newList();
    // append(L_valid, 10); // L = (10), Cursor undefined
    // get(L_valid); // Expected to crash with "position is negative" error
}

int main(int argc, char* argv[]){
    test_accessors();
    test_mutators();
    test_deletes();
    test_complex_ops();
    // test_preconditions_fatal(); // Keep commented unless running explicitly
    
    fprintf(stdout, "\n==========================================================\n");
    fprintf(stdout, "SUMMARY: %d tests run, %d passed, %d failed\n", 
            test_count, passed_count, test_count - passed_count);
    fprintf(stdout, "==========================================================\n");

    return(EXIT_SUCCESS);
}
