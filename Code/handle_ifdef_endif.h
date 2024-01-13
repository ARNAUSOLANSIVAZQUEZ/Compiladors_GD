#ifndef HEADER_HANDLE_BACKSLASH
#define HEADER_HANDLE_BACKSLASH

#include <stdio.h>


/*
Handles the backslash in the code. handle_backslash() should return the an equivalent code 
of source_code without using the "\ "


source code is the string of the code to be pre-processed. And size_source_code is the 
length of source_code. handle_macros() is now the owner (and responsable) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/

char* handle_define(char* source_code);
char* handle_ifdef_endif(char* source_code);

#endif