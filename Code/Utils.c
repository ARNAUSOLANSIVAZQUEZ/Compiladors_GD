#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>

#include "Utils.h"

#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)

#define ARRAY_GROWTH_FACTOR 3/2 // 1.5 ~= phi = (1+sqrt(5))/2
// ^for mathematical reasons, this constant is better than 2
// ^also currenly unused, found a better way to do the thing :P

#define MAX_LENGTH_INCUDE 100 //the max length of #incude<{HERE}>


char* GetFileContents(char* directory, size_t* size_source_code, bool debug_error_messages) {

    *size_source_code = -1; //no undefined behaviour >:(
    FILE* source_file = fopen(directory, "rb"); // r because we cannot modify original file

    if(source_file == NULL) {
        if(debug_error_messages) printf("ERROR: Could not open file in directory: %s", directory); 
        return NULL; 
    }

    free(directory); 

    { // find size of file
        int fseek_return = fseek(source_file, 0L, SEEK_END); 
        if(fseek_return != 0) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return NULL; 
        }

        long int ftell_return = ftell(source_file); 

        if(ftell_return == -1L) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. ftell return: %d", ftell_return); 
            fclose(source_file); 
            return NULL; 
        }

        *size_source_code = (size_t)ftell_return; 
        fseek_return = fseek(source_file, 0L, SEEK_SET); 

        if(fseek_return != 0) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return NULL; 
        }
    }

    char* file_contents = (char*)calloc(*size_source_code, 1); 


    if(file_contents == NULL) { // error requesting memory
        if(debug_error_messages) printf("ERROR: error while requesting memory. \nMemory asked: %d Bytes\t = %d MB", size_source_code, (int) *size_source_code * BYTES_TO_MB_CONVERSION_FACTOR); 
        fclose(source_file); 
        return NULL; 
    }

    { // copy contents
        size_t fread_return = fread(file_contents, 1, *size_source_code, source_file); 

        if(fread_return != *size_source_code && feof(source_file) == 0) { // handle error
            if(debug_error_messages) {
                printf("ERROR: error while reading file. fread return: %d\tfile length: %d bytes\n", fread_return, size_source_code); 
                printf("feof(file) = %d\n", feof(source_file)); 
            }

            fclose(source_file); 
            return NULL; 
        }
    }

    fclose(source_file); 

    return file_contents; 


}



void print_multistring(MultiString* ms){

    //for debugging pruposes
    printf("\n\nMultiString: \n\n\t\t%d elements: \n\n", ms->length); 

    for(int i = 0; i < ms->length; i++) {

        printf("\t%d (%d = %d chars): |%s|", i, ms->string_len[i], strlen(ms->string_arr[i]), ms->string_arr[i]); 
        printf("\n\n"); 
    } 


}


MultiString* string_tonenizer(char* source_str, size_t str_len, char* element, int element_len) {

    
    int num_elements = count_ocurrences(source_str, str_len, element, element_len); 
    
    MultiString* ret = (MultiString*)malloc(sizeof(MultiString)); 

    ret->length = num_elements + 1; //initialize structure
    ret->string_arr = (char**)malloc(ret->length * sizeof(char*)); 
    ret->string_len = (int*)calloc(ret->length, sizeof(int)); 
    
    int curr_char = 0; 

    //int batch_size = 256; 
    //int current_string_capacity = batch_size; 
    char* current_str = NULL; // auxiliar variable to simplify code and reduce redirection

    int element_count = 0; 
    int current_array_len = 0; 
    int index_start = 0; 

    for(int i = 0; i < num_elements + 1; i++) {


        element_count = 0; 
        current_array_len = 0; 

        while(curr_char < str_len) { 
            
            //current_str[curr_char] = source_str[curr_char]; 
            current_array_len += 1; 


            if(source_str[curr_char] == element[element_count]) {

                element_count++; 

                if(element_count == element_len) { 

                    //current_str[curr_char - element_len + 1] = '\0'; 
                    current_array_len = curr_char - index_start + 1; 
                    current_array_len += -element_len; 
                    current_str = (char*)malloc((current_array_len + 1) * sizeof(char)); 

                    // printf("EQUALITY: %d (%d, %d)\n", curr_char - index_start + 1 == current_array_len + element_len, curr_char - index_start + 1, current_array_len + element_len); 

                    int mem_ret = memcpy_s(current_str, (current_array_len + 1) * sizeof(char), &source_str[index_start], current_array_len); 
                    if(mem_ret != 0) {
                        printf("memcpy_s error\n"); 
                    }
                    
                    current_str[current_array_len] = '\0'; 
                    index_start = curr_char; 
                    curr_char++; 

                    ret->string_arr[i] = current_str; 
                    ret->string_len[i] = current_array_len; 

                    index_start = curr_char; 

                    break; 

                }

            } else {
                element_count = 0; 
            }

            curr_char++; 

        }

        if(source_str[curr_char + 1] == '\0') {
            //handle last bit of data (it didn't have the delimiter at the end)

            current_array_len = curr_char - index_start + 1; 

            current_str = (char*)malloc((current_array_len + 1) * sizeof(char)); 


            int mem_ret = memcpy_s(current_str, (current_array_len + 1) * sizeof(char), &source_str[index_start], current_array_len); 
            if(mem_ret != 0) {
                printf("memcpy_s error\n"); 
            }
            
            current_str[current_array_len] = '\0'; 

            ret->string_arr[i] = current_str; 
            ret->string_len[i] = current_array_len; 

        }
    }
    
    //Uncoplete
    return ret; 
}

int count_ocurrences(char* source_str, size_t str_len, char* element, int element_len) {

    int ret = 0; 
    int current_word_count = 0; 

    for(int i = 0; i < str_len; i++){

        if(source_str[i] == element[current_word_count]) {
            current_word_count++; 

            if(element_len <= current_word_count) {
                current_word_count = 0; 
                ret++; 
            }
        } else current_word_count = 0; 


    }


    return ret; 

}





