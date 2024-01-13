#ifndef HEADER_HANDLE_CONSTANTS
#define HEADER_HANDLE_CONSTANTS


#include <stdio.h>


/*
The handle_constants function handles the constants in the code. It will substitute all the constants by their 
corresponding value. It will also remove the definition of all the constants.

The source_code parameter is the string of the code to be processed, and changed. Size_source_code is the size 
of the source_code parameter. 

The function returns the updated source_code and the size_source_code will be updated to the size of this returned
new code. 
*/

char* handle_constants(char* source_code, size_t* size_source_code); 



#endif