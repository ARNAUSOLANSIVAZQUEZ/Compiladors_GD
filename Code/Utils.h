#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h> 

#define ARRAY_GROWTH_FACTOR 3/2 
// 1.5 ~= phi = (1+sqrt(5))/2
// ^for mathematical reasons, the growth factor seems to be better if its lower that phi
// 1.5 is a "simple" value that is less than phi, thats why its choosen

#define MAX_LENGTH_INCUDE 100 //the max length of #incude<{HERE}>



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

    get_new_filename() does not take ownership of old_name. Reutrns NULL on error
*/
char* get_new_filename(char* old_name, bool terminate_with_c); 



#endif