/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_defines.h
* Defines directive handler.
*
*
* Responsible: Claudia Quera
*/
#ifndef HANDLE_DEFINES_H
#define HANDLE_DEFINES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_ROWS 5

// Define a struct to hold define information
struct DefineInfo {
    int id;             // 8 for constants and 9 for macros
    char* identifier;
    char* content;
};

// Function prototypes
struct DefineInfo create_error_result();
struct DefineInfo* handle_define(char* source_code, int index, int* len);
struct DefineInfo defineResult(int id, char* source_code);
bool entryExists(struct DefineInfo* table, int num_rows, int id, const char* identifier);
void updateTable(struct DefineInfo* table, int num_rows, struct DefineInfo result);
void addToTable(struct DefineInfo* table, int num_rows, struct DefineInfo result);
void printTable(struct DefineInfo* table, int num_rows);

#endif  // HANDLE_DEFINES_H
