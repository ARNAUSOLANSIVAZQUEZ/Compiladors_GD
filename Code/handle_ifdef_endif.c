/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_ifdef_endif.c
* Ifdef directive handler.
*
*
* Responsible: Ariadna Prat
*/
#include "handle_ifdef_endif.h"
char *handle_ifdef_endif(char *source_code, int index, int *len, MultiString *ms) {
    // Initialize result
    *len = 0;
    char *result = NULL;

    // Counter to track #ifdef structures index
    int ifdef_index = 0;

    // Find the first occurrence of #ifdef starting from the given index
    char *search_start = source_code + index;
    char *ifdef_start = strstr(search_start, "#ifdef");
    if (!ifdef_start) {
        printf("No se encontró ningún bloque #ifdef-#endif.\n");
        return NULL; // No #ifdef-#endif structure found
    }

    // Loop to process each #ifdef-#endif structure
        // If index matches the index of current #ifdef structure, proceed
        if (ifdef_index == index) {
            //printf("Encontrado bloque #ifdef-#endif en el índice %d.\n", index);

            // Find the end of current #ifdef structure
            char *ifdef_end = strstr(ifdef_start, "#endif");
            if (!ifdef_end) {
                printf("Bloque #ifdef-#endif incompleto.\n");
                return NULL; // Current #ifdef-#endif structure is incomplete
            }

            // Find the beginning of the content inside #ifdef
            char *content_start = ifdef_start;
            while (*content_start != '\n' && content_start < ifdef_end) {
                content_start++;
            }
            content_start++; // Move past the newline character

            // Find the string associated with #ifdef
            char ifdef_str[256];
            if (sscanf(ifdef_start, "#ifdef %s", ifdef_str) != 1) {
                printf("Error al leer el nombre después de #ifdef.\n");
                return NULL; // Failed to read name after #ifdef
            }
            //printf("Nombre después de #ifdef: %s\n", ifdef_str);

            // Check if the string associated with #ifdef is already present in MultiString
            if (!multistring_contains(ms, ifdef_str)) {
                // Add the string associated with #ifdef to MultiString
                add_string(ms, strdup(ifdef_str));
            } else {
                // String already present, return NULL
                printf("La cadena asociada con #ifdef ya está presente.\n");
                return NULL;
            }

            // Calculate the length of content inside #ifdef
            int content_len = ifdef_end - content_start;

            // Allocate memory for result
            result = (char *)malloc((content_len + 1) * sizeof(char)); // +1 for null terminator
            if (!result) {
                perror("Error de asignación de memoria");
                exit(EXIT_FAILURE);
            }

            // Copy content inside #ifdef to result
            strncpy(result, content_start, content_len);
            result[content_len] = '\0'; // Add null terminator
            //printf("Contenido dentro del bloque #ifdef-#endif [PRIMERO]: %s\n", result);

            // Update length
            *len = content_len;

            // Structure found and processed, exit loop

        // Increment #ifdef structures index
        ifdef_index++;

        // Find the next occurrence of #ifdef
        ifdef_start = strstr(ifdef_start + 1, "#ifdef");
    }

    return result;
}
void pre_handle_ifdef_endif(char* reading_buffer, int i, char* writing_buffer, size_t* writing_buffer_len, int* writing_index, MultiString* ms){
    int len = -1;
    char *if_def_text = handle_ifdef_endif (reading_buffer, i, &len, ms);
    //^should return directly what needs to be inserted in the writing buffer

    if(writing_buffer_len <= writing_index + len + 1 ) { // +1 for /0
    // get more space
    writing_buffer_len = (int)writing_buffer_len * ARRAY_GROWTH_FACTOR;
    writing_buffer = realloc(writing_buffer, writing_buffer_len);
    }
    if(*writing_buffer_len <= *writing_index + len + 1 ) { // +1 for /0
        // get more space
        *writing_buffer_len = *writing_buffer_len * ARRAY_GROWTH_FACTOR;
        *writing_buffer = realloc(*writing_buffer, *writing_buffer_len);
    }

    memcpy(&writing_buffer[(int)writing_index - 5], if_def_text, (size_t)len);
    writing_index += -5 + len - 1;
}
