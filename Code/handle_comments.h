#ifndef HEADER_HANDLE_COMMENTS
#define HEADER_HANDLE_COMMENTS

#include <stddef.h>

//Jorge Villarino Moruja, 231351

char* handle_comments_simple(const char* source_code, size_t start_index, int* new_index);
char* handle_comments_multi(const char* source_code, size_t start_index, int* new_index);

#endif