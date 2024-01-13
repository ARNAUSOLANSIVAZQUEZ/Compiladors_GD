#ifndef HEADER_HANDLE_MACROS
#define HEADER_HANDLE_MACROS


#include <stdio.h>


/*
Handles the macros. Substitutes the macro by the definition and then removes the definition. 

source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_macros() is now the owner (and responsable) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/

char* handle_macros(char* source_code, size_t* size_source_code); 






#endif