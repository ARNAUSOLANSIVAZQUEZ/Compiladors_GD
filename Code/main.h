#ifndef HEADER_MAIN
#define HEADER_MAIN

#include <stdio.h>


// This header exists because we need to call preprocess recursively from handle_include


/*
preprocesses the given reading_buffer and returns a new str with the preprocessed file. 
includes is a multistring (see utils.h) that contains all the currenly added includes. 
_len points to the original size og reading buffer and will be overwritten to the final 
size of the output
*/
char* preprocess(char* reading_buffer, size_t* _len, MultiString* includes); 

/*Prints help for the user in the console*/
void PrintHelp(); 

// int main(...); 

/*
    does everything needed to call handle_include_file() and handles its outputs
*/
void pre_handle_include_file(char* reading_buffer, char* writing_buffer, size_t* writting_buffer_len, int* writing_index); 



#endif