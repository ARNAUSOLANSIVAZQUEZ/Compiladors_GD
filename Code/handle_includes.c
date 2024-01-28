
#include "handle_includes.h" 

#ifdef __MINGW64__
    #define MINGW 1
    #define LINUX 0
    #define CYGWIN 0
    #define COMPILER_PATH "MinGW/x86_64-w64-mingw32/include/"
    #define COMPILER_PATH_1 ""
    #define COMPILER_PATH_2 ""
#endif
#ifdef __linux__
    #define MINGW 0
    #define LINUX 1
    #define CYGWIN 0
    #define COMPILER_PATH ""
    #define COMPILER_PATH_1 "usr/lib/gcc/x86_64-linux-gnu/11/include"
    #define COMPILER_PATH_2 "usr/include/"
#endif
#ifdef __CYGWIN__
    #define MINGW 0
    #define LINUX 0
    #define CYGWIN 1
    #define COMPILER_PATH "Cygwin/lib/gcc/x86_64-pc-cygwin/11/include"
    #define COMPILER_PATH_1 ""
    #define COMPILER_PATH_2 ""
#endif

//char* handle_include_program_files(char* source_code, int index, MultiString* includes, char* base_directory) {
char* handle_include_program_files(char* reading_buffer, PatternMatcher* pattern_match_base) {
    
    //char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_base
    // TODO: implement handle_include_program_files()

    printf("hipf: |%s|\n", reading_buffer); 

    char include_dir[MAX_LENGTH_INCUDE] = ""; 

    int scan_ret = sscanf(reading_buffer, "%s\"", include_dir); 
    if(scan_ret == 0) {
        printf("error while parsing include. (%s)\n", include_dir); 
        return NULL; 
    } else {

        include_dir[strlen(include_dir) - 1] = '\0'; // erase last |"|
        //printf("Parsing succesfull. |%s|\n", include_dir); 

    }

    // get file contents, preprocess (, free) and return 

    size_t size_include = -1; 

    char* raw_include = GetFileContents(include_dir, &size_include, false); 
    if(raw_include == NULL) return NULL; 
    //printf("hipf file contents: |%s|\n", raw_include); 


    char* ret = preprocess(raw_include, &size_include, pattern_match_base); 

    //printf("hipf preprocessed: |%s|\n", ret); 


    // TODO: free       free       free       free       free       free       free       

    free(raw_include); 

    /* We do not have ownership over reading_buffer, _len, pattern_match_base; therefore we must 
    NOT free them. */

    return ret; 
}

char* handle_include_compiler_files(char* reading_buffer, PatternMatcher* pattern_match_base) {
    char include_dir[MAX_LENGTH_INCUDE];
    char* raw_include;
    size_t size_include = -1;
    printf("Enter handle.\n");
    if(LINUX == 1){
        printf("Enter LINUX.\n");
        strcpy(include_dir, COMPILER_PATH_1);
        raw_include = GetFileContents(include_dir, &size_include, false);
        if(raw_include == NULL){
            strcpy(include_dir, COMPILER_PATH_2);
            raw_include = GetFileContents(include_dir, &size_include, false);
            if(raw_include == NULL){
                printf("Cannot open target file.\n");
                return NULL;
            }
        }
    }
    else{
        strcpy(include_dir, COMPILER_PATH);
        raw_include = GetFileContents(include_dir, &size_include, false);
        if(raw_include == NULL){
            printf("Cannot open target file.\n");
            return NULL;
        }
    }
    char* ret = preprocess(raw_include, &size_include, pattern_match_base);
    free(raw_include);

    /* We do not have ownership over reading_buffer, _len, pattern_match_base; therefore we must
    NOT free them. */

    return ret;
}



