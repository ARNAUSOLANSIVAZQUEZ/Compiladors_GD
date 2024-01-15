#include <stdlib.h>
#include <string.h>
#include <memory.h>
/*
#include <stdio.h>
#include <stdbool.h> 

*/
#include <dirent.h> // <- this gives me an error
#include "Utils.h" 

void fetch_directory(char* directory_path) {
    //Skeleton for opening subdirectories and entries
    //TODO: make the function able to detect the correct file and retrieve it's path
    // Open directory from path input
    DIR* d = opendir(directory_path);
    // Return error if unable to open specified path
    if(d == NULL) {
        return;
    }
    // Initialize directory entries from reading the directory opened
    struct dirent* dir;
    dir = readdir(d);
    // While we can read something keep processing the entries
    while(dir != NULL)
    {
        // Initialize entry name
        char* entry;
        entry = dir -> d_name;
        // If the entry is not a directory
        if(dir -> d_type != DT_DIR)
        {
            //printf(entry);
        }
        else
        {
            char new_path[256];
            sprintf(new_path, "%s/%s", directory_path, entry);
            fetch_directory(new_path);
        }
        printf("%s", entry);
    }
    closedir(d);
}

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

char* handle_include_compiler_files(char* source_code, size_t* size_source_code) { 
    // TODO: implement handle_include_compiler_files()
    return source_code; 
}




