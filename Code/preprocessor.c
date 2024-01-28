/*
* Compilers
* Practice 1: c pre-processor
* File name: main.c
* Recursive preprocessing function.
*
*
* Responsible: Marcel Aranich, Arnau Solans
*/
#include "preprocessor.h"

char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_static) {
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
    int count_struct=0; //case #ifdef_endif
    //Define the table for storing the defines information
    //Define the number of rows in your table
    int num_rows = TABLE_ROWS;
    // Allocate memory for an array of struct DefineInfo
    struct DefineInfo* table = (struct DefineInfo*)malloc(num_rows * sizeof(struct DefineInfo));
    for(int i = 0; i < *_len; i++){
        current_char = reading_buffer[i];
        pattern_return = pattern_scan(pattern_match_static, current_char);
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
                char* define_text = handle_define(reading_buffer);
                // We use pattern_match_dyn to store the identifier
                char* identifier = get_identifier_from_define(define_text);
                add_pattern(&pattern_match_dyn, identifier, pattern_match_dyn.num_patterns);
                // Create an error result structure
                struct DefineInfo error_result = create_error_result();
                // Example: Call handle_define with a predefined #define line
                struct DefineInfo result = handle_define("#define max(x,y) (x>y?x:y)\n");
                // Check if the result is not an error
                if (result.id != error_result.id) {
                    // Check if an entry with the same ID and identifier already exists
                    if (entryExists(table, num_rows, result.id, result.identifier)) {
                        // If exists, update the table entry
                        updateTable(table, num_rows, result);
                    } else {
                        // If not exists, add a new entry to the table
                        addToTable(table, num_rows, result);
                    }
                }

                //printTable(table, num_rows);

                /*TODO: store all the information needed in a corresponding data structure

                Also use pattern_match_dyn to store the identifier of the constant/macro.
                When the pattern is detected bellow this switch, use he handle_macro() or
                handle_constant() accordingly. You may want to delete one of the 2 functions.

                ; // <- empty statement DO NOT REMOVE

                //get the following using the reading buffer
                char patten_definition[500] = "#define this_cool_stuff_i_found(x) (x + 3) ";

                //get somehow
                char pattern[500] = "this_cool_stuff_i_found" ;

                add_pattern(&pattern_match_dyn, pattern, pattern_match_dyn.num_patterns);
                //^save pattern; 3rd argument should be an unique ID

                //TODO: store the information as you can

                writing_index += - 1; //update accordingly
                */

                break;
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
                pre_handle_ifdef_endif(reading_buffer, writing_buffer, &writing_buffer_len, &writing_index, count_struct);

                break;
            case INCLUDE_COMP_ID:
                pre_handle_include_file(reading_buffer, &i, writing_buffer,
                                        &writing_buffer_len, &writing_index, pattern_match_static);
                break;
            case INCLUDE_LOC_ID:
                //patter: "#include \""
                pre_handle_include_file(reading_buffer, &i, writing_buffer,
                                        &writing_buffer_len, &writing_index, pattern_match_static);
                break;
            case COMMENT_ID:

                ; // <- empty statement DO NOT REMOVE


                handle_comments_simple(reading_buffer, i, new_index);
                //^ should return the position of the next char to write (even if its /0)

                i = new_index - 1; // ignore the whole comment

                writing_index += -2; //repcace the // in the writting buffer
                // -1 is for going back and the other -1 is to account the ++ at the end of the for

                break;
            case MULTI_COMMENT_ID:

                ; // <- empty statement DO NOT REMOVE


                handle_comments_multi(reading_buffer, i, new_index);
                //^ should return the position of the next char to write (even if its /0)

                i = new_index - 1; // ignore the whole comment

                writing_index += -2; //repcace the / * in the writting buffer
                // -1 is for going back and the other -1 is to account the ++ at the end of the for


                break;
            default:
                // help, this should not happen
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
            char* define_text = handle_define(reading_buffer, i, &data_structure, pattern_return, &len);

            if(writing_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writing_buffer_len = writing_buffer_len * ARRAY_GROWTH_FACTOR;
                writing_buffer = realloc(writing_buffer, writing_buffer_len);
            }

            memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)len);
            writing_index += 0; //update acorfingly


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

