#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>


#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)



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



char** string_tonenizer(char* source_str, size_t str_len, int* out_str_len, int* str_len_arr_len) {

    out_str_len = NULL; 
    str_len_arr_len = calloc(1, sizeof(int)); 

    //Uncoplete
    return NULL; 
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
        }


    }


    return ret; 

}









