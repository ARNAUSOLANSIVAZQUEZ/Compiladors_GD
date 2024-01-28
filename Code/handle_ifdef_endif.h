#ifndef HEADER_HANDLE_IFDEF_ENDIF
#define HEADER_HANDLE_IFDEF_ENDIF

#include <stdio.h>
/*
Handles the structure ifdef-endif in the code. handle_ifdef_endif() should return the text without structure ifdef_endif
which doesn't have the string #define boolean.

source code is the string of the code to be pre-processed. And size_source_code is the 
length of source_code. handle_macros() is now the owner (and responsible) of source_code. 

Returns a (possibly new) text and size_source_code is updated to the new size. 

*/
char* handle_ifdef_endif(char *source_code, int index, int *len);
char* delete_small_comment(char* texto);
char* delete_big_comment(const char *cadena);

#endif
