

#include "Utils.h"





char* GetFileContents(char* directory, size_t* size_source_code, bool debug_error_messages) {

    *size_source_code = -1; //no undefined behaviour >:(
    FILE* source_file = fopen(directory, "rb"); // r because we cannot modify original file

    if(source_file == NULL) {
        if(debug_error_messages) printf("ERROR: Could not open file in directory: %s", directory); 
        return NULL; 
    }

    free(directory); 

    { // find size of file
        int fseek_return = fseek(source_file, 0L, SEEK_END); 
        if(fseek_return != 0) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return NULL; 
        }

        long int ftell_return = ftell(source_file); 

        if(ftell_return == -1L) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. ftell return: %d", ftell_return); 
            fclose(source_file); 
            return NULL; 
        }

        *size_source_code = (size_t)ftell_return; 
        fseek_return = fseek(source_file, 0L, SEEK_SET); 

        if(fseek_return != 0) { //error
            if(debug_error_messages) printf("ERROR: error while reading file. fseek return: %d", fseek_return); 
            fclose(source_file); 
            return NULL; 
        }
    }

    char* file_contents = (char*)calloc(*size_source_code, 1); 


    if(file_contents == NULL) { // error requesting memory
        if(debug_error_messages) printf("ERROR: error while requesting memory. \nMemory asked: %d Bytes\t = %d MB", size_source_code, (int) *size_source_code * BYTES_TO_MB_CONVERSION_FACTOR); 
        fclose(source_file); 
        return NULL; 
    }

    { // copy contents
        size_t fread_return = fread(file_contents, 1, *size_source_code, source_file); 

        if(fread_return != *size_source_code && feof(source_file) == 0) { // handle error
            if(debug_error_messages) {
                printf("ERROR: error while reading file. fread return: %d\tfile length: %d bytes\n", fread_return, size_source_code); 
                printf("feof(file) = %d\n", feof(source_file)); 
            }

            fclose(source_file); 
            return NULL; 
        }
    }

    fclose(source_file); 

    return file_contents; 


}



int count_ocurrences(char* source_str, size_t str_len, char* element, int element_len) {

    int ret = 0; 
    int current_word_count = 0; 

    for(int i = 0; i < str_len; i++){

        if(source_str[i] == element[current_word_count]) {
            current_word_count++; 

            if(element_len <= current_word_count) {
                current_word_count = 0; 
                ret++; 
            }
        } else current_word_count = 0; 


    }


    return ret; 

}


char* get_new_filename(char* old_name, bool terminate_with_c){

    int old_name_len = strlen(old_name); 
    char* suffix = "_pp"; 
    char* ret = (char*)malloc(old_name_len + strlen(suffix) + 1); 
    strcpy(ret, old_name); 
    char* extension = (char*)calloc(old_name_len, sizeof(char)); //use more memory than needed but its ok
    int e = 0; // e is extension index

    int i = old_name_len - 1; 
    while(0 <= i) { // should always be true

        if(ret[i] == '.') {

            ret[i] = '\0'; 
            strcat(ret, suffix); //add sufix
            i += strlen(suffix); 

            /*
            char* dot = "."; 
            strcat(ret, dot); //add .
            i += 1; 
            */

            //add extension accordingly
            if(terminate_with_c) {

                char* dot_c_extension = ".c\0"; 
                strcat(ret, dot_c_extension); //add .
                //go exit

            } else {
                //use old extension
                char* dot = "."; 
                strcat(ret, dot); //add .
                i += 1; 
                e--; //move from the position to write to the position of the last char

                while(0 <= e) { 
                    ret[i] = extension[e]; 
                    i++; 
                    e--; 
                }
                ret[i] = '\0'; 

            }

            break; 

        }

        extension[e] = ret[i]; // store the old extension (in reverse)
        e++; 

        ret[i] = '\0'; //set current position empty
        i--; 

    }

    free(extension); 

    if( !(0 <= i) ) { //unexpected error

        
        free(ret); //avoid memory leak
        return NULL; 

    }

    return ret; 

}


// Function to handle the input when executing the program.
int processFlags(int argc, char** argv, bool* process_comments, bool* process_directives) { 

    if(argc <= MIN_ARGUMENTS) {
        if(!strcmp(argv[1], "-help")){
            PrintHelp();
            return 0;
        }
        else {
            printf("ERROR: To few arguments. (include file to preprocess)\n");
            printf("Usage: %s {flags} {name of the program to pre-process} \n", argv[0]);
            printf("Use the flag \"-help\" to get help. \n");
        }
        return 1; // return error
    } 
    if(MIN_ARGUMENTS < argc) {
        // handle flags
        /*Note: if the same valid flag is used more than once, the other
        instances will be effectively ignored (according to instructions)*/
        *process_comments = false;
        *process_directives = false;
        int c_flag;
        int d_flag;
        int all_flag;
        int help_flag;
        for (int i = 1; i < argc - 1; i++) {
            //handle flags
            c_flag = strcmp(argv[i], "-c");
            d_flag = strcmp(argv[i], "-d");
            all_flag = strcmp(argv[i], "-all");
            help_flag = strcmp(argv[i], "-help");
            if(!c_flag) {
                *process_comments = true;
            }
            else if(!d_flag) {
                *process_directives = true;
            }
            else if(!help_flag) {
                PrintHelp(); //TODO: fix this (help will be printed multiple times if flag is added more than once)
                return 0;
            }
            else if(!all_flag) {
                *process_comments = true;
                *process_directives = true;
            }
            else {
                //if(c_flag && d_flag && all_flag && help_flag)
                // unexpected flag
                printf("ERROR: unknown flag: \"%s\" \n", argv[i]);
                printf("Use flag -help for additional information.\n");
                return 1;
            }
        }
    }

    //TODO: if no flags are provided, comments flag should be on by deafult

    return 0;
}

// Function to print help for the user
void PrintHelp() {
    printf("\n\n\nUsage: ./preprocessor {flags} {name of the program to pre-process} \n");
    printf("Behaviour of the flags: \n\n");
    printf("\t-c: deletes all comments (// comment and /*comment*/). \n\n");
    printf("\t-d: Replaces all directives starting with # (#define, #include, etc. ). \n\n");
    printf("\t-all: shortcut for \"-c -d\" (uses both flags). \n\n");
    printf("\t-help: display this message. \n\n");

    printf("Using no flags is equivalent to using only the \"-c\" flag. The order of the flags or amount used is irrelevant. using an invalid flag will abort the process. ");
    printf("Keep in mind that the file to preprocess needs to be in the last position. \n\n");

    printf("Note that this preprocessor only supports properly files with .c extension (or other extensions with just 1 letter). Otherwise, the name of the new file may not be properly generated. ");
    printf("After executing the preprocessor, a new file should appear in the same directory as the old one. ");
    printf("If the old file was named \"my_program.c\" then the new file will be named \"my_program_pp.c\". ");

    printf("\n\nIMPORTANT: if there already was a file with the same name, it will be overwritten. Be careful with the files you wish to keep. \n\n");
}

