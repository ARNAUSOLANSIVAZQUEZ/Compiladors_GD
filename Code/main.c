
#include "main.h"


/*
    Escriviu aquí els vostres noms, U i NIA per si acas: 



    Marcel Aranich, U185166, NIA: 251453
    Arnau Solans, U161668, NIA: 216530
    David Garcia Lozano, U198629, NIA: 251587
    Ariadna Prat, , NIA: 251281
    Clàudia Quera, U172781, NIA: 231197
    Jorge Villarino, , NIA: 231351


*/

//#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)
// ^defined in Utils.h

#define NO_PATTERN_DETECTED 0
#define DEFINE_ID 1 
#define IFDEF_ID 2
#define INCLUDE_COMP_ID 3 
#define INCLUDE_LOC_ID 6 //unsorted
#define COMMENT_ID 4
#define MULTI_COMMENT_ID 5







int main(int argc, char** argv) {

    bool process_comments;
    bool process_directives;
    processFlags(argc, argv, &process_comments, &process_directives);

    char* filename = get_new_filename(argv[argc - 1], false); 

    printf("\nOld filename: %s\n\n", argv[argc-1]); //TODO: might want to remove this
    printf("New filename: %s\n\n", filename); 

    size_t original_file_length = 0; //NOT including /0 
    char* reading_buffer = GetFileContents(argv[argc - 1], &original_file_length, true); 
    //^read gile contents and store them in the reading buffer. the reading buffer 
    // should not be altered


    size_t writting_buffer_len = original_file_length; //copy contents

    /*
        This pattern matcher detects the things that our code needs to detect
    */
    PatternMatcher pattern_match_base; // see Utils.c
    pattern_matcher_initialize(&pattern_match_base); 


    { //define basic patterns
        
        char* define_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(define_pattern, "#define "); 
        add_pattern(&pattern_match_base, define_pattern, DEFINE_ID); 

        char* ifdef_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(ifdef_pattern, "#ifdef"); 
        add_pattern(&pattern_match_base, ifdef_pattern, IFDEF_ID); 

        char* include_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(include_pattern, "#include <"); 
        add_pattern(&pattern_match_base, include_pattern, INCLUDE_COMP_ID); 

        char* comment_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(comment_pattern, "//"); 
        add_pattern(&pattern_match_base, comment_pattern, COMMENT_ID); 

        char* ML_comment_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(ML_comment_pattern, "/*"); 
        add_pattern(&pattern_match_base, ML_comment_pattern, MULTI_COMMENT_ID); 

        char* inlcude_local_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char)); 
        strcpy(inlcude_local_pattern, "#include \""); 
        add_pattern(&pattern_match_base, inlcude_local_pattern, INCLUDE_LOC_ID); 

    }


    char* preprocessed_file = preprocess(reading_buffer, &writting_buffer_len, &pattern_match_base); 

    free(reading_buffer); 

    //char* filename = get_new_filename(argv[argc - 1], false); //moved up

    int writting_file_error_return = write_new_file(preprocessed_file, writting_buffer_len, filename); 
    if(writting_file_error_return != 0){
        printf("There has been an error while writing into the new file. \n"); 
    }

    free(filename); 

    free_pattern_matcher(&pattern_match_base); 

    free(preprocessed_file); 
    //free_multi_string(&includes); 

    return 0; 

}


char* preprocess(char* reading_buffer, size_t* _len, PatternMatcher* pattern_match_base) {


    size_t writting_buffer_len = *_len; 
    char* writing_buffer = (char*)malloc(writting_buffer_len * sizeof(char)); // will probably be increased in size
    

    /*This pattern matcher detects the things that can be found again in the code 
    i.e. defines*/
    PatternMatcher pattern_match_dyn; // see Utils.c
    pattern_matcher_initialize(&pattern_match_dyn); 
    
    //auxiliar variables
    int writing_index = 0; 
    int len = -1; 
    int new_index = 0; 
    char* include_text = NULL; 

    //Define the table for storing the defines information
    //Define the number of rows in your table
    int num_rows = TABLE_ROWS;

    // Allocate memory for an array of struct DefineInfo
    struct DefineInfo* table = (struct DefineInfo*)malloc(num_rows * sizeof(struct DefineInfo));

    for(int i = 0; i < *_len; i++){

        char current_char = reading_buffer[i]; 

        int pattern_return = pattern_scan(&pattern_match_base, current_char); 

        switch (pattern_return)
        {
        case NO_PATTERN_DETECTED: 
            writing_buffer[writing_index] = current_char; 
            //coninue writting normally

            if(writting_buffer_len <= writing_index + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
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

            len = -1; 
            char* if_def_text = handle_ifdef_endif(reading_buffer, i - 5, &len); 
            //^should return direcly what needs to be inserted in the writing buffer

            if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
            }

            memcpy(&writing_buffer[writing_index - 5], if_def_text, (size_t)len); 
            writing_index += -5 + len - 1; 


            break;        
        case INCLUDE_COMP_ID: 

            pre_handle_include_file(reading_buffer, writing_buffer, &writting_buffer_len, &writing_index); 

            /*
                ; // <- empty statement DO NOT REMOVE

                len = -1; 
                include_text = handle_include_compiler_files(reading_buffer, &len); 
                //^should return direcly what needs to be inserted in the writing buffer

                if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                    // get more space
                    writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                    writing_buffer = realloc(writing_buffer, writting_buffer_len); 
                }

                memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)len); 
                writing_index += -9 + len - 1; 
            */

            break;        
        case INCLUDE_LOC_ID: 
            //patter: "#include \""

            pre_handle_include_file(reading_buffer, &i, writing_buffer, 
                &writting_buffer_len, &writing_index, pattern_match_base); 




            /*
                // ; empty statement should not be needes since len = -1 is not a declaration

                len = -1; 
                include_text = handle_include_program_files(source_code, i - 9, &includes, argv[0]); 
                //^should return direcly what needs to be inserted in the writing buffer

                if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                    // get more space
                    writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                    writing_buffer = realloc(writing_buffer, writting_buffer_len); 
                }

                memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)strlen(include_text)); 
                writing_index += -9 + len - 1; 
                ///

            */

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

        pattern_return = pattern_scan(pattern_match_dyn, current_char); 


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

            if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
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

    *_len = writting_buffer_len; //return new length
    return writing_buffer; 
}

void pre_handle_compile_file(char* reading_buffer, char* writing_buffer, size_t* writting_buffer_len, int* writing_index) {

    int len = -1; //aux var
    include_text = handle_include_compiler_files(reading_buffer, &len); 
    //^should return direcly what needs to be inserted in the writing buffer

    if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
        // get more space
        writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
        writing_buffer = realloc(writing_buffer, writting_buffer_len); 
    }

    memcpy(&writing_buffer[writing_index], include_text, (size_t)len); 
    writing_index += len - 1; 
    //^ -1 is correct (???) <- check
    // TODO: update reading index

}

void pre_handle_include_file(char* reading_buffer, int* reading_buffer_index, char* writing_buffer, 
        size_t* writting_buffer_len, int* writing_index, PatternMatcher* pattern_match_base) {

    /*This hideous function only exists for the grade. 
    "because each switch statement case has only a function"
    */


    char* include_text = handle_include_program_files(reading_buffer, pattern_match_base); 
    //^should return direcly what needs to be inserted in the writing buffer

    int len = strlen(include_text); 



    if(*writting_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writting_buffer_len = *writting_buffer_len * ARRAY_GROWTH_FACTOR; 
        writing_buffer = realloc(writing_buffer, *writting_buffer_len); 
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
