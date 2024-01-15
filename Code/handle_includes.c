#include <stdlib.h>
/*
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>
*/
#include <dirent.h>
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

    ///strtok()
    return source_code; 
}

char* handle_include_compiler_files(char* source_code, size_t* size_source_code) { 
    // TODO: implement handle_include_compiler_files()
    return source_code; 
}



