#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>

#include "handle_backslash.h"
#include "handle_comments.h"
#include "handle_constants.h"
#include "handle_includes.h"
#include "handle_macros.h"
#include "handle_ifdef_endif.h"

#include "Utils.h"


/*
    Escriviu aquí els vostres noms, U i NIA per si acas: 



    Marcel Aranich, U185166, NIA: 251453
    Arnau Solans, U161668, NIA: 216530
    David Garcia Lozano, U198629, NIA: 251587
    Ariadna Prat, , NIA: 251281
    Clàudia Quera, , NIA: 231197
    Jorge Villarino, , NIA: 231351


*/

#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)

#define DEFINE_ID 1 
#define IFDEF_ID 2
#define INCLUDE_COMP_ID 3 
#define INCLUDE_LOC_ID 6 //unsorted
#define COMMENT_ID 4
#define MULTI_COMMENT_ID 5


void PrintHelp(); 


/*
preprocesses the given reading_buffer and returns a new str with the preprocessed file. 
includes is a multistring (see utils.h) that contains all the currenly added includes. 
_len points to the original size og reading buffer and will be overwritten to the final 
size of the output
*/
char* preprocess(char* reading_buffer, size_t* _len, MultiString* includes); 

int main(int argc, char** argv) {

    //2

    // argv[1] is the file to pre-process

    bool eliminate_comments_flag = true; // -c flag (true by deafult)
    bool replace_all_directives = false; // -d flag


    if(argc < 2) {
        printf("ERROR: To few arguments. (incude file to preprocess)\n"); 
        printf("Usage: ./%s {flags} {name of the program to pre-process} \n", argv[0]); 
        printf("Use the flag \"-help\" to get help. \n"); 
        return 1; // return error
    } else if(2 < argc) {

        // handle flags
        /*Note: if the same valid flag is used more than once, the other 
        instances will be effectively ignored (acording to instructions)*/

        bool user_needs_help = false; // -help flag
        bool abort = false; 
        eliminate_comments_flag = false; 

        for(int i = 1; i < argc - 1; i++) { //handle flags

            // remove switch and use only strcmp()  ?
            switch (argv[i][1]) {
            case 'c': // -c
                if(strcmp(argv[i], "-c") != 0) { 
                    // the input is not what we expected. Handle error and abort. 
                    printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 

                    printf("Tip: maybe you intended to use: \"-c\" ? \n"); 
                    abort = true; 
                    break; 
                } 
                eliminate_comments_flag = true; 
                break;
            case 'd': //-d
                if(strcmp(argv[i], "-d") != 0) { 
                    // not what we expected
                    printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                    
                    printf("Tip: maybe you intended to use: \"-d\" ? \n"); 
                    abort = true; 
                    break; 
                } 
                replace_all_directives = true; 
                break;
            case 'h': //-help
                if(strcmp(argv[i], "-help") != 0) { 
                    printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                    
                    printf("Tip: maybe you intended to use: \"-help\" ? \n"); 
                    abort = true; 
                    break; 
                } 
                user_needs_help = true; 
                break;
            case 'a': //-all
                if(strcmp(argv[i], "-all") != 0) { 
                    printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                    
                    printf("Tip: maybe you intended to use: \"-all\" ? \n"); 
                    abort = true; 
                    break; 
                } 
                eliminate_comments_flag = true; 
                replace_all_directives = true; 
                break;
            default: 
                // unexpected flag
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 

                abort = true; 

                break;
            }
        } 

        if(user_needs_help) {
            PrintHelp(); 
            //return 0; // finish execution ?
        }

        if(abort){
            return 1; 
        }


    } else if(strcmp(argv[1], "-help") == 0) {

        PrintHelp(); 
        return 0; 

    }

    //////////////////////////////////////////////////////



    /*
    size_t file_length_bytes = -1; 


    
    FILE* source_file = fopen(argv[argc - 1], "rb"); // r because we cannot modify original file

    if(source_file == NULL) {
        printf("ERROR: Could not open file: %s", argv[argc - 1]); 
        return 1; 
    }



    { // find size of file
        int fseek_return = fseek(source_file, 0L, SEEK_END); 
        if(fseek_return != 0) { //error
            printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return 1; 
        }

        long int ftell_return = ftell(source_file); 

        if(ftell_return == -1L) { //error
            printf("ERROR: error while reading file. ftell return: %d", ftell_return); 
            fclose(source_file); 
            return 1; 
        }

        file_length_bytes = (size_t) ftell_return; 
        fseek_return = fseek(source_file, 0L, SEEK_SET); 

        if(fseek_return != 0) { //error
            printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return 1; 
        }
    }

    char* file_contents = (char*)calloc(file_length_bytes, 1); 


    if(file_contents == NULL) { // error requesting memory
        printf("ERROR: error while requesting memory. \nMemory asked: %d Bytes\t = %d MB", file_length_bytes, (int) file_length_bytes * BYTES_TO_MB_CONVERSION_FACTOR); 
        fclose(source_file); 
        return 1; 
    }

    { // copy contents
        size_t fread_return = fread(file_contents, 1, file_length_bytes, source_file); 

        if(fread_return != file_length_bytes && feof(source_file) == 0) { // handle error
            printf("ERROR: error while reading file. fread return: %d\tfile length: %d bytes\n", fread_return, file_length_bytes); 
            printf("feof(file) = %d\n", feof(source_file)); 
            fclose(source_file); 
            return 1; 
        }
    }
    fclose(source_file); // no need to keep file open
    

    char* file_contents = NULL; 

    {

        int directory_len = strlen(argv[argc - 1]); //copy directoty to another string
        char* directory_copy = calloc(directory_len, 1); 
        int memcpy_ret = memcpy_s(directory_copy, directory_len, argv[argc - 1], directory_len); 
        if(memcpy_ret != 0) {
            printf("There has been an error wile attempting to move data. err num: %d\n\n", memcpy_ret); 
            return 1; 
        }
        
        bool debug_error_messages = true; 
        file_contents = GetFileContents(directory_copy, &file_length_bytes, debug_error_messages); 

        if(file_contents == NULL) {
            printf("There has been an error while accessing the contents of the file. "); 
            return 1; 
        }
        
    }


    printf("Readed file: \n\n%s\n\n", file_contents); 

    //call every function to preprocess: 

    if(false) { // debbuging, TODO: remove later

        if(replace_all_directives) {
            file_contents = handle_include_program_files(file_contents, &file_length_bytes); 
            file_contents = handle_include_compiler_files(file_contents, &file_length_bytes); 
            file_contents = handle_ifdef_endif(file_contents, &file_length_bytes);
        }

        file_contents = handle_backslash(file_contents, &file_length_bytes); 
        file_contents = handle_constants(file_contents, &file_length_bytes); 
        file_contents = handle_macros(file_contents, &file_length_bytes); 


        if(eliminate_comments_flag) {
            file_contents = remove_single_line_comments(file_contents, &file_length_bytes); 
            file_contents = remove_multi_line_comments(file_contents, &file_length_bytes); 
        }

    }    



    // printf("Final pre-processing: \n\n%s\n\n", file_contents); 

    int original_file_len = strlen(argv[argc - 1]) + 1; // +\0
    int preprocessed_file_name_length = original_file_len + 3;  // + "_pp"

    char* preprocessed_file_name = calloc(preprocessed_file_name_length, 1); 

    {
        // NOTE: this code assumes only 1 letter is used as extension (prm.c, file.h, smtng.p, but NOT inc.asd)

        int error_ret = (int)memcpy_s(preprocessed_file_name, preprocessed_file_name_length, argv[argc - 1], original_file_len - 3); 

        if(error_ret != 0) {
            printf("ERROR: error while moving data (memcpy_s). \n"); 
            return 1; 
        }

        int bytes_to_copy = preprocessed_file_name_length - (original_file_len - 3); 

        error_ret = (int)memcpy_s(&preprocessed_file_name[original_file_len - 3], bytes_to_copy, "_pp.c\0", bytes_to_copy); 

        if(error_ret != 0) {
            printf("ERROR: error while moving data (memcpy_s 2). %d\n", error_ret); 
            return 1; 
        }

        printf("New file name: \n\t%s\n", preprocessed_file_name); 
    }

    FILE* preprocessed_file = fopen(preprocessed_file_name, "wb"); //create new file

    
    fwrite(file_contents, 1, file_length_bytes, preprocessed_file); //write everything

    free(preprocessed_file_name); 
    free(file_contents); 

    fclose(preprocessed_file); 
    */
    /*
    // Open the file read-only
    // FILE* fh = fopen(argv[2], "r");
    // Obtain length of original file name (+"\0")
    int original_file_len = strlen(argv[argc - 1]) + 1;
    // Compute length of preprocessed file name (+"_pp")
    int preprocessed_file_name_length = original_file_len + 3;
    // Allocate space for preprocessed file name
    char* preprocessed_file_name = calloc(preprocessed_file_name_length, 1);
    // Create the preprocessed file to write
    // Allocate space to read lines
    char* line = malloc(MAX_LENGTH); 
    // Terminate if empty file
    if(fh == NULL){
        return 1;
    }
    // Reading loop
    while(true) {
        // Obtain position before reading
        int old_pos = ftell(fh);
        // Reading a line
        char* l = fgets(line, MAX_LENGTH,fh); 
        // Obtain position after reading
        int new_pos = ftell(fh);
        // Iterating over characters of line read
        for(int i = 0; i < strlen(l); i++) {
            // Retrieve current character
            char c = l[i];
            // Define next_character
            char next_c;
            // Switch for current character
            switch(c) {
                // Starts with #
                case '#':
                    printf("Hashtag case:");
                    next_c = l[i+1]; ///////////////// <- bad idea, we dont know if it is out of bounds
                    // Switch for next character
                    switch(next_c){
                        // Define case
                        case 'd':
                            printf("Define case\n");
                            // TODO: handle define (correct and errors)
                            break;
                        // Include / Ifdef case
                        case 'i':
                            char next_c2 = l[i+2];  /////// <- also bad idea
                            switch(next_c2){
                                // Include case
                                case 'n':
                                    printf("Include case\n");
                                    // TODO: handle include (correct and errors)
                                    break;
                                // Ifdef case
                                case 'f':
                                    printf("Ifdef case\n");
                                    // TODO: handle ifdef (correct and errors)
                                    break;
                                // Invalid case
                                default:
                                    printf("Not correct");
                                    break;
                            }
                        // Invalid case
                        default:
                            printf("Not a hashtag\n");
                            break;
                    }
                    break; 
                // Backslash case
                case '\\':
                    printf("Bacslash case\n");
                    // TODO: handle backlash (variations correct and errors)
                    break;
                // Comment case
                case '/':
                    printf("Comment case:");
                    next_c = l[i+1];
                    // Switch for next character
                    switch(next_c){
                        // Simple comment case
                        case '/':
                            printf("Simple comment\n");
                            // TODO: handle simple comment
                            break;
                        // Multiline comment case
                        case '*':
                            printf("Multiline comment\n");
                            // TODO: handle multiline comment
                            break;
                        // Invalid case
                        default:
                            printf("Not a comment\n");
                            break;
                    }
                    break;
            }
        }
        // Break if we reached EOF
        if(feof(fh)){break;}
    }

    free(line); 

    // Close file handle for reading

    FILE* fhpp = fopen(preprocessed_file_name, "wb");

    // Close file handle for writing
    fclose(fhpp);*/ 

    size_t original_file_length = 0; //NOT including /0 
    char* reading_buffer = GetFileContents(argv[argc - 1], &original_file_length, true); 
    //^read gile contents and store them in the reading buffer. the reading buffer 
    // should not be altered

    MultiString includes; 
    includes.capacity = 5; 
    includes.string_arr = (char**)calloc(includes.capacity, sizeof(char*)); 
    includes.string_len = (int*)calloc(includes.capacity, sizeof(int)); 
    includes.length = 0; //no str currenly stored

    {
        //TODO: add include of the current file
        //add_string(&includes, some_str_heap_allocated)

    }

    size_t writting_buffer_len = original_file_length; //copy contents








    char* preprocessed_file = preprocess(reading_buffer, &writting_buffer_len, &includes); 

    free(reading_buffer); 

    //TODO: put everything in new file

    //reuse code in 1st big comment (?)


    free(preprocessed_file); 
    free_multi_string(&includes); 

    return 0; 

}


char* preprocess(char* reading_buffer, size_t* _len, MultiString* includes) {


    size_t writting_buffer_len = *_len; 
    char* writing_buffer = (char*)malloc(writting_buffer_len * sizeof(char)); // will probably be increased in size
    

    /*This pattern matcher detects the things that our code needs to detect
    */
    PatternMatcher pattern_match_base; // see Utils.c
    pattern_match_base.capacity = 6; 
    pattern_match_base.num_patterns = 0; 
    pattern_match_base.patterns = (Pattern**)calloc(pattern_match_base.capacity, sizeof(Pattern*)); 


    //moved id as constants

    {
        //define basic patterns
        char* define_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(define_pattern, "#define "); 
        add_pattern(&pattern_match_base, define_pattern, DEFINE_ID); 

        char* ifdef_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(ifdef_pattern, "#ifdef"); 
        add_pattern(&pattern_match_base, ifdef_pattern, IFDEF_ID); 

        char* include_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(include_pattern, "#include <"); 
        add_pattern(&pattern_match_base, include_pattern, INCLUDE_COMP_ID); 

        char* comment_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(comment_pattern, "//"); 
        add_pattern(&pattern_match_base, comment_pattern, COMMENT_ID); 

        char* ML_comment_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(ML_comment_pattern, "/*"); 
        add_pattern(&pattern_match_base, ML_comment_pattern, MULTI_COMMENT_ID); 

        char* inlcude_local_pattern = (char*)malloc(20 * sizeof(char)); 
        strcpy(inlcude_local_pattern, "#include \""); 
        add_pattern(&pattern_match_base, inlcude_local_pattern, INCLUDE_LOC_ID); 

    }

    /*This pattern matcher detects the things that can be found again in the code 
    i.e. defines*/
    PatternMatcher pattern_match_dyn; // see Utils.c
    pattern_match_dyn.capacity = 5; 
    pattern_match_dyn.num_patterns = 0; 
    pattern_match_dyn.patterns = (Pattern**)calloc(pattern_match_dyn.capacity, sizeof(Pattern*)); 

    


    unsigned int writing_index = 0; 
    int len = -1; 
    int new_index = 0; 
    char* include_text = NULL; 


    for(int i = 0; i < *_len; i++){

        char current_char = reading_buffer[i]; 

        int pattern_return = pattern_scan(&pattern_match_base, current_char); 

        switch (pattern_return)
        {
        case 0: // NO PATTERN
            writing_buffer[writing_index] = current_char; 
            //coninue writting normally

            if(writting_buffer_len <= writing_index + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
            }

            break;
        case DEFINE_ID: //#define

            /*TODO: store all the information needed in a corresponding data structure
            
            Also use pattern_match_dyn to store the identifier of the constant/macro. 
            When the pattern is detected bellow this switch, use he handle_macro() or 
            handle_constant() accordingly. You may want to delete one of the 2 functions. 


            */

            ; // <- empty statement DO NOT REMOVE


            //get the following using the reading buffer
            char patten_definition[500] = "#define this_cool_stuff_i_found(x) (x + 3) "; 

            //get somehow 
            char pattern[500] = "this_cool_stuff_i_found" ; 

            add_pattern(&pattern_match_dyn, pattern, pattern_match_dyn.num_patterns); 
            //^save pattern; 3rd argument should be an unique ID

            //TODO: store the information as you can

            writing_index += - 1; //update accordingly


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


            ; // <- empty statement DO NOT REMOVE

            len = -1; 
            include_text = handle_include_compiler_files(reading_buffer, i - 9, &len); 
            //^should return direcly what needs to be inserted in the writing buffer

            if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
            }

            memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)len); 
            writing_index += -9 + len - 1; 

            break;        
        case INCLUDE_LOC_ID: 


            ; // <- empty statement DO NOT REMOVE

            len = -1; 
            include_text = handle_include_program_files(reading_buffer, i - 9, &len); 
            //^should return direcly what needs to be inserted in the writing buffer

            if(writting_buffer_len <= writing_index + len + 1 ) { // +1 for /0
                // get more space
                writting_buffer_len = writting_buffer_len * ARRAY_GROWTH_FACTOR; 
                writing_buffer = realloc(writing_buffer, writting_buffer_len); 
            }

            memcpy(&writing_buffer[writing_index - 9], include_text, (size_t)len); 
            writing_index += -9 + len - 1; 

            break;
        case COMMENT_ID: 

            ; // <- empty statement DO NOT REMOVE


            new_index = handle_comments_simple(reading_buffer, i); 
            //^ should return the position of the next char to write (even if its /0)

            i = new_index - 1; // ignore the whole comment

            writing_index += -2; //repcace the // in the writting buffer
            // -1 is for going back and the other -1 is to account the ++ at the end of the for

            break;        
        case MULTI_COMMENT_ID: 

            ; // <- empty statement DO NOT REMOVE


            new_index = handle_comments_multi(reading_buffer, i); 
            //^ should return the position of the next char to write (even if its /0)

            i = new_index - 1; // ignore the whole comment

            writing_index += -2; //repcace the / * in the writting buffer
            // -1 is for going back and the other -1 is to account the ++ at the end of the for


            break;
        default:
            // help, this should not happen
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

    free_pattern_matcher(&pattern_match_base); 
    free_pattern_matcher(&pattern_match_dyn); 



    writing_buffer[writing_index] = '\0'; 
    //set final char to /0, this can be done because we chave space
    //(see realloc in switch(pattern_return) case 0)

    *_len = writting_buffer_len; //return new length
    return writing_buffer; 

}



void PrintHelp() {

    //TODO: debug all information

    //printf("\n\nHere all the help needed should be printed. \n\n"); 
    //printf("Since its not currenly implemented, you can have a happy face: \n\n\t:)\n\n"); 
    
    
    
    printf("\n\n\nUsage: ./preprocessor {flags} {name of the program to pre-process} \n"); 
    printf("Behaviour of the flags: \n\n"); 
    
    printf("\t-c: deletes all comments (// comment and /*comment*/). \n\n"); 
    
    printf("\t-d: Replaces all directives starting with # (#define, #include, etc. ). \n\n"); 
    
    printf("\t-all: shortcut for \"-c -d\" (uses both flags). \n\n"); 
    
    printf("\t-help: display this cool message. \n\n"); 

    printf("Using no flags is equivalent to using only the \"-c\" flag. The order of the flags or amount used is irrelevant. using an invalid flag will abort the process. "); 
    printf("Keep in mind that the file to preprocess needs to be in the last position. \n\n"); 
    
    printf("Note that this preprocessor only supports properly files with .c extention (or other extentions with just 1 letter). Otherwise, the name of the new file may not be properly generated. "); 
    printf("After executing the preprocessor, a new file should appear in the same directory as the old one. "); 
    printf("If the old file was named \"my_program.c\" then the new file will be named \"my_program_pp.c\". "); 
    
    printf("\n\nIMPORTANT: if there already was a file with the same name, it will be overwrited. Be careful with the files you wish to keep. \n\n"); 







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
