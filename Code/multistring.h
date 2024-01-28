#ifndef HEADER_DATASTRUCTURES
#define HEADER_DATASTRUCTURES


#include <stdio.h>
#include <stdbool.h> 
#include "utils.h"

#define BASIC_CAPACITY 5
#define ARRAY_GROWTH_FACTOR 3/2
// basic capacity for vector<T>-like structures


/*
    Structure that holds multiple strings in MultiString.string_arr. 
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


//      MultiString: ----------------------------------------------------------------


/*
    initializes the pattern matcher empty (lenght = 0) with capacity BASIC_CAPACITY. 
*/
void multistring_initialize(MultiString* multi_string); 

/*
    tiString structure. Used only for debugging. 
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
    Divides the source_str into multiple strings. The source string is divided where 
    element appears. (element itself is removed). str_len is the length of source_str. 
    Element is an string and element_len is it's lenght. 


    Returns the MultiString struct (for more info, check it's definition). 

*/
MultiString* string_tonenizer(char* source_str, size_t str_len, char* element, int element_len); 

/*
    frees the contents of the MultiString structure. If ms is heap-allocated, 
    must later call free on it. This function frees everything inside it. 
*/
void free_multi_string(MultiString* ms); 










#endif
