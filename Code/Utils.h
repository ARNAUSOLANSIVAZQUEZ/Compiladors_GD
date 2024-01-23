#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h> 

#define ARRAY_GROWTH_FACTOR 3/2 // 1.5 ~= phi = (1+sqrt(5))/2
// ^for mathematical reasons, this constant is better than 2

#define MAX_LENGTH_INCUDE 100 //the max length of #incude<{HERE}>


/*Structure that holds multiple strings in MultiString.string_arr. 
The length of MultiString.string_arr[x] is MultiString.string_len[x] 
and there are a total of MultiString.length elements. capacity is the 
number of strings that can actually be holded (dont change manually). 

char** string_arr; 
int* string_len; 
int length; 
int capacity
*/
typedef struct struct_MultiString {

    char** string_arr; 
    int* string_len; 
    int length; 
    int capacity; 

} MultiString; 

/*
ID: identifier for this pattern
str_pattern: the string to identify
len: length of the string
current_matches: number of patterns currenly matched (must be in [0, len - 1])
*/
typedef struct struct_pattern {

    int ID; // info extra
    char* str_pattern; //"#define "
    int len; 
    int current_matches; //

} Pattern; 

/*
patterns: the patterns itself (pointer to a list of pointers to the actual struct)
len_patterns: the number of patterns currenly hold
capacity: the maximum number of patterns tha could be holded
*/
typedef struct struct_patten_matcher {

    Pattern** patterns; 
    int num_patterns; 
    int capacity; 

} PatternMatcher; 


/*
Scans a single character with the given pattern matcher. 
returns 0 iff there is no match, otherwise returns the ID of the 
corresponding match. 
*/
int pattern_scan(PatternMatcher* pattern_matcher, char c); 


/*
    adds a string (new_pattern) as a pattern to the pattern matcher. 
    ID cannot be 0 and will be tha value returned by pattern_scan
    new_pattern must be heap allocated, and now pattern_matcher owns it 
    (has the responsability to deallocate it)
*/
void add_pattern(PatternMatcher* pattern_matcher, char* new_pattern, int id); 

/*
    frees the contents of the patter matcher structure. If pattern_matcher is heap-allocated, 
    must later call free on it. This function frees everything inside it. 
*/
void free_pattern_matcher(PatternMatcher* pattern_matcher); 



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
adds a new string to the multi_string structure
new_str is a heap allocated string. increases capacity of multistring if needed
new_str must end in /0 and be valid. ms must be initialized and well-behaved
*/
void add_string(MultiString* ms, char* new_str); 

/*
returns true/false iff element belongs to ms
ms must be initialized and well-behaved
*/
bool multistring_contains(MultiString* ms, char* element); 

/*
    frees the contents of the MultiString structure. If ms is heap-allocated, 
    must later call free on it. This function frees everything inside it. 
*/
void free_multi_string(MultiString* ms); 

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