#include "main.h"
/*
*    Marcel Aranich, U185166, NIA: 251453
*    Arnau Solans, U161668, NIA: 216530
*    David Garcia Lozano, U198629, NIA: 251587
*    Ariadna Prat, , NIA: 251281
*    Clàudia Quera, U172781, NIA: 231197
*    Jorge Villarino, , NIA: 231351
* Compilers
* Practice 1: c pre-processor
* File name: main.c
* Main program file
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/



int main(int argc, char** argv) {
    // Initialize flags to specify preprocessor behaviour
    bool process_comments;
    bool process_directives;
    processFlags(argc, argv, &process_comments, &process_directives); // Process input arguments to update flags
    char* filename = get_new_filename(argv[argc - 1], false); // Compute new filename
    printf("\nOld filename: %s\n\n", argv[argc-1]); //TODO: might want to remove this
    printf("New filename: %s\n\n", filename);
    size_t original_file_length = 0; // Initialize variable to store original file length
    char* reading_buffer = GetFileContents(argv[argc - 1], &original_file_length, true); // Initialize reading buffer
    size_t writing_buffer_len = original_file_length; // Define writing buffer length with updated original file length
    // Initialize pattern matcher that detects the things that our code needs to detect
    PatternMatcher pattern_match_static;
    pattern_matcher_initialize(&pattern_match_static);
    add_static_patterns(&pattern_match_static);
    char* preprocessed_file = preprocess(reading_buffer, &writing_buffer_len, &pattern_match_static); // Call preprocessing with static patterns
    free(reading_buffer); // free reading buffer memory
    // Write the preprocessed file and check for errors
    int writing_file_error_return = write_new_file(preprocessed_file, writing_buffer_len, filename);
    if(writing_file_error_return != 0) {
        printf("There has been an error while writing into the new file. \n");
    }
    // Free used memory for filename storage, static pattern matcher, and preprocessed content
    free(filename);
    free_pattern_matcher(&pattern_match_static);
    free(preprocessed_file);

    return 0; 

}


void pre_handle_compile_file(char* reading_buffer, int* reading_buffer_index, char* writing_buffer,
                             size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_static) {


    char* include_text = handle_include_compiler_files(reading_buffer, pattern_match_static);
    //^should return direcly what needs to be inserted in the writing buffer

    int len = strlen(include_text);



    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        writing_buffer = realloc(writing_buffer, *writing_buffer_len);
    }

    memcpy(&writing_buffer[*writing_index - INCLUDE_FILE_PATTERN_DETECTION_LEN], include_text, (size_t)len);
    *writing_index += len;
    //^ -1 is correct (???) <- check
    free(include_text);


    // update reading index

    while(reading_buffer[*reading_buffer_index] != '\"'){
        *reading_buffer_index += 1;
    }
    /*
    reading_buffer_index is now in the correct position will be on the char after the closing
    ", wich is the intended way.
    */
}

void pre_handle_include_file(char* reading_buffer, int* reading_buffer_index, char* writing_buffer, 
        size_t* writing_buffer_len, int* writing_index, PatternMatcher* pattern_match_base) {

    /*This hideous function only exists for the grade. 
    "because each switch statement case has only a function"
    */


    char* include_text = handle_include_program_files(reading_buffer, pattern_match_base); 
    //^should return direcly what needs to be inserted in the writing buffer

    int len = strlen(include_text); 



    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        writing_buffer = realloc(writing_buffer, *writing_buffer_len);
    }

    memcpy(&writing_buffer[*writing_index - INCLUDE_FILE_PATTERN_DETECTION_LEN], include_text, (size_t)len); 
    *writing_index += len; 
    //^ -1 is correct (???) <- check
    free(include_text); 
    
    
    // update reading index

    while(reading_buffer[*reading_buffer_index] != '\"'){
        *reading_buffer_index += 1; 
    }
    /*
    reading_buffer_index is now in the correct position will be on the char after the closing
    ", wich is the intended way. 
    */

}
void pre_handle_ifdef_endif(char* reading_buffer, char* writing_buffer,
                 size_t* writing_buffer_len, int* writing_index, int count_struct){
    ; // <- empty statement DO NOT REMOVE
    char* e=eliminar(reading_buffer);
    char* d=eliminar_comentarios_bloque(e);
    int len = -1;
    char *if_def_text = handle_ifdef_endif (d, count_struct, &len);
    //^should return direcly what needs to be inserted in the writing buffer
    count_struct+=1;
    if(writing_buffer_len <= writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        writing_buffer = realloc(writing_buffer, writing_buffer_len);
    }

    memcpy(&writing_buffer[*writing_index - 5], if_def_text, (size_t)len);
    writing_index += -5 + len - 1;
}
int write_new_file(char* content_buffer, size_t len, char* filename) {

    //I think this function ended up being a bit short... 
    FILE* preprocessed_file = fopen(filename, "wb"); //create/overwrite new file
    if(preprocessed_file == NULL) return 1; //error

    
    size_t fwrite_ret = fwrite(content_buffer, (size_t)1, len, preprocessed_file); //write everything
    if(fwrite_ret != len) {
        //not all characters successfully writed
        return 2; //error
    }

    fclose(preprocessed_file); 
    return 0; //success

}























/*
./preprocessor SampleText_00.txt



cd .\Code\
// ^enter the Code sub-folder

gcc main.c -o preprocessor
// ^just compile the main file

gcc main.c Utils.c -o preprocessor
// ^also compile the utils.c file

gcc main.c Utils.c handle_backslash.c handle_comments.c handle_constants.c handle_ifdef_endif.c handle_includes.c handle_macros.c -o preprocessor
// ^compile using everything

./preprocessor -all ./../SampleText_00.c

*/
