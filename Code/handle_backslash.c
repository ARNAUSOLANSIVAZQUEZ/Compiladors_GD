/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_backslash.c
* Backslash directive handler.
*
*
* Responsible: Ariadna Prat
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256
#include "backslash.h"

char* handle_backslash(char* source_code, size_t* size_source_code, int i) {
    char *result = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    size_t source_length = strlen(source_code);
    size_t result_length = 0;

    // Iterate through each character of the source code starting from position i
    for (int j = i; j < source_length; j++) {
        // Check for backslash at the end of the line
        if (source_code[j] == '\\' && j < source_length - 1 && source_code[j + 1] == '\n') {
            // Skip the backslash and the newline character
            j += 1;
            continue;
        }

        // Copy characters to result
        result[result_length++] = source_code[j];
    }

    // Null-terminate the result
    result[result_length] = '\0';

    *size_source_code = result_length; // Update the size of the processed code
    return result;
}

