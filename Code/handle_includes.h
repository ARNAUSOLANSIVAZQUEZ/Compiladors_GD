/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_includes.h
* Include directive handler.
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/
#ifndef HEADER_HANDLE_INCLUDES
#define HEADER_HANDLE_INCLUDES

#include <stddef.h>
#include <stdbool.h>
#include "patternmatcher.h"
#include "utils.h"
#include "preprocessor.h"
#define INCLUDE_FILE_PATTERN_DETECTION_LEN 9
#define MAX_LENGTH_INCLUDE 100 //the max length of #incude<{HERE}>


/*
    Returns the preprocessed code that the "#includes " includes. The includes is in the 
    source_code at the  index (source_code[index] should be '#'). If the included
    file was already added, it should be stored in the MultiString includes and will be omited. 
    base_directory is the directory of the original file (argv[0]). 

    the new include will be automatically added to includes. The calee holds ownership of 
    source_code, includes, base_directory and the return value. The returned string is already 
    preprocessed. 

    If there is an error, NULL will be returned instead. 
*/
//char* handle_include_program_files(char* source_code, size_t* size_source_code); 
//char* handle_include_program_files(char* source_code, int index, MultiString* includes, char* base_directory) {
char* handle_include_program_files(char* reading_buffer, PatternMatcher* pattern_match_static, MultiString* ifdef_ms, bool process_comments, bool process_directives);


/*
    Handles the include compiler files of the source code. source code is the string 
    of the code to be pre-processed. And size_source_code is the length of source_code. 
    handle_include_compiler_files() is now the owner (and responsible) of source_code. 

    Returns a (possibly new) string and size_source_code is updated to the new size. 

*/
char* handle_include_compiler_files(char* reading_buffer, PatternMatcher* pattern_match_static, MultiString* ifdef_ms, bool process_comments, bool process_directives);

/*
    does everything needed to call handle_include_file() and handles its outputs
*/
void pre_handle_compile_file(char* reading_buffer, int* reading_buffer_index, char** writing_buffer, size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_static, MultiString* ifdef_ms, bool process_comments, bool process_directives);

void pre_handle_include_file(char* reading_buffer, int* reading_buffer_index, char** writing_buffer, size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_static, MultiString* ifdef_ms, bool process_comments, bool process_directives);



#endif
