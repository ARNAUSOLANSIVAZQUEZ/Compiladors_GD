/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_backslash.h
* Backslash directive handler.
*
*
* Responsible: Ariadna Prat
*/

#ifndef HEADER_HANDLE_BACKSLASH
#define HEADER_HANDLE_BACKSLASH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 256
#define ARRAY_GROWTH_FACTOR 3/2
/*
Handles the backslash in the code. handle_backslash() should return the an equivalent code
of source_code without using the "\ "


source code is the string of the code to be pre-processed. And size_source_code is the
length of source_code. handle_macros() is now the owner (and responsable) of source_code.

Returns a (possibly new) string and size_source_code is updated to the new size.

*/

char* handle_backslash(char* source_code, size_t* size_source_code, int i);
void pre_handle_backslash(char* reading_buffer, int i, char* writing_buffer, int* writing_buffer_len, int* writing_index);


#endif
