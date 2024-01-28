#ifndef UTILS
#define UTILS


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>
#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)

#define MAX_LENGTH_INCLUDE 100 //the max length of #incude<{HERE}>
#define MIN_ARGUMENTS 2 // Minimum arguments to properly execute the preprocessor

/*
    Returns the contents of the file located in directory. If an error happens, GetFileContents()
    will return NULL. size_sorce_code is an out value and may be anything; it will be overwritted
    to the size of the source code. 

    GetFileContents() will free the memory of directory automatically. debug_error_messages = true 
    prits error messages if the function fails. 
*/
char* GetFileContents(char* directory, size_t* size_source_code, bool debug_error_messages); 



/*
    Counts the number of thimes that the string element appears in the string source_str. 
    str_len and element_len are the length of source_str and element respectiely. 
    The strings must be valid strings. 

*/
int count_ocurrences(char* source_str, size_t str_len, char* element, int element_len); 



/*
    gets the new filename (adding the "_pp") and returns it. 
    ("my_program.c" -> "my_program_pp.c", "nasa_code.k" -> "nasa_code.k")
    if terminate_with_c == true, then the termination of the file will be ".c"
    (i.e. "my_program.ftw" -> "my_program.c"). Assumes old_name contains a '.' 
    (for the file type)

    get_new_filename() does not take ownership of old_name. Returns NULL on error
*/
char* get_new_filename(char* old_name, bool terminate_with_c); 

// Function to handle the input when executing the program
int processFlags(int argc, char** argv, bool* process_comments, bool* process_directives);

// Prints help for the user in the console
void PrintHelp();

#endif
