
#include <stdio.h>



char* handle_ifdef_endif(char* source_code, size_t* size_source_code) {
    char *encontrado_ifdef = strstr(source_code, "#ifdef");
    while (encontrado_ifdef != NULL) {
        // Calculate the position of the world "#ifdef" of the string
        int posicion = encontrado_ifdef - source_code;

        // Replace "#ifdef" per "//ifdef"
        strncpy(source_code + posicion, "//ifdef", 7);

        // Search the next concurrency of "#ifdef"
        encontrado_ifdef = strstr(source_code, "#ifdef");
    }

    // Search and replace the word "#endif" per "//endif"
    char *encontrado_endif = strstr(source_code, "#endif");
    while (encontrado_endif != NULL) {
        // Calculate the position of the word "#endif" of the string
        int posicion = encontrado_endif - source_code;

        // Replace "#endif" per "//endif"
        strncpy(source_code + posicion, "//endif", 7);

        // Search the next string "#endif"
        encontrado_endif = strstr(source_code, "#endif");
    }

    printf("Cadena modificada:\n%s\n", source_code);
    return source_code;
}
