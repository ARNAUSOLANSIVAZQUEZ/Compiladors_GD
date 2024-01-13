#ifndef HEADER_HANDLE_INCLUDES
#define HEADER_HANDLE_INCLUDES


#include <stdio.h>

/*
Handles the include program files of the source code. source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_include_program_files() is now the owner (and responsible) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_include_program_files(char* source_code, size_t* size_source_code); 


/*
Handles the include compiler files of the source code. source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_include_compiler_files() is now the owner (and responsible) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_include_compiler_files(char* source_code, size_t* size_source_code); 


/*
Handles the handle ifdef endif of the source code. source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_ifdef_endif() is now the owner (and responsible) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_ifdef_endif(char* source_code);







#endif
