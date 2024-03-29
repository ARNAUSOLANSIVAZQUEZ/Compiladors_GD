/*
* Compilers
* Practice 1: c pre-processor
* File name: multistring.c
* Multistring structure functions.
*
*
* Responsible: Marcel Aranich
*/
#include "multistring.h"


//      MultiString: ----------------------------------------------------------------


void multistring_initialize(MultiString* multi_string){
    multi_string->capacity = BASIC_CAPACITY; 
    multi_string->string_arr = (char**)calloc(BASIC_CAPACITY, sizeof(char*)); 
    multi_string->string_len = (int*)calloc(BASIC_CAPACITY, sizeof(int)); 
    multi_string->length = 0; //no str currenly stored
}

void add_string(MultiString* ms, char* new_str) {

    if(ms->length == ms->capacity){
        //no space for new str
        ms->capacity = ms->capacity * ARRAY_GROWTH_FACTOR; 
        ms->string_arr = (char**)realloc(ms->string_arr, ms->capacity * sizeof(char*)); 
        ms->string_len = (int*)realloc(ms->string_len, ms->capacity * sizeof(int)); 

    }

    ms->string_arr[ms->length] = new_str; 
    ms->string_len[ms->length] = strlen(new_str); 
    ms->length += 1; 


}

bool multistring_contains(MultiString* ms, char* element) {

    int ms_len = ms->length; 

    for(int i = 0; i < ms_len; i++){
        if(strcmp(ms->string_arr[i], element) == 0){
            return true; 
        }
    }
    
    return false; 

}

MultiString* string_tonenizer(char* source_str, size_t str_len, char* element, int element_len) {

    
    int num_elements = count_ocurrences(source_str, str_len, element, element_len); 
    
    MultiString* ret = (MultiString*)malloc(sizeof(MultiString)); 

    ret->length = num_elements + 1; //initialize structure
    ret->capacity = ret->length; 
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
                    /*
                    int mem_ret = memcpy_s(current_str, (current_array_len + 1) * sizeof(char), &source_str[index_start], current_array_len);
                    if(mem_ret != 0) {
                        printf("memcpy_s error\n"); 
                    }
                    */
                    memcpy(current_str, &source_str[index_start], current_array_len);
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

            /*
            int mem_ret = memcpy_s(current_str, (current_array_len + 1) * sizeof(char), &source_str[index_start], current_array_len); 
            if(mem_ret != 0) {
                printf("memcpy_s error\n"); 
            }
            */
            memcpy(current_str, &source_str[index_start], current_array_len);
            current_str[current_array_len] = '\0'; 

            ret->string_arr[i] = current_str; 
            ret->string_len[i] = current_array_len; 

        }
    }
    
    //Uncoplete
    return ret; 
}

void print_multistring(MultiString* ms){

    //for debugging pruposes
    printf("\n\nMultiString: \n\n\t\t%d elements: \n\n", ms->length); 

    for(int i = 0; i < ms->length; i++) {

        printf("\t%d (%d = %ld chars): |%s|", i, ms->string_len[i], strlen(ms->string_arr[i]), ms->string_arr[i]);
        printf("\n\n"); 
    } 


}

void free_multi_string(MultiString* ms) {

    for(int i = 0; i < ms->length; i++){
        free(ms->string_arr[i]); 
    }
    free(ms->string_arr); 
    free(ms->string_len); 

}
