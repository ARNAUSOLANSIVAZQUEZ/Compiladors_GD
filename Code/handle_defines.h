#ifndef HANDLE_DEFINES_H
#define HANDLE_DEFINES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a struct to hold define information
struct DefineInfo {
    int id;             // 8 for constants and 9 for macros
    char* identifier;
    char* content;
};

// Function to create an error result for DefineInfo structures
struct DefineInfo create_error_result();

// Function to handle #define lines and return a DefineInfo structure
struct DefineInfo* handle_define(char* source_code, int index, int* len);

// Function to handle the result of a #define line and return a DefineInfo structure
struct DefineInfo defineResult(int id, char* source_code);

#endif  // HANDLE_DEFINES_H