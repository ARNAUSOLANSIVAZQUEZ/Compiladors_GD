/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_includes.c
* Include directive handler.
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/
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

    char include_dir[MAX_LENGTH_INCLUDE] = "";

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
    char include_dir[MAX_LENGTH_INCLUDE];
    char* raw_include;
    size_t size_include = -1;
    if(LINUX == 1){
        strcpy(include_dir, COMPILER_PATH_1);
        printf("%s\n", COMPILER_PATH_1);
        raw_include = GetFileContents(include_dir, &size_include, false);
        if(raw_include == NULL){
            strcpy(include_dir, COMPILER_PATH_2);
            raw_include = GetFileContents(include_dir, &size_include, true);
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


void pre_handle_compile_file(char* reading_buffer, int* reading_buffer_index, char** writing_buffer,
                             size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_static) {
    printf("%s", &reading_buffer[*reading_buffer_index]);
    char* include_text = handle_include_compiler_files(&reading_buffer[*reading_buffer_index], pattern_match_static);
    //^should return direcly what needs to be inserted in the writing buffer
    if(include_text == NULL){
        printf("Error while handling include compiler files. \n");
        return;
    }
    int len = strlen(include_text);
    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        *writing_buffer = realloc(*writing_buffer, *writing_buffer_len);
    }
    //printf("pre memcpy: |%s|\n", writing_buffer);
    memcpy(&(*writing_buffer)[*writing_index - INCLUDE_FILE_PATTERN_DETECTION_LEN], include_text, (size_t)len);
    *writing_index = strlen(*writing_buffer) - 1;
    //^ -1 is correct (???) <- check
    printf("len: %d || writing idx: %d\n", len, *writing_index - len +1);
    //printf("includetext %d: |%s|\n", strlen(include_text), include_text);
    //printf("post memcpy writing_buffer: |%s|\n", *writing_buffer);
    free(include_text);
    // update reading index
    *reading_buffer_index += 1; //ignore current |"|
    while(reading_buffer[*reading_buffer_index] != '>'){
        *reading_buffer_index += 1;
    }
    /*
    reading_buffer_index is now in the correct position will be on the char after the closing
    ", wich is the intended way.
    */
}


void pre_handle_include_file(char* reading_buffer, int* reading_buffer_index, char** writing_buffer,
                             size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_static) {

    char* include_text = handle_include_program_files(&reading_buffer[*reading_buffer_index + 1], pattern_match_static);
    //^should return direcly what needs to be inserted in the writing buffer
    if(include_text == NULL){
        printf("Error while handling include program files. \n");
        return;
    }
    int len = strlen(include_text);
    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        *writing_buffer = realloc(*writing_buffer, *writing_buffer_len);
    }
    //printf("pre memcpy: |%s|\n", writing_buffer);
    memcpy(&(*writing_buffer)[*writing_index - INCLUDE_FILE_PATTERN_DETECTION_LEN], include_text, (size_t)len);
    *writing_index = strlen(*writing_buffer) - 1;
    //^ -1 is correct (???) <- check
    printf("len: %d || writing idx: %d\n", len, *writing_index - len +1);
    //printf("includetext %d: |%s|\n", strlen(include_text), include_text);
    //printf("post memcpy writing_buffer: |%s|\n", *writing_buffer);
    free(include_text);
    // update reading index
    *reading_buffer_index += 1; //ignore current |"|
    while(reading_buffer[*reading_buffer_index] != '\"'){
        *reading_buffer_index += 1;
    }
    /*
    reading_buffer_index is now in the correct position will be on the char after the closing
    ", wich is the intended way.
    */

}

