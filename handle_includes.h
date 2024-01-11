#include <stdio.h>

/*
handles the include program files of the source code. source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_include_program_files() is now the owner (and responsable) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_include_program_files(char* source_code, size_t* size_source_code); 


/*
handles the include compiler files of the source code. source code is the string 
of the code to be pre-processed. And size_source_code is the length of source_code. 
handle_include_compiler_files() is now the owner (and responsable) of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_include_compiler_files(char* source_code, size_t* size_source_code); 