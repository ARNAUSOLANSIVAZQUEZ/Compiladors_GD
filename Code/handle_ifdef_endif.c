#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Ariadna Prat U185150, NIA:251281

#define MAX_LINE_LENGTH 256
char* handle_ifdef_endif(char* source_code, int index, int* len) {
    // Find the start of the #ifdef block
    char* ifdef_start = strstr(source_code, "#ifdef");
    if (!ifdef_start) {
        *len = 0;
        return NULL;  // No #ifdef found
    }

    // Find the end of the #ifdef line
    char* ifdef_line_end = strchr(ifdef_start, '\n');
    if (!ifdef_line_end) {
        *len = 0;
        return NULL;  // Malformed #ifdef
    }

    // Find the start of the #define block
    char* define_start = strstr(source_code, "#define");
    if (!define_start || define_start > ifdef_start) {
        *len = 0;
        return NULL;  // No #define found or inside #ifdef-#endif
    }

    // Find the end of the #define line
    char* define_line_end = strchr(define_start, '\n');
    if (!define_line_end) {
        *len = 0;
        return NULL;  // Malformed #define
    }

    char ifdef_str[MAX_LINE_LENGTH];
    sscanf(ifdef_start, "#ifdef %s", ifdef_str);

    while (1) {
        // Extract the strings after #ifdef and #define
        char define_str[MAX_LINE_LENGTH];
        sscanf(define_start, "#define %s", define_str);

        // Compare the strings, if they match, process the block
        if (strcmp(ifdef_str, define_str) == 0) {
            // Find the #endif
            char* endif_start = strstr(define_line_end, "#endif");
            if (!endif_start) {
                *len = 0;
                return NULL;  // Malformed #endif
            }

            // Calculate the length of the processed block
            *len = (int)(endif_start - ifdef_start) + strlen("#endif");

            // Allocate memory for the processed block
            char* result = (char*)malloc(*len + 1);  // +1 for null terminator
            if (!result) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            // Copy the processed block to the result string
            strncpy(result, ifdef_start, *len);
            result[*len] = '\0';  // Null-terminate the result string

            return result;
        }

        // Find the start of the next #define block
        define_start = strstr(define_line_end, "#define");
        if (!define_start || define_start > ifdef_start) {
            *len = 0;
            return NULL;  // No more #define found or inside #ifdef-#endif
        }

        // Find the end of the #define line
        define_line_end = strchr(define_start, '\n');
        if (!define_line_end) {
            *len = 0;
            return NULL;  // Malformed #define
        }
    }
}
