#include <stdlib.h>
#include <stdio.h>


/*
    Escriviu aquí els vostres noms, U i NIA per si acas: 



    Marcel Aranich, U185166, NIA: 251453
    Ariadna Prat, U15150, NIA:251281


*/

#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)

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

        if(fread_return != file_length_bytes) { // handle error
            printf("ERROR: error while reading file. fread return: %d", fread_return); 
            fclose(source_file); 
            return 1; 
        }
    }
    fclose(source_file); // no need to keep file open

    //call every function to preprocess: 

    //file_contents = 




    free(file_contents); 

}
