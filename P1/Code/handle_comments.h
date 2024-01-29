/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_comments.h
* Comment directive handler.
*
*
* Responsible: Jorge Villarino
*/
#ifndef HEADER_HANDLE_COMMENTS
#define HEADER_HANDLE_COMMENTS

#include <stddef.h>


char* handle_comments_simple(const char* source_code, size_t start_index, int* new_index);
char* handle_comments_multi(const char* source_code, size_t start_index, int* new_index);

#endif