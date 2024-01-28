/*
* Compilers
* Practice 1: c pre-processor
* File name: patternmatcher.h
* Pattern Matcher structure file.
* Stores and recognizes different patterns to handle while reading the file.
*
* Responsible: Marcel Aranich, Arnau Solans
*/

#ifndef PATTERNMATCHER
#define PATTERNMATCHER

#include <stdio.h>
#include <stdbool.h>

#define BASIC_CAPACITY 5
#define NO_PATTERN_DETECTED 0
#define DEFINE_ID 1
#define IFDEF_ID 2
#define INCLUDE_COMP_ID 3
#define INCLUDE_LOC_ID 6 //unsorted
#define COMMENT_ID 4
#define MULTI_COMMENT_ID 5
#define BASIC_PATTERN_STR_LEN 20
#define ARRAY_GROWTH_FACTOR 3/2
// ^for mathematical reasons, the growth factor seems to be better if its lower that phi

/*
    ID: identifier for this pattern
    str_pattern: the string to identify
    len: length of the string
    current_matches: number of characters currently matched (must be in [0, len - 1])
*/
typedef struct struct_pattern {
    int ID; // info extra
    char* str_pattern; //"#define "
    int len;
    int current_matches; //
}Pattern;

/*
    patterns: the patterns themselves (pointer to a list of pointers to the actual struct)
    len_patterns: the number of patterns currently hold
    capacity: the maximum number of patterns tha could be held
*/
typedef struct struct_pattern_matcher {
    Pattern** patterns;
    int num_patterns;
    int capacity;
}PatternMatcher;

/*
    initializes the pattern matcher empty (length = 0) with capacity BASIC_CAPACITY.
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

// Adds compiler directives patterns to the pattern matcher
void add_static_patterns(PatternMatcher* pattern_matcher);

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

#endif
