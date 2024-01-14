#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Ariadna Prat U185150, NIA:251281

char* handle_ifdef_endif(char* source_code, size_t* size_source_code) {
    //We create an output_code with the same memory
    char *outputCode = (char *)malloc(strlen(source_code) * sizeof(char));

    // Tokenize the source code by lines
    char *line = strtok((char *)source_code, "\n");

    //We create a while where we detect the string "#define <str>" and "#ifdef <str>".
    while (line != NULL) {
        // Check if the line contains #define
        if (strncmp(line, "#ifdef", 6) == 0) {
            //We detect #ifdef <str> where str is a word.
            while (line != NULL) {
                if (strncmp(line, "#define", 7) == 0) {
                    //We detect #define <str> where str is a word.
                } else if (strncmp(line, "#endif", 6) == 0) {
                    //If exists #endif we compare the two <str>.
                    //If we get the following four conditions: 
                        //Exists #define <str>1
                        //Exists #ifdef <str>2
                        //<str>1 and <str>2 are the same.
                        //Exists #endif
                    //We put the structure ifdef-endif in the output version, otherwise not.
                }
                // Move to the next line
                line = strtok(NULL, "\n");
            }
        }else{
            //we keep the string in the output version.
        }
        // Move to the next line
        line = strtok(NULL, "\n");
    }

    return source_code;
}
