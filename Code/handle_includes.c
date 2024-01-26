
#include "handle_includes.h" 


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


//char* handle_include_program_files(char* source_code, int index, MultiString* includes, char* base_directory) {
char* handle_include_program_files(char* reading_buffer, PatternMatcher* pattern_match_base) {
    
    //char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_base
    // TODO: implement handle_include_program_files()


    char include_dir[MAX_LENGTH_INCUDE] = ""; 

    sscanf("%s\"", reading_buffer, include_str); 


    // get file contents, preprocess (, free) and return 

    size_t size_include = -1; 

    char* raw_include = GetFileContents(include_dir, &size_include, false); 
    if(raw_include == NULL) return NULL; 

    char* ret = preprocess(raw_include, &size_include, pattern_match_base); 

    // TODO: free       free       free       free       free       free       free       

    free(raw_include); 

    /* We do not have ownership over reading_buffer, _len, pattern_match_base; therefore we must 
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




