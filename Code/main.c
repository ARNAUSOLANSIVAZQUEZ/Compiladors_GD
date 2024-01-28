#include "main.h"
/*
*    Marcel Aranich, U185166, NIA: 251453
*    Arnau Solans, U161668, NIA: 216530
*    David Garcia Lozano, U198629, NIA: 251587
*    Ariadna Prat, U185150, NIA: 251281
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

/*

gcc main.c multistring.c patternmatcher.c utils.c preprocessor.c handle_backslash.c handle_comments.c handle_constants.c handle_ifdef_endif.c handle_includes.c handle_defines.c -o preprocessor
// ^compile using everything

./preprocessor -all ./../SampleText_00.c

*/
