/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_ifdef_endif.h
* Ifdef directive handler.
*
*
* Responsible: Ariadna Prat
*/
#ifndef HEADER_HANDLE_IFDEF_ENDIF
#define HEADER_HANDLE_IFDEF_ENDIF
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle_ifdef_endif.h"
#include "multistring.h"
#define ARRAY_GROWTH_FACTOR 3/2

/*
Handles the structure ifdef-endif in the code. handle_ifdef_endif() should return the text without structure ifdef_endif
which doesn't have the string #define boolean.

source code is the string of the code to be pre-processed. And size_source_code is the 
length of source_code. handle_macros() is now the owner (and responsible) of source_code. 

Returns a (possibly new) text and size_source_code is updated to the new size. 

*/
char *handle_ifdef_endif(char *source_code, int index, int *len, MultiString *ms);
void pre_handle_ifdef_endif(char* reading_buffer, int i, char* writing_buffer, char* writing_buffer_len, char* writing_index, MultiString* ms, bool process_comments, bool process_directives);
#endif
