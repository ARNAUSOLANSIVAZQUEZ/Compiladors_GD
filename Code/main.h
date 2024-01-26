#ifndef HEADER_MAIN
#define HEADER_MAIN

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>

#include "handle_backslash.h"
#include "handle_comments.h"
#include "handle_constants.h"
#include "handle_includes.h"
#include "handle_macros.h"
#include "handle_ifdef_endif.h"

#include "Utils.h"
#include "datastructures.h"

#define INCLUDE_FILE_PATTERN_DETECTION_LEN 9


// This header exists because we need to call preprocess recursively from handle_include


/*
preprocesses the given reading_buffer and returns a new str with the preprocessed file. 
pattern_match_base is the pattern matcher with the base cases
_len points to the original size og reading buffer and will be overwritten to the final 
size of the output
*/
char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_base); 

/*Prints help for the user in the console*/
void PrintHelp(); 

// int main(...); 

/*
    does everything needed to call handle_include_file() and handles its outputs
*/
void pre_handle_compile_file(char* reading_buffer, char* writing_buffer, size_t* writting_buffer_len, int* writing_index); 

//void pre_handle_include_file(char* reading_buffer, char* writing_buffer, size_t* writting_buffer_len, int* writing_index); 
void pre_handle_include_file(char* reading_buffer, int* reading_buffer_index, char* writing_buffer, size_t* writting_buffer_len, int* writing_index, PatternMatcher* pattern_match_base); 



/*
    writes the content buffer in a new file (with filename as name). 
    If the file already exists, it will be overwritten with the new file. 
    content_buffer is the contents of the new file. len is the length of the 
    content buffer. write_new_file() does NOT take ownership of any parameter. 

    returns 0 on succes, otherwise returns any other number
*/
int write_new_file(char* content_buffer, size_t len, char* filename); 


#endif