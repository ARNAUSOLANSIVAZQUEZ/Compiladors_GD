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
    David Garcia Lozano, U198629, NIA: 251587


*/

#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)


void PrintHelp(); 


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




    size_t file_length_bytes = -1; 


    /*
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
    */

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
    
    return 0; 
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
