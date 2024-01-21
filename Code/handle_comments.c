#include "handle_comments.h"
#include <stdlib.h>
#include <string.h>

char* handle_comments_simple(const char* source_code, size_t start_index, int* new_index) {
    size_t source_length = strlen(source_code);
    size_t i = start_index;
    char* result = NULL;
    int result_index = 0;

    while (i < source_length && source_code[i] != '\n') {
        i++;
    }

    *new_index = i + 1;  // Set the new index after the end of the single-line comment

    // Allocate memory for the result string
    result = (char*)malloc((i - start_index + 1) * sizeof(char));

    // Copy characters from the source excluding the single-line comment
    for (size_t j = start_index; j <= i; j++) {
        result[result_index++] = source_code[j];
    }

    result[result_index] = '\0';  // Null-terminate the result string
    return result;
}

char* handle_comments_multi(const char* source_code, size_t start_index, int* new_index) {
    size_t source_length = strlen(source_code);
    size_t i = start_index + 2;  // Move past the initial "/*"
    char* result = NULL;
    int result_index = 0;

    while (i < source_length && !(source_code[i] == '*' && source_code[i + 1] == '/')) {
        i++;
    }

    i += 2;  // Move past the closing "*/"
    *new_index = i;

    // Allocate memory for the result string
    result = (char*)malloc((i - start_index - 1) * sizeof(char));

    // Copy characters from the source excluding the multi-line comment
    for (size_t j = start_index; j < i; j++) {
        result[result_index++] = source_code[j];
    }

    result[result_index] = '\0';  // Null-terminate the result string
    return result;
}
