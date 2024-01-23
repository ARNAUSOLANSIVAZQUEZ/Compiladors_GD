#include <stdlib.h>
#include <string.h>
#include <memory.h>
/*
#include <stdio.h>
#include <stdbool.h> 

*/
#include "Utils.h" 
#include "main.h"

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


char* handle_include_program_files(char* source_code, int index, MultiString* includes, char* base_directory) {
    // TODO: implement handle_include_program_files()


    char include_str[MAX_LENGTH_INCUDE] = NULL; 

    sscanf("#include \"%s\"", &source_code[index], include_str); 

    if(multistring_contains(includes, include_str)) {
        return NULL; //already added, add nothing to the file
    }

    // add new include to ms 
    char new_include_str = (char*)malloc(strlen(include_str) * sizeof(char)); 
    strcpy(new_include_str, include_str); 
    add_string(includes, new_include_str); 

    // get of header
    int base_dir_len = strlen(base_directory); 
    char* directory = malloc((base_dir_len + strlen(include_str)) * sizeof(char)); 
    if(directory == NULL) return NULL; 

    strcpy(directory, base_directory); 

    {
        // asume base directory has the form "[...]/somefolder/mymain.c"
        //we need to delete everything after the second to last dot and append include_str
        bool seen_delimiter = false; 
        int i = base_dir_len - 1; 
        char delimiter = '/'; 
        while(0 <= i) { // cond should always be true

            if(directory[i] == delimiter) {
                if(seen_delimiter) {
                    break; 
                }
                seen_delimiter = true; 
            }
            directory[i] = '\0'; 
            i += -1; 
        }

    }

    strcat(directory, new_include_str); 
    // directory should now be complete


    // get file contents, preprocess (, free) and return 

    size_t size_include = -1; 

    char* raw_include = GetFileContents(directory, &size_include, false); 

    char* ret = preprocess(raw_include, &size_include, includes); 


    // TODO: free       free       free       free       free       free       free       

    free(directory); 
    //NOT free new_include_str
    free(raw_include); 

    /* We do not have ownership over source_code, includes, base_directory; therefore we must 
    NOT free them. */

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




