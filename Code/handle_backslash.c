
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
char* handle_backslash(char* source_code, size_t* size_source_code) {
    char *result = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    // Copy input to result
    strcpy(result, source_code);
    
    // Find the slash character
    char *slash = strrchr(result, '/');
    
    // If slash is found, remove it and concatenate the next line
    if (slash != NULL) {
        *slash = '\0'; // Replace slash with null terminator
        char nextLine[MAX_LINE_LENGTH];
        printf("Enter continuation line: ");
        fgets(nextLine, sizeof(nextLine), stdin); // Read next line
        strcat(result, nextLine); // Concatenate next line
        // Recursively process the next line
        char *processed = handle_backslash(result, size_source_code);
        free(result);
        *size_source_code = strlen(processed); // Calculate length
        return processed;
    } else {
        *size_source_code = strlen(result); // Calculate length
        return result; // Return the processed line if no slash found
    } 
}
