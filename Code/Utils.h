#ifndef UTILS
#define UTILS

#include <stdio.h>

#define ARRAY_GROWTH_FACTOR 3/2 // 1.5 ~= phi = (1+sqrt(5))/2
// ^for mathematical reasons, this constant is better than 2

#define MAX_LENGTH_INCUDE 100 //the max length of #incude<{HERE}>


/*Structure that holds multiple strings in MultiString.string_arr. 
The length of MultiString.string_arr[x] is MultiString.string_len[x] 
and there are a total of MultiString.length elements. 

char** string_arr; 
int* string_len; 
int length; 
*/
typedef struct struct_MultiString {

    char** string_arr; 
    int* string_len; 
    int length; 

} MultiString; 




/*
Returns the contents of the file located in directory. If an error happens, GetFileContents()
will return NULL. size_sorce_code is an out value and may be anything; it will be overwritted
to the size of the source code. 

GetFileContents() will free the memory of directory automatically. debug_error_messages = true 
prits error messages if the function fails. 
*/
char* GetFileContents(char* directory, size_t* size_source_code, bool debug_error_messages); 


/*
Prints the MultiString structure. Used only for debugging. 
*/
void print_multistring(MultiString* ms); 


/*
Divides the source_str into multiple strings. The source string is divided where 
element appears. (element itself is removed). str_len is the length of source_str. 
Element is an string and element_len is it's lenght. 


Returns the MultiString struct (for more info, check it's definition). 

*/
MultiString* string_tonenizer(char* source_str, size_t str_len, char* element, int element_len); 



/*
Counts the number of thimes that the string element appears in the string source_str. 
str_len and element_len are the length of source_str and element respectiely. 
The strings must be valid strings. 

*/
int count_ocurrences(char* source_str, size_t str_len, char* element, int element_len); 





#endif