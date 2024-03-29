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

#include "patternmatcher.h"
#define TABLE_ROWS 5

// Define a struct to hold define information
struct DefineInfo {
    int id;             // 8 for constants and 9 for macros
    char* identifier;
    char* content;
};

// Function prototypes
struct DefineInfo create_error_result();
struct DefineInfo handle_define(char* reading_buffer);
struct DefineInfo defineResult(int id, char* source_code);
bool entryExists(struct DefineInfo* table, int num_rows, int id, const char* identifier);
void updateTable(struct DefineInfo* table, int num_rows, struct DefineInfo result, PatternMatcher* patternMatcher);
struct DefineInfo* addToTable(struct DefineInfo* table, int num_rows, struct DefineInfo result, PatternMatcher* patternMatcher);
void printTable(struct DefineInfo* table, int num_rows);
char* extractDefineLine(const char* buffer, size_t defineIndex);

#endif  // HANDLE_DEFINES_H
