#include "handle_comments.h"

// Helper function to find the index of the next newline character '\n'
size_t find_next_newline(char* str, size_t start) {
    size_t index = start;
    while (str[index] != '\0' && str[index] != '\n') {
        ++index;
    }
    return index;
}

char* handle_comments_simple(char* source_code, size_t* size_source_code) {
    size_t read_index = 0;
    size_t write_index = 0;

    while (source_code[read_index] != '\0') {
        if (source_code[read_index] == '/' && source_code[read_index + 1] == '/') {
            // Found the beginning of a single-line comment, skip until the next newline
            read_index = find_next_newline(source_code, read_index);
        } else {
            // Copy character to the new buffer
            source_code[write_index] = source_code[read_index];
            ++write_index;
        }

        ++read_index;
    }

    source_code[write_index] = '\0'; // Null-terminate the new string
    *size_source_code = write_index; // Update the new size

    return source_code;
}

char* handle_comments_multi(char* source_code, size_t* size_source_code) {
    size_t read_index = 0;
    size_t write_index = 0;

    while (source_code[read_index] != '\0') {
        if (source_code[read_index] == '/' && source_code[read_index + 1] == '*') {
            // Found the beginning of a multi-line comment, skip until the comment ends
            while (!(source_code[read_index] == '*' && source_code[read_index + 1] == '/')) {
                ++read_index;
            }
            read_index += 2; // Skip the closing '*/'
        } else {
            // Copy character to the new buffer
            source_code[write_index] = source_code[read_index];
            ++write_index;
        }

        ++read_index;
    }

    source_code[write_index] = '\0'; // Null-terminate the new string
    *size_source_code = write_index; // Update the new size

    return source_code;
}










