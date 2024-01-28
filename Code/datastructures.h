#ifndef HEADER_DATASTRUCTURES
#define HEADER_DATASTRUCTURES


#include <stdio.h>
#include <stdbool.h> 
#include "Utils.h"

#define BASIC_CAPACITY 5 
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


//      Pattern matcher: --------------------------------------------------------------------


/*
    prints a pattern (for debugging pruposes)
*/
void print_pattern(Pattern* pattern); 

/*
    initializes the pattern matcher empty (lenght = 0) with capacity BASIC_CAPACITY. 
*/
void pattern_matcher_initialize(PatternMatcher* pattern_matcher); 

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
    prints information of pattern matcher. (use for debugging proposes only)
    pattern_matcher must be initialized and valid. 
*/
void print_pattern_matcher(PatternMatcher* pattern_matcher); 

/*
    frees the contents of the patter matcher structure. If pattern_matcher is heap-allocated, 
    must later call free on it. This function frees everything inside it. 
*/
void free_pattern_matcher(PatternMatcher* pattern_matcher); 



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
