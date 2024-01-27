#include "handle_defines.h"


/**
* Handles the processing of a #define line in the source code and returns
 * a DefineInfo structure representing the result.
 *
 * @param source_code The source code containing the #define line.
 * @param index The index of the #define line in the source code.
 * @param len A pointer to an integer that will be updated with the length
 *            of the processed #define line.
 *
 * @return A DefineInfo structure representing the result of the #define line.
 *         If the #define line is successfully processed, the returned
 *         structure contains information about the constant or macro.
 *         If there is an error in processing the #define line, an error
 *         DefineInfo structure is returned with the id field set to -1.
 */
struct DefineInfo handle_define(char* source_code) {

    struct DefineInfo result;
    struct DefineInfo error_result = create_error_result();

    // Find the start of the #define block
    char* define_start = strstr(source_code, "#define");
    if (!define_start) {
        printf("define block not found");
        return error_result;  // No #define found
    }

    // Move the pointer to the character after the 'e' in '#define'
    define_start += strlen("#define");

    //If '#define' is not followed by a " " then it ain't valid
    if (*define_start != ' ') {
        printf("define not followed by a space");
        return error_result;  // Invalid #define, missing space
    }

    // Find the end of the #define line
    char* define_line_end = strchr(define_start, '\n');
    if (!define_line_end) {
        printf("define block end not found");
        return error_result;  // Malformed #define
    }

    // Calculate the length of the content
    size_t content_len = define_line_end - define_start;

    // Allocate memory for the content and copy it
    char* define_content = (char*)malloc(content_len + 1);
    if (!define_content) {
        printf("could not allocate memory");
        return error_result;  // Memory allocation error
    }
    memcpy(define_content, define_start, content_len);
    define_content[content_len] = '\0';  // Null-terminate the string

    // Check if the content contains parentheses, indicating a macro
    if (strchr(define_content, '(') && strchr(define_content, ')')) {
        // It's a macro
        result = defineResult(9, define_content);

    } else {
        // It's a constant
        result = defineResult(8, define_content);
    }

    // Free the allocated memory for define_content
    free(define_content);

    return result;
}

/**
 * Creates and returns a DefineInfo structure based on the provided parameters.
 * The function parses the given source code to extract information about a #define
 * macro or constant. It identifies the #define identifier and separates it from
 * the content.
 *
 * @param id The identifier representing the type of the #define (8 for constants, 9 for macros).
 * @param source_code The source code containing information about the constant or macro.
 *
 * @return A DefineInfo structure representing the constant or macro information.
 *         If there is an error in creating the structure, an error DefineInfo
 *         structure is returned with the id field set to -1.
 */
struct DefineInfo defineResult(int id, char* source_code) {
    struct DefineInfo result;
    struct DefineInfo error_result = create_error_result();

    // Initialize fields
    result.id = id;
    result.identifier = NULL;
    result.content = NULL;

    // Skip leading spaces
    while (*source_code && (*source_code == ' ' || *source_code == '\t')) {
        source_code++;
    }

    // Find the first letter corresponding to the macro name (identifier)
    if (*source_code && ((*source_code >= 'A' && *source_code <= 'Z') ||
                         (*source_code >= 'a' && *source_code <= 'z') ||
                         *source_code == '_')) {
        char* identifier_start = source_code;

        // Macro names in C can contain uppercases, lowercases, numbers, and underscores
        while (*source_code && ((*source_code >= 'A' && *source_code <= 'Z') ||
                                (*source_code >= 'a' && *source_code <= 'z') ||
                                (*source_code >= '0' && *source_code <= '9') ||
                                *source_code == '_')) {
            source_code++;
        }

        // Allocate and copy the identifier
        size_t identifier_len = source_code - identifier_start;
        result.identifier = (char*)malloc(identifier_len + 1);
        if (!result.identifier) {
            // Handle memory allocation failure
            return error_result;
        }
        strncpy(result.identifier, identifier_start, identifier_len);
        result.identifier[identifier_len] = '\0';  // Null-terminate the identifier

        // Skip leading spaces after the identifier
        while (*source_code && (*source_code == ' ' || *source_code == '\t')) {
            source_code++;
        }

        // Copy the rest as parameters and logic
        result.content = strdup(source_code);
        if (!result.content) {
            // Handle memory allocation failure
            free(result.identifier);  // Free the allocated memory for identifier
            return error_result;
        }
    }

    return result;
}


/**
 * Creates and returns a special DefineInfo structure indicating an error condition.
 * This function is useful for signaling errors in functions that return DefineInfo structures.
 *
 * @return A DefineInfo structure initialized to represent an error.
 */
struct DefineInfo create_error_result() {
    struct DefineInfo error_result;    

    // Set the id to a special value indicating an error
    error_result.id = -1;
    error_result.identifier = NULL;
    error_result.content = NULL;

    return error_result;
}
