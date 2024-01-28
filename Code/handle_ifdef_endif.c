#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Ariadna Prat U185150, NIA:251281

char* delete_small_comment(char* texto) {
    static char texto_sin_comentarios[1000]; // Variable to store text without comments
    char *linea = strtok(texto, "\n"); // Split text into lines
    texto_sin_comentarios[0] = '\0'; // Initialize string without comments
    int ifdef_encontrado = 0; // Flag to indicate if #ifdef has been found

    while (linea != NULL) {
        char *comentario_pos = strstr(linea, "//"); // Find start of comment
        if (comentario_pos != NULL && !ifdef_encontrado) {
            *comentario_pos = '\0'; // Terminate string at start of comment
        }
        if (strstr(linea, "#ifdef") != NULL) {
            ifdef_encontrado = 1; // Mark that #ifdef has been found
        }
        if (!ifdef_encontrado) {
            strcat(texto_sin_comentarios, linea); // Add line to text without comments
            strcat(texto_sin_comentarios, "\n"); // Add a new line
        } else {
            strcat(texto_sin_comentarios, linea); // Add line to text without comments
            strcat(texto_sin_comentarios, "\n"); // Add a new line
        }
        linea = strtok(NULL, "\n"); // Get next line
    }
    return texto_sin_comentarios;
}
char* delete_big_comment(const char *cadena) {
    char *resultado = (char *)malloc(strlen(cadena) + 1);
    strcpy(resultado, cadena);

    // Delete comments
    char *posicion = resultado;
    while (1) {
        char *inicio_comentario = strstr(posicion, "/*");
        if (inicio_comentario == NULL)
            break;

        char *fin_comentario = strstr(inicio_comentario + 2, "*/");
        if (fin_comentario == NULL)
            break;

        memmove(inicio_comentario, fin_comentario + 2, strlen(fin_comentario + 2) + 1);
        posicion = inicio_comentario;
    }

    // Delete empty lines
    char *temp = (char *)malloc(strlen(resultado) + 1);
    posicion = resultado;
    char *linea = strtok(posicion, "\n");
    temp[0] = '\0';
    while (linea != NULL) {
        if (strspn(linea, " \t\r") != strlen(linea)) {
            strcat(temp, linea);
            strcat(temp, "\n");
        }
        linea = strtok(NULL, "\n");
    }

    free(resultado);
    return temp;
}

char *handle_ifdef_endif(char *source_code, int index, int *len) {
    // Initialize result
    *len = 0;
    char *result = NULL;

    // Counter to track #ifdef structures index
    int ifdef_index = 0;

    // Find the first occurrence of #ifdef
    char *ifdef_start = strstr(source_code, "#ifdef");
    if (!ifdef_start) {
        return NULL; // No #ifdef-#endif structure found
    }

    // Loop to process each #ifdef-#endif structure
    while (ifdef_start) {
        // If index matches the index of current #ifdef structure, proceed
        if (ifdef_index == index) {
            // Find the end of current #ifdef structure
            char *ifdef_end = strstr(ifdef_start, "#endif");
            if (!ifdef_end) {
                // Current #ifdef-#endif structure is incomplete
                return NULL;
            }

            // Find the string associated with #ifdef
            char ifdef_str[256];
            if (sscanf(ifdef_start, "#ifdef %s", ifdef_str) != 1) {
                // Failed to read name after #ifdef
                return NULL;
            }

            // Find the string associated with #define
            char define_str[256];
            char *define_start = strstr(source_code, "#define");
            while (define_start && define_start < ifdef_end) {
                if (sscanf(define_start, "#define %s", define_str) == 1 && strcmp(ifdef_str, define_str) == 0) {
                    break;
                }
                define_start = strstr(define_start + 1, "#define");
            }
            if (!define_start || define_start >= ifdef_end) {
                // Corresponding #define not found
                return NULL;
            }

            // Calculate the length of current structure
            int block_len = ifdef_end - ifdef_start + strlen("#endif");

            // Reallocate memory for result
            result = (char *)realloc(result, *len + block_len + 1); // +1 for null terminator
            if (!result) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }

            // Copy current structure to result
            strncpy(result + *len, ifdef_start, block_len);
            *len += block_len;
            result[*len] = '\0'; // Add null terminator

            // Structure found and processed, exit loop
            break;
        }

        // Increment #ifdef structures index
        ifdef_index++;

        // Find the next occurrence of #ifdef
        ifdef_start = strstr(ifdef_start + 1, "#ifdef");
    }

    return result;
}
