/*
Karmann Saini
CruzID:2034335
pa1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "List.h"

#define MAX_LINE_LENGTH 1000
#define INITIAL_ARRAY_CAPACITY 10

// Non-alphabetic characters to discard from the handout.
const char* DELIMITERS = " \t\n\r\\\"\'.,<>/?;:[{]}|`~!@#$%^&*()_+=-0123456789";

// Function prototype is required for C to correctly resolve the function before main()
int find_word(char** word_array, int count, const char* word);

// Check if a word exists in the array
int find_word(char** word_array, int count, const char* word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(word_array[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {

    FILE *in_file, *out_file;
    char line[MAX_LINE_LENGTH];
    char* token;

    char** unique_words = NULL;
    int word_count = 0;
    int capacity = INITIAL_ARRAY_CAPACITY;

    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "Words Error: Unable to open file %s for reading.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file
    out_file = fopen(argv[2], "w");
    if (out_file == NULL) {
        fclose(in_file);
        fprintf(stderr, "Words Error: Unable to open file %s for writing.\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    unique_words = (char**)calloc(capacity, sizeof(char*));
    if (unique_words == NULL) {
        fprintf(stderr, "Words Error: Initial memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(line, MAX_LINE_LENGTH, in_file) != NULL) {

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        token = strtok(line, DELIMITERS);

        while (token != NULL) {
            if (find_word(unique_words, word_count, token) == -1) {
                if (word_count == capacity) {
                    capacity *= 2;
                    char** temp = (char**)realloc(unique_words, capacity * sizeof(char*));
                    if (temp == NULL) {
                        fprintf(stderr, "Words Error: Array reallocation failed.\n");
                        exit(EXIT_FAILURE);
                    }
                    unique_words = temp;
                }
                unique_words[word_count] = (char*)malloc(strlen(token) + 1);
                if (unique_words[word_count] == NULL) {
                    fprintf(stderr, "Words Error: Word string allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
                strcpy(unique_words[word_count], token);
                word_count++;
            }
            token = strtok(NULL, DELIMITERS);
        }
    }

    List sorted_indices = newList();
    
    if (word_count > 0) {
        append(sorted_indices, 0);
    }
    
    for (int i = 1; i < word_count; i++) {
        moveFront(sorted_indices);
        while (position(sorted_indices) != -1) {
            int list_index = get(sorted_indices);
            if (strcmp(unique_words[i], unique_words[list_index]) < 0) {
                insertBefore(sorted_indices, i);
                break;
            }
            moveNext(sorted_indices);
        }
        if (position(sorted_indices) == -1) {
            append(sorted_indices, i);
        }
    }
    
    fprintf(out_file, "(");
    moveFront(sorted_indices);
    while (position(sorted_indices) != -1) {
        fprintf(out_file, "%d", get(sorted_indices));
        moveNext(sorted_indices);
        if (position(sorted_indices) != -1) {
            fprintf(out_file, ", ");
        }
    }
    fprintf(out_file, ")\n\n");

    moveFront(sorted_indices);
    while (position(sorted_indices) != -1) {
        int word_idx = get(sorted_indices);
        fprintf(out_file, "%s\n", unique_words[word_idx]);
        moveNext(sorted_indices);
    }
    
    for (int i = 0; i < word_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);
    freeList(&sorted_indices);
    
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}