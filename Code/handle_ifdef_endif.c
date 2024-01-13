
#include <stdio.h>



char* handle_ifdef_endif(char* source_code, size_t* size_source_code) {
    char *encontrado_ifdef = strstr(source_code, "#ifdef");

    printf("Cadena modificada:\n%s\n", source_code);
    return source_code;
}
