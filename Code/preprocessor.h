/*
* Compilers
* Practice 1: c pre-processor
* File name: preprocessor.h
* Recursive preprocessing function.
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/

#ifndef PREPROCESSOR
#define PREPROCESSOR
#include "patternmatcher.h"
#include "main.h"
#define INCLUDE_FILE_PATTERN_DETECTION_LEN 9
#define TABLE_ROWS 5
#define ARRAY_GROWTH_FACTOR 3/2
// Recursive implementation of preprocessing function
char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_static);

/*
    writes the content buffer in a new file (with filename as name).
    If the file already exists, it will be overwritten with the new file.
    content_buffer is the contents of the new file. len is the length of the
    content buffer. write_new_file() does NOT take ownership of any parameter.

    returns 0 on succes, otherwise returns any other number
*/
int write_new_file(char* content_buffer, size_t len, char* filename);

#endif
