#include <stdlib.h>
#include <string.h>
#include <memory.h>
/*
#include <stdio.h>
#include <stdbool.h> 

*/
#include "Utils.h" 

#if defined(__WIN32__)
    #define SYSTEM_PATH ""
#elif __linux__
    #define SYSTEM_PATH "x86_64-linux-gnu/"
#endif
#if (__STDC_VERSION__ == 201112L)
    #define COMPILER_VERSION "11/"
#elif (__STDC_VERSION__ == 199901L)
    #define COMPILER_VERSION "99/"
#elif (__STDC_VERSION__ == 199409L)
    #define COMPILER_VERSION "90/"
    #define COMPILER_VERSION_2 "89/"
#endif
#define PATH1 "/usr/include/"
#define PATH2 "/lib/gcc/include/"


char* handle_include_program_files(char* source_code, size_t* size_source_code) {
    // TODO: implement handle_include_program_files()

    char delimiter[11] = "#include \""; 
    MultiString* Mstr = string_tonenizer(source_str, str_len, delimiter, strlen(delimiter)); 

    // Pseudocode explanation

    size_t reserved_len = size_source_code; 

    char* ret = (char*)malloc(size_source_code * sizeof(char)); 

    strcpy(ret, Mstr->string_arr[0]); 

    for(int i = 1; i < Mstr->length; i++){

        char include_str[MAX_LENGTH_INCUDE] = NULL; 

        sscanf("%s\"", Mstr->string_arr[i], include_str); 

        // Get the contents of the file of include_str
        char* include_source_code = NULL; 
        
        // ret = ret + include_source_code

        //also realloc() and keep count of the size when necessary

    }

    // TODO: free       free       free       free       free       free       free       

    return ret; 
}

char* handle_include_compiler_files(char* source_code, int index, int* substitution_length) {
    // TODO: implement handle_include_compiler_files()
    char* id = "#include <";
    int id_length = strlen(id);
    char* target_file;
    char* current_char;
    int start_index = index + id_length;
    int current_index = start_index;
    int filename_found = 0;
    while(!filename_found){
        current_char = &source_code[current_index];
        if(strcmp(current_char, ">")){
            filename_found = 1;
        }
        else{
            current_index++;
        }
    }
    strncpy(target_file, source_code + start_index, current_index - start_index);
    char path1[100] = PATH1;
    strcat(path1, target_file);
    char path2[100] = PATH2;
    strcat(path2, SYSTEM_PATH);
    strcat(path2, "11/");
    strcat(path2, "include/");
    strcat(path2, target_file);
    printf(path1);
    printf(path2);
    //char** possible_paths = ["/usr/local/include" , "lib/gcc/%s", "", ""];
    return source_code; 
}




