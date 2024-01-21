#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char*** handle_macro(char* source_code);

int main() {
    char*** result = handle_macro("#define AREA_CIRCLE(r, x, y) (3.14*r*r)");

    // Print or use the result as needed
    if (result != NULL) {
        printf("Identifier: %s\n", result[0][0]);

        // Print parameters if available
        if (result[1] != NULL) {
            for (int i = 1; result[1][i] != NULL; i++) {
                printf("Parameter %d: %s\n", i, result[1][i]);
                free(result[1][i]); // Free parameter memory
            }
            free(result[1]); // Free the array itself
        }

        // Print content if available
        if (result[2] != NULL) {
            printf("Content: %s\n", result[2][0]);
            free(result[2][0]); // Free content memory
        }

        // Free the result memory
        free(result);
    } else {
        printf("Macro not found or malformed.\n");
    }

    return 0;
}

char*** handle_macro(char* source_code) {
    char*** result = (char***)malloc(3 * sizeof(char**));
    
    // Initialize arrays
    result[0] = NULL;  // Identifier
    result[1] = NULL;  // Parameters
    result[2] = NULL;  // Content

    // Define start
    char* define_start = strstr(source_code, "#define");

    if (!define_start) {
        // No #define found, return default result
        return result;
    }

    // Move past "#define"
    char* macro_start = define_start + strlen("#define");

    // Skip spaces
    while (isspace((unsigned char)*macro_start)) {
        macro_start++;
    }
    char* identifier_start = macro_start;
    while (*macro_start != '(' && *macro_start != '\0') {
        macro_start++;
    }

    // Calculate the length of the identifier
    size_t identifier_length = macro_start - identifier_start;

    // Allocate memory for the identifier and copy its content
    result[0] = (char**)malloc(2 * sizeof(char*));
    result[0][0] = (char*)malloc((identifier_length + 1) * sizeof(char));
    strncpy(result[0][0], identifier_start, identifier_length);
    result[0][0][identifier_length] = '\0';  // Null-terminate the string

    // Skip spaces and move to the opening parenthesis '('
    while (*macro_start != '(' && *macro_start != '\0') {
        macro_start++;
    }

    // Check if '(' is found
    if (*macro_start == '(') {
        macro_start++;  // Move past '('

        // Find the end of the parameters (')')
        char* parameters_start = macro_start;
        while (*macro_start != ')' && *macro_start != '\0') {
            macro_start++;
        }

        // Calculate the length of the parameters
        size_t parameters_length = macro_start - parameters_start;

        // Allocate memory for the parameters and copy their content
        result[1] = (char**)malloc(2 * sizeof(char*));
        result[1][0] = (char*)malloc((parameters_length + 1) * sizeof(char));
        strncpy(result[1][0], parameters_start, parameters_length);
        result[1][0][parameters_length] = '\0';  // Null-terminate the string

        // Tokenize parameters based on comma ',' separator
        int parameter_count = 0;

        char* token = strtok(result[1][0], ",");
        while (token != NULL) {
            // Store each parameter in the array
            result[1] = realloc(result[1], (parameter_count + 2) * sizeof(char*));
            result[1][parameter_count + 1] = (char*)malloc((strlen(token) + 1) * sizeof(char));
            strcpy(result[1][parameter_count + 1], token);
            parameter_count++;

            token = strtok(NULL, ",");
        }

        // Skip spaces and move to the opening parenthesis '('
        while (*macro_start != '(' && *macro_start != '\0') {
            macro_start++;
        }

        // Check if '(' is found
        if (*macro_start == '(') {
            macro_start++;  // Move past '('

            // Find the end of the macro content (')')
            char* content_start = macro_start;
            while (*macro_start != ')' && *macro_start != '\0') {
                macro_start++;
            }

            // Calculate the length of the content
            size_t content_length = macro_start - content_start;

            // Allocate memory for the content and copy its content
            result[2] = (char**)malloc(2 * sizeof(char*));
            result[2][0] = (char*)malloc((content_length + 1) * sizeof(char));
            strncpy(result[2][0], content_start, content_length);
            result[2][0][content_length] = '\0';  // Null-terminate the string
        }
    }

    return result;
}
