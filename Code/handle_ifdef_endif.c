/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_ifdef_endif.c
* Ifdef directive handler.
*
*
* Responsible: Ariadna Prat
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle_ifdef_endif.h"

char *handle_ifdef_endif(char *source_code, int index, int *len) {
    // Initialize result
    *len = 0;
    char *result = NULL;

    // Counter to track #ifdef structures index
    int ifdef_index = 0;

    // Find the first occurrence of #ifdef
    char *ifdef_start = strstr(source_code, "#ifdef");
    if (!ifdef_start) {
        return NULL; // No #ifdef-#endif structure found
    }

    // Loop to process each #ifdef-#endif structure
    while (ifdef_start) {
        // If index matches the index of current #ifdef structure, proceed
        if (ifdef_index == index) {
            // Find the end of current #ifdef structure
            char *ifdef_end = strstr(ifdef_start, "#endif");
            if (!ifdef_end) {
                // Current #ifdef-#endif structure is incomplete
                return NULL;
            }

            // Find the string associated with #ifdef
            char ifdef_str[256];
            if (sscanf(ifdef_start, "#ifdef %s", ifdef_str) != 1) {
                // Failed to read name after #ifdef
                return NULL;
            }

            // Find the string associated with #define
            char define_str[256];
            char *define_start = strstr(source_code, "#define");
            while (define_start && define_start < ifdef_end) {
                if (sscanf(define_start, "#define %s", define_str) == 1 && strcmp(ifdef_str, define_str) == 0) {
                    break;
                }
                define_start = strstr(define_start + 1, "#define");
            }
            if (!define_start || define_start >= ifdef_end) {
                // Corresponding #define not found
                return NULL;
            }

            // Calculate the length of current structure
            int block_len = ifdef_end - ifdef_start + strlen("#endif");

            // Reallocate memory for result
            result = (char *)realloc(result, *len + block_len + 1); // +1 for null terminator
            if (!result) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            // Copy current structure to result
            strncpy(result + *len, ifdef_start, block_len);
            *len += block_len;
            result[*len] = '\0'; // Add null terminator

            // Structure found and processed, exit loop
            break;
        }

        // Increment #ifdef structures index
        ifdef_index++;

        // Find the next occurrence of #ifdef
        ifdef_start = strstr(ifdef_start + 1, "#ifdef");
    }

    return result;
}
