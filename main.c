#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

#include "handle_backslash.h"
#include "handle_comments.h"
#include "handle_constants.h"
#include "handle_includes.h"
#include "handle_macros.h"


/*
    Escriviu aquí els vostres noms, U i NIA per si acas: 



    Marcel Aranich, U185166, NIA: 251453
    Ariadna Prat, U15150, NIA:251281


*/

#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)


void PrintHelp(); 


int main(int argc, char** argv) {


    // argv[1] is the file to pre-process

    if(argc < 2) {
        printf("ERROR: To few arguments. (incude file to preprocess)\n"); 
        printf("Usage: ./%s {name of the program to pre-process} \n", argv[0]); 
        printf("Use the flag \"-help\" to get help. \n"); 
        return 1; // return error
    }

    bool eliminate_comments_flag = true; // -c flag (true by deafult)
    bool replace_all_directives = false; // -d flag
    bool user_needs_help = false; // -help flag

    for(int i = 2; i < argc; i++) { //handle flags

        switch (argv[i][1]) {
        case 'c': // -c
            //TODO: I dont fully inderstand what this flag has to do. Someome please fix this
            if(strcmp(argv[i], "-c") != 0) { 
                // not what we expected
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 

                printf("Tip: maybe you intended to use: \"-c\" ? \n"); 
                return 1; 
            } 
            eliminate_comments_flag = true; //?
            break;
        case 'd': //-d
            if(strcmp(argv[i], "-d") != 0) { 
                // not what we expected
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                
                printf("Tip: maybe you intended to use: \"-d\" ? \n"); 
                return 1; 
            } 
            replace_all_directives = true; 
            break;
        case 'h': //-help
            if(strcmp(argv[i], "-help") != 0) { 
                // not what we expected
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                
                printf("Tip: maybe you intended to use: \"-help\" ? \n"); 
                return 1; 
            } 
            user_needs_help = true; 
            break;
        case 'a': //-all
            if(strcmp(argv[i], "-a") != 0) { 
                // not what we expected
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 
                
                printf("Tip: maybe you intended to use: \"-a\" ? \n"); 
                return 1; 
            } 
            eliminate_comments_flag = true; 
            replace_all_directives = true; 
            break;
        default: 
            
            printf("ERROR: unknown flag: \"%s\" \n", argv[i]); 

            return 1; 

            break;
        }
    }

    if(user_needs_help) {
        PrintHelp(); 
        //return 0; // finish execution ?
    }

    return 0; 
    //TODO: check that everything else in argv is correct

    FILE* source_file = fopen(argv[1], "r"); // we cannot modify original file

    if(source_file == NULL) {
        printf("ERROR: Could not open file: %s", argv[1]); 
    }


    int file_length_bytes = -1; 

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

    char* file_contents = (char*)malloc(file_length_bytes); 

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

    //call every function to preprocess: 

    //file_contents = 

    printf("Readed file: \n\n%s\n\n", file_contents); 


    free(file_contents); 

}

void PrintHelp() {

    //TODO: debug all information

    printf("\n\nHere all the help needed should be printed. \n\n"); 
    printf("Since its not currenly implemented, you can have a happy face: \n\n\t:)\n\n"); 
}

























/*

gcc main.c -o main

./main SampleText_00.txt

*/
