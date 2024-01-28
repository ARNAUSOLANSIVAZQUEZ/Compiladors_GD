/*
* Compilers
* Practice 1: c pre-processor
* File name: preprocessor.c
* Recursive preprocessing function.
*
*
* Responsible: Marcel Aranich, Arnau Solans, David Garcia, Claudia Quera
*/
#include "preprocessor.h"

char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_static, MultiString *ms, bool process_comments, bool process_directives) {
    size_t writing_buffer_len = *_len; // Copy writing buffer length
    char* writing_buffer = (char*)malloc(writing_buffer_len * sizeof(char)); // Allocate current length memory
    // Initialize pattern matcher for defines
    PatternMatcher pattern_match_dyn; // see Utils.c
    pattern_matcher_initialize(&pattern_match_dyn);
    // Define auxiliary variables for writing and adding the preprocessed text
    int writing_index = 0;
    int len = -1;
    int new_index = 0;
    char* include_text = NULL;
    char current_char;
    int pattern_return;
    //Define the table for storing the defines information
    //Define the number of rows in your table
    int num_rows = TABLE_ROWS;
    // Allocate memory for an array of struct DefineInfo
    struct DefineInfo* definesTable = (struct DefineInfo*)malloc(num_rows * sizeof(struct DefineInfo));
    for(int i = 0; i < *_len; i++){
        current_char = reading_buffer[i];
        pattern_return = pattern_scan(pattern_match_static, current_char);

        if(!process_directives){
            if(pattern_return == 1 || pattern_return == 2 || pattern_return == 3 || pattern_return == 6 ){
                pattern_return = 0;
            }
        }
        switch (pattern_return)
        {
            case NO_PATTERN_DETECTED:
                writing_buffer[writing_index] = current_char; // Continue writing
                // Expand memory allocation
                if(writing_buffer_len <= writing_index + 1 ) { // +1 for /0 special character
                    writing_buffer_len = writing_buffer_len * ARRAY_GROWTH_FACTOR;
                    writing_buffer = realloc(writing_buffer, writing_buffer_len);
                }
                break;
                
            case DEFINE_ID: //#define
            
                ; // <- empty statement DO NOT REMOVE
                
                char* infoDefinesLine = extractDefineLine(reading_buffer, i);
                // Call the handle_define function to process the #define line
                struct DefineInfo infoDefines = handle_define(infoDefinesLine);
                // Check if the handle_define function returned an error result
                if (infoDefines.id == -1) {
                    // Handle error, for example, print a message
                    printf("Error processing #define at index %d\n", i);
                } else {
                    // Check if an entry with the same ID and identifier already exists
                    if (entryExists(definesTable, num_rows, infoDefines.id, infoDefines.identifier)) {
                        // If exists, update the table entry
                        updateTable(definesTable, num_rows, infoDefines, pattern_match_static);
                    } else {
                        // If not exists, add a new entry to the table
                        definesTable = addToTable(definesTable, num_rows, infoDefines, pattern_match_static);
                        
                    }
                }

                printTable(definesTable, num_rows);

                break;

                /* We have been able to identify the macro and constant variables inside the input files and separate the
                variable or macro name and print them into a table, but even though we have tried it, we could add a new
                pattern that identifies the variables along the file and substitute it for its value. 
                We've commented a couple of lines in the addToTable and UpdateTable functions from the handle_defines.c 
                file with some tries of making this possible.
                */

            case IFDEF_ID:


                ; // <- empty statement DO NOT REMOVE

                /*len = -1;
                char* if_def_text = handle_ifdef_endif(reading_buffer, i - 5, &len);
                //^should return direcly what needs to be inserted in the writing buffer

                if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                    // get more space
                    writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR;
                    writing_buffer = realloc(writing_buffer, writting_buffer_len);
                }

                memcpy(&writing_buffer[writing_index - 5], if_def_text, (size_t)len);
                writing_index += -5 + len - 1;
                */
                pre_handle_ifdef_endif(reading_buffer, i-5, writing_buffer, &writing_buffer_len, &writing_index, ms);

                break;
            case INCLUDE_COMP_ID:
                pre_handle_compile_file(reading_buffer, &i, &writing_buffer, &writing_buffer_len, &writing_index, pattern_match_static, ms, process_comments, process_directives);
                break;
            case INCLUDE_LOC_ID:
                //patter: "#include \""
                pre_handle_include_file(reading_buffer, &i, &writing_buffer,
                                        &writing_buffer_len, &writing_index, pattern_match_static, ms, process_comments, process_directives);
                break;
            case COMMENT_ID:

                ; // <- empty statement DO NOT REMOVE


                handle_comments_simple(reading_buffer, i, &new_index);
                //^ should return the position of the next char to write (even if its /0)

                i = new_index - 1; // ignore the whole comment

                writing_index += -2; //repcace the // in the writting buffer
                // -1 is for going back and the other -1 is to account the ++ at the end of the for

                break;
            case MULTI_COMMENT_ID:

                ; // <- empty statement DO NOT REMOVE


                handle_comments_multi(reading_buffer, i, &new_index);
                //^ should return the position of the next char to write (even if its /0)

                i = new_index - 1; // ignore the whole comment

                writing_index += -2; //repcace the / * in the writting buffer
                // -1 is for going back and the other -1 is to account the ++ at the end of the for


                break;
            case BACKSLASH_ID:
                ;
                pre_handle_backslash(reading_buffer, i, writing_buffer, writing_buffer_len, writing_index);
                break;
            default:
                // help, this should not happen
                printf("%d\n", pattern_return);
                printf("Unexpected pattern at index: %d", i);
                break;
        }

        // =================================================================================
        // =================================================================================
        //dynamic pattern matching

        pattern_return = pattern_scan(&pattern_match_dyn, current_char);


        if (pattern_return != 0) {

            /*Do wathever you need to substitute everything as needed. I leave
            you with something basic you may want to change. */

            struct SUPER_USCEFULL_DATA_STRUCTURE { // /s
                int x;
            };

            struct SUPER_USCEFULL_DATA_STRUCTURE data_structure;
            data_structure.x = 0;

            int len = 0;


            if(writing_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writing_buffer_len = writing_buffer_len * ARRAY_GROWTH_FACTOR;
                writing_buffer = realloc(writing_buffer, writing_buffer_len);
            }

            memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)len);
            writing_index += 0; //update acordingly


        }

        ///////////////////////////////////////////////
        writing_index++; // go to new index

    }

    free_pattern_matcher(&pattern_match_dyn);


    writing_buffer[writing_index] = '\0';
    //set final char to /0, this can be done because we have space
    //(see realloc in switch(pattern_return) case NO_PATTERN_DETECTED)

    *_len = writing_index; //return new length
    return writing_buffer;
}


int write_new_file(char* content_buffer, size_t len, char* filename) {
    FILE* preprocessed_file = fopen(filename, "wb"); // Create or overwrite preprocessed file
    if(preprocessed_file == NULL) return 1; // Error opening the write file
    size_t fwrite_ret = fwrite(content_buffer, (size_t)1, len, preprocessed_file); //write everything
    if(fwrite_ret != len) { // Error while writing some of the characters
        return 2; //error
    }
    fclose(preprocessed_file);
    return 0; //success

}

