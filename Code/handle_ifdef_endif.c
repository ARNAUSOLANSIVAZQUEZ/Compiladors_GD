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
#include "multistring.h"

char *handle_ifdef_endif(char *source_code, int index, int *len, MultiString *ms) {
    // Initialize result
    *len = 0;
    char *result = NULL;

    // Counter to track #ifdef structures index
    int ifdef_index = 0;

    // Find the first occurrence of #ifdef starting from the given index
    char *search_start = source_code + index;
    char *ifdef_start = strstr(search_start, "#ifdef");
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

            // Find the beginning of the content inside #ifdef
            char *content_start = ifdef_start;
            while (*content_start != '\n' && content_start < ifdef_end) {
                content_start++;
            }
            content_start++; // Move past the newline character

            // Calculate the length of the content inside #ifdef
            int content_len = ifdef_end - content_start;

            // Reallocate memory for result
            result = (char *)realloc(result, *len + content_len + 1); // +1 for null terminator
            if (!result) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            // Copy content inside #ifdef to result
            strncpy(result + *len, content_start, content_len);
            *len += content_len;
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
