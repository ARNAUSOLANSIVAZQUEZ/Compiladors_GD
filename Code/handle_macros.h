#ifndef HEADER_HANDLE_MACROS
#define HEADER_HANDLE_MACROS


#include <stdio.h>


/*
The handle_macros function will handle the macros of the code. It will substitute the macros by their definition
and, eventually, remove the definitions. 

The source_code parameter is the code to be pre-processed (a string), and the size_source_code paraemter is the size
the source_code parameter.

The function returns an string and, size_source_code will end by being the size of this new string.
*/

char* handle_macros(char* source_code, size_t* size_source_code); 






#endif