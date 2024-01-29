/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_backslash.c
* Backslash directive handler.
*
*
* Responsible: Ariadna Prat
*/
#include "handle_backslash.h"
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
void pre_handle_backslash(char* reading_buffer, int i,  char* writing_buffer, int* writing_buffer_len, int* writing_index){
    int len = -1;
    char *if_def_text = handle_backslash (reading_buffer, &len,i);
    //^should return direcly what needs to be inserted in the writing buffer

    if(writing_buffer_len <= writing_index + len + 1 ) { // +1 for /0
        // get more space
        writing_buffer_len = (int)writing_buffer_len * ARRAY_GROWTH_FACTOR;
        writing_buffer = realloc(writing_buffer, writing_buffer_len);
    }
    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        *writing_buffer = realloc(*writing_buffer, *writing_buffer_len);
    }
    memcpy(&writing_buffer[*writing_index - 5], if_def_text, (size_t)len);
    writing_index += -5 + len - 1;
}

