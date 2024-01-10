#include <stdlib.h>
#include <stdio.h>


/*
    Escriviu aquí els vostres noms, U i NIA per si acas: 



    Marcel Aranich, U185166, NIA: 251453


*/

int main(int argc, char** argv) {

    printf("Test"); 

    // argv[1] is the file to pre-process

    if(argc < 2) {
        printf("ERROR: To few arguments. (incude file to preprocess)"); 
        printf("Usage: %s ./{name of the program to pre-process} -{flags}", argv[0]); 
        return 1; // return error
    }
    

    FILE* source_file = fopen(argv[1], 'r'); // we cannot modify original file

    if(source_file == NULL) {
        printf("ERROR: Could not open file: %s", argv[1]); 
    }

    // TODO: copy contents of file in main memory. 

    int file_length_bytes = -1; //TODO: 
    char* file_contents = (char*)malloc(file_length_bytes); 

    //copy contents

    //call every function to preprocess: 


    free(file_contents); 
    fclose(source_file); 

}
