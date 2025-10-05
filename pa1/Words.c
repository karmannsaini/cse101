#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Assuming List.h is available in the current directory
#include "List.h"

// Define constants for file handling and parsing
#define MAX_LINE_LENGTH 1000
#define INITIAL_ARRAY_CAPACITY 10

// The official list of non-alphabetic characters to discard, from the pa1.pdf handout.
const char* DELIMITERS = "\t\n\r\\\"\'.,<>/?;:[{]}|`~!@#$%^&*()_+0123456789";

// Function prototype is required for C to correctly resolve the function before main()
int find_word(char** word_array, int count, const char* word); 

// Helper function to check if a word already exists in the array
// Returns the index if found, or -1 if not found.
int find_word(char** word_array, int count, const char* word) {
    for (int i = 0; i < count; i++) {
        // strcmp returns 0 if strings are identical
        if (strcmp(word_array[i], word) == 0) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    
    FILE *in_file, *out_file;
    char *input_file_name, *output_file_name;
    
    // For reading lines from the file
    char line[MAX_LINE_LENGTH];
    char* token;
    
    // Dynamic Array to hold unique words (array of char pointers)
    char** unique_words = NULL;
    int word_count = 0;
    int capacity = INITIAL_ARRAY_CAPACITY;

    // 1. Check command line arguments (Required: Words <input file> <output file>)
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Assign file names
    input_file_name = argv[1];
    output_file_name = argv[2];

    // 2. Open the input file and check for errors
    in_file = fopen(input_file_name, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Words Error: Unable to open file %s for reading.\n", input_file_name);
        exit(EXIT_FAILURE);
    }

    // 3. Open the output file and check for errors
    out_file = fopen(output_file_name, "w");
    if (out_file == NULL) {
        fclose(in_file); 
        fprintf(stderr, "Words Error: Unable to open file %s for writing.\n", output_file_name);
        exit(EXIT_FAILURE);
    }
    
    // Initialize the dynamic array
    unique_words = (char**)calloc(capacity, sizeof(char*));
    if (unique_words == NULL) {
        fprintf(stderr, "Words Error: Initial memory allocation failed.\n");
        fclose(in_file);
        fclose(out_file);
        exit(EXIT_FAILURE);
    }
    
    // --- PART 1: FILE PARSING AND WORD STORAGE ---
    
    // Read the input file line by line
    while (fgets(line, MAX_LINE_LENGTH, in_file) != NULL) {
        
        // FIX: Explicitly remove the newline character before tokenizing.
        // This makes tokenization more reliable as newline is not part of the token.
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        
        // Get the first token (word)
        token = strtok(line, DELIMITERS);

        while (token != NULL) {
            
            // If the word is unique (not found in the array yet)
            if (find_word(unique_words, word_count, token) == -1) {
                
                // Check if capacity needs to be expanded
                if (word_count == capacity) {
                    capacity *= 2;
                    // Attempt to reallocate memory for the expanded array
                    char** temp = (char**)realloc(unique_words, capacity * sizeof(char*));
                    if (temp == NULL) {
                        fprintf(stderr, "Words Error: Array reallocation failed.\n");
                        // Clean up all memory before exiting
                        for(int i = 0; i < word_count; i++) {
                            free(unique_words[i]);
                        }
                        free(unique_words);
                        fclose(in_file);
                        fclose(out_file);
                        exit(EXIT_FAILURE);
                    }
                    unique_words = temp;
                }
                
                // Store a copy of the word in the dynamic array
                unique_words[word_count] = (char*)malloc(strlen(token) + 1);
                if (unique_words[word_count] == NULL) {
                    fprintf(stderr, "Words Error: Word string allocation failed.\n");
                    // Cleanup before exiting due to severe error
                    for(int i = 0; i < word_count; i++) {
                        free(unique_words[i]);
                    }
                    free(unique_words);
                    fclose(in_file);
                    fclose(out_file);
                    exit(EXIT_FAILURE);
                }
                strcpy(unique_words[word_count], token);
                word_count++;
            }
            
            // Get the next token in the line
            token = strtok(NULL, DELIMITERS);
        }
    }

    // --- PART 2: INDIRECT SORTING LOGIC ---
    List sorted_indices = newList();
    int current_index;
    
    // The core of the sorting: iterate through the array and insert the index
    // into the List based on the alphabetical order of the corresponding word.
    for (int i = 0; i < word_count; i++) {
        
        // Index of the word we are currently trying to place
        current_index = i; 
        
        // 1. Start the cursor at the front of the List
        moveFront(sorted_indices);
        
        // 2. Iterate through the List until the correct position is found
        while (position(sorted_indices) != -1) {
            
            // Get the index of the word currently under the cursor
            int list_index = get(sorted_indices);
            
            // Comparison using strcmp():
            // If the new word (current_index) is alphabetically BEFORE the
            // word currently in the list (list_index), we found our spot.
            if (strcmp(unique_words[current_index], unique_words[list_index]) < 0) {
                // Found the spot! Insert the new index before the cursor.
                insertBefore(sorted_indices, current_index);
                break; // Exit the while loop
            }
            
            // Move to the next index in the List
            moveNext(sorted_indices);
        }
        
        // 3. If the loop finished (cursor is undefined), the new index belongs at the back
        if (position(sorted_indices) == -1) {
            append(sorted_indices, current_index);
        }
    }

    // --- PART 3: OUTPUT AND CLEANUP ---
    
    // 1. Print the List of sorted indices (Required format: (i0, i1, i2, ...))
    fprintf(out_file, "(");
    moveFront(sorted_indices);
    while (position(sorted_indices) != -1) {
        fprintf(out_file, "%d", get(sorted_indices));
        moveNext(sorted_indices);
        if (position(sorted_indices) != -1) {
            fprintf(out_file, ", ");
        }
    }
    fprintf(out_file, ")\n\n"); // End with closing parenthesis and two newlines

    // 2. Print the words in alphabetical order using the List of indices
    moveFront(sorted_indices);
    while (position(sorted_indices) != -1) {
        int word_idx = get(sorted_indices);
        fprintf(out_file, "%s\n", unique_words[word_idx]);
        moveNext(sorted_indices);
    }
    
    // 3. Clean up allocated memory 
    for (int i = 0; i < word_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);
    freeList(&sorted_indices); // Free the List ADT memory!
    
    // 4. Close files
    fclose(in_file);
    fclose(out_file);

    return EXIT_SUCCESS;
}