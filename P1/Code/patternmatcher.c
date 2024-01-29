/*
* Compilers
* Practice 1: c pre-processor
* File name: patternmatcher.c
* Pattern Matcher structure file.
* Stores and recognizes different patterns to handle while reading the file.
*
* Responsible: Marcel Aranich, Arnau Solans
*/

#include "patternmatcher.h"

// Initialize empty pattern table
void pattern_matcher_initialize(PatternMatcher* pattern_matcher) {
    pattern_matcher->capacity = BASIC_CAPACITY;
    pattern_matcher->patterns = (Pattern**) calloc(BASIC_CAPACITY, sizeof(Pattern*));
    pattern_matcher->num_patterns = 0; //no str currently stored
}

// Check if current character fits any pattern and if it ends any pattern.
int pattern_scan(PatternMatcher* pattern_matcher, char c){
    Pattern* pattern;
    // Iterate over patterns
    for(int i = 0 ; i < pattern_matcher->num_patterns; i++) {
        pattern = pattern_matcher->patterns[i];
        // Character corresponds to pattern current position, thus advance position
        if(pattern->str_pattern[pattern->current_matches] == c) {
            pattern->current_matches++;
            // Pattern fully matched
            if(pattern->len <= pattern->current_matches) {
                pattern->current_matches = 0;
                return pattern->ID;
            }
        }
        // Character does not fit pattern
        else {
            pattern->current_matches = 0;
        }
    }
    // No pattern matched
    return 0;
}

// Add a pattern to the pattern table
void add_pattern(PatternMatcher* pattern_matcher, char* new_pattern, int id) {
    // Expand capacity if pattern table is full
    if(pattern_matcher->num_patterns == pattern_matcher->capacity) {
        int new_size = pattern_matcher->capacity * ARRAY_GROWTH_FACTOR;
        pattern_matcher->patterns = realloc(pattern_matcher->patterns, sizeof(Pattern*) * new_size);
        pattern_matcher->capacity = new_size;
    }
    // Create pattern
    Pattern* pattern = (Pattern*)malloc(sizeof(Pattern));
    pattern->str_pattern = new_pattern;
    pattern->ID = id;
    pattern->current_matches = 0;
    pattern->len = strlen(new_pattern);
    // Add pattern
    pattern_matcher->patterns[pattern_matcher->num_patterns] = pattern;
    pattern_matcher->num_patterns += 1;
}

// Add compiler directives known patterns
void add_static_patterns(PatternMatcher* pattern_matcher) {
    // Add #define pattern
    char* define_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(define_pattern, "#define ");
    add_pattern(pattern_matcher, define_pattern, DEFINE_ID);
    // Add #ifdef pattern
    char* ifdef_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(ifdef_pattern, "#ifdef");
    add_pattern(pattern_matcher, ifdef_pattern, IFDEF_ID);
    // Add // pattern
    char* comment_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(comment_pattern, "//");
    add_pattern(pattern_matcher, comment_pattern, COMMENT_ID);
    // Add /**/ pattern
    char* ML_comment_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(ML_comment_pattern, "/*");
    add_pattern(pattern_matcher, ML_comment_pattern, MULTI_COMMENT_ID);
    // Add #include "" pattern
    char* include_local_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(include_local_pattern, "#include \"");
    add_pattern(pattern_matcher, include_local_pattern, INCLUDE_LOC_ID);
    // Add #include <> pattern
    char* include_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(include_pattern, "#include <");
    add_pattern(pattern_matcher, include_pattern, INCLUDE_COMP_ID);
    // Add \ pattern
    char* backslash_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    strcpy(include_pattern, " \\ ");
    add_pattern(pattern_matcher, backslash_pattern, BACKSLASH_ID);

}

void print_pattern_matcher(PatternMatcher* pattern_matcher) {
    printf("Patern matcher: \t\t------------------------------------\n");
    printf("Number of patterns: %d\n\n", pattern_matcher->num_patterns);
    for(int i = 0; i < pattern_matcher->num_patterns; i++) {
        Pattern* curr_pat = pattern_matcher->patterns[i];
        printf("%d: \t|%s| \n\t\t >> ID: %d \t(%d chars, %d of them currently matched)\n\n", i, curr_pat->str_pattern, curr_pat->ID, curr_pat->len, curr_pat->current_matches);
    }
    printf("-----------------------------------------------------------------------\n\n");
}

void free_pattern_matcher(PatternMatcher* pattern_matcher) {
    for(int i = 0; i < pattern_matcher->num_patterns; i++) {
        free(pattern_matcher->patterns[i]->str_pattern); // free string inside
        free(pattern_matcher->patterns[i]);  //free structure itself
    }
    free(pattern_matcher->patterns);
}