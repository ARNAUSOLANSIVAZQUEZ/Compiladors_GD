#include <stdio.h>


/*
Handles the constants in the code. It must substitute every constant in the code 
by it's corresponding value and remove the definition. 

source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_include_program_files() is now the owner (and responsable) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/

char* handle_constants(char* source_code, size_t* size_source_code); 


