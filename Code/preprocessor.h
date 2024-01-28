/*
* Compilers
* Practice 1: c pre-processor
* File name: preprocessor.h
* Recursive preprocessing function.
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stddef.h>
#include <stdio.h>

#include "patternmatcher.h"
#include "utils.h"
#include "handle_ifdef_endif.h"
#include "handle_includes.h"
#include "handle_comments.h"

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
