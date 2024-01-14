#ifndef HEADER_HANDLE_INCLUDES
#define HEADER_HANDLE_INCLUDES


#include <stdio.h>
#include <dirent.h>

/*
 Allows to open and search directories searching for a file.
 directory_path is a string input that represents the path to the directory in 
 which the function will search for entries and subdirectories.

 Returns the path to desired file.
 */
void fetch_directory(char* directory_path);


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




#endif
