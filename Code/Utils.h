#ifndef UTILS
#define UTILS

#include <stdio.h>




/*
Returns the contents of the file located in directory. If an error happens, GetFileContents()
will return NULL. size_sorce_code is an out value and may be anything; it will be overwritted
to the size of the source code. 

GetFileContents() will free the memory of directory automatically. debug_error_messages = true 
prits error messages if the function fails. 
*/
char* GetFileContents(char* directory, size_t* size_source_code, bool debug_error_messages); 




/*
Divides the source_str into multiple strings. The source string is divided where 
element appears. (element itself is removed). str_len is the length of source_str. 
Element is an string and element_len is it's lenght. 


Returns an array of strings wich result of spliting the source_str. 
out_str_len is an out parameter. The position that this points to will be set to an array of 
integers. The integers represent the length of each sub_string in source_str. The function caller 
is now the owner of the array. 
out_str_len_arr_len will be written the number of elements of source_str and out_str_len. 


*/
char** string_tonenizer(char* source_str, size_t str_len, size_t str_len, char* element, int element_len, int** out_str_len, int* out_str_len_arr_len); 



/*
Counts the number of thimes that the string element appears in the string source_str. 
str_len and element_len are the length of source_str and element respectiely. 
The strings must be valid strings. 

*/
int count_ocurrences(char* source_str, size_t str_len, char* element, int element_len); 





#endif