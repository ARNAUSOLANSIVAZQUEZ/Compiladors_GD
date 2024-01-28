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

char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_static);

#endif
