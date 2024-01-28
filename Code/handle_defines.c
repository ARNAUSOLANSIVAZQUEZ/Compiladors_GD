/*
* Compilers
* Practice 1: c pre-processor
* File name: handle_defines.c
* Define directive handler.
*
*
* Responsible: Claudia Quera & David Garcia
*/
#include "handle_defines.h"


 /* Example main to demonstrate calling handle_define with a predefined #define line
 * and adding the result to the table which will contain defines relations to substitute
 * the values when a pattern matcher of a define variable is encountered.
 */

/*int main()
{
    // Define the number of rows in your table
    int num_rows = TABLE_ROWS;
    // Allocate memory for an array of struct DefineInfo
    struct DefineInfo* table = (struct DefineInfo*)malloc(num_rows * sizeof(struct DefineInfo));
    
    // Create an error result structure
    struct DefineInfo error_result = create_error_result();
    
    // Example: Call handle_define with a predefined #define line
    struct DefineInfo result = handle_define("#define max(x,y) (x>y?x:y)\n");
    
    // Check if the result is not an error
    if (result.id != error_result.id) {
        // Check if an entry with the same ID and identifier already exists
        if (entryExists(table, num_rows, result.id, result.identifier)) {
            // If exists, update the table entry
            updateTable(table, num_rows, result);
        } else {
            // If not exists, add a new entry to the table
            addToTable(table, num_rows, result);
        }
    }
    
    printTable(table, num_rows);
    return 0;
}
*/

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
        // If newline character is not found, check for the end of the string
        define_line_end = strchr(define_start, '\0');
        if (!define_line_end) {
            printf("define block end not found");
            return error_result;  // Malformed #define
        }
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


char* extractDefineLine(const char* buffer, size_t defineIndex) {
    // Find the start of the line containing #define
    size_t start = defineIndex;
    while (start > 0 && buffer[start - 1] != '\n') {
        start--;
    }

    // Find the end of the line containing #define
    size_t end = defineIndex;
    while (buffer[end] != '\n' && buffer[end] != '\0') {
        end++;
    }

    // Calculate the length of the line
    size_t lineLength = end - start;

    // Allocate memory for the line
    char* defineLine = (char*)malloc((lineLength + 1) * sizeof(char));

    // Copy the line to the allocated memory
    strncpy(defineLine, buffer + start, lineLength);
   
    // Null-terminate the string
    defineLine[lineLength] = '\0';
    return defineLine;
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


/**
 * Check if an entry with the same ID and identifier already exists in the table.
 *
 * @param table The table of DefineInfo structures.
 * @param num_rows The number of rows in the table.
 * @param id The ID to check for.
 * @param identifier The identifier to check for.
 * @return true if an entry with the same ID and identifier exists, false otherwise.
 */
bool entryExists(struct DefineInfo* table, int num_rows, int id, const char* identifier) {
    for (int i = 0; i < num_rows; ++i) {
        if (table[i].id == id && strcmp(table[i].identifier, identifier) == 0) {
            return true;  // Entry already exists
        }
    }
    return false;  // Entry not found
}

/**
 * Add entries to the table.
 *
 * @param table The table of DefineInfo structures.
 * @param num_rows The number of rows in the table.
 * @param result The DefineInfo structure to add to the table.
 */
struct DefineInfo* addToTable(struct DefineInfo* table, int num_rows, struct DefineInfo result, PatternMatcher* patternMatcher) {
    //char* define_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    for (int i = 0; i < num_rows; ++i) {
        if (table[i].id == 0 && table[i].identifier == NULL) {
            // Empty slot, add the result

            // Allocate memory for the identifier and copy the value
            table[i].identifier = strdup(result.identifier);
            if (!table[i].identifier) {
                // Handle memory allocation failure
                return table;
            }

            // Allocate memory for the content and copy the value
            table[i].content = strdup(result.content);
            if (!table[i].content) {
                // Handle memory allocation failure
                free(table[i].identifier);  // Free the allocated memory for identifier
                return table;
            }

            // Update the id and exit the loop
            table[i].id = result.id;
            //strcpy(define_pattern, table[i].identifier);
            //add_pattern(patternMatcher, define_pattern, table[i].id);
            return table;
        }
    }
    return table;
    // If the table is full, allocate more space (+TABLE_ROWS)
    int new_size = num_rows + TABLE_ROWS;
    table = (struct DefineInfo*)realloc(table, new_size * sizeof(struct DefineInfo));
    if (!table) {
        // Handle memory allocation failure
        return;
    }

    // Initialize the new entries in the added space
    for (int i = num_rows; i < new_size; ++i) {
        table[i].id = 0;
        table[i].identifier = NULL;
        table[i].content = NULL;
    }

    // Update the num_rows variable to reflect the new size
    num_rows = new_size;

    // Add the result to the newly allocated space
    addToTable(table, num_rows, result, patternMatcher);
}


/**
 * Update an entry in the table.
 *
 * @param table The table of DefineInfo structures.
 * @param num_rows The number of rows in the table.
 * @param result The DefineInfo structure containing the update information.
 */
void updateTable(struct DefineInfo* table, int num_rows, struct DefineInfo result, PatternMatcher* patternMatcher) {
    //char* define_pattern = (char*)malloc(BASIC_PATTERN_STR_LEN * sizeof(char));
    for (int i = 0; i < num_rows; ++i) {
        if (table[i].id == result.id && strcmp(table[i].identifier, result.identifier) == 0){
            // Entry with the same ID and identifier found, update the content
            free(table[i].content);  // Free the existing content
            table[i].content = result.content;
            //strcpy(define_pattern, table[i].identifier);
            //add_pattern(patternMatcher, define_pattern, DEFINE_ID);
            return;  // Entry updated, exit the function
        }
    }
}

/**
 * Print the contents of the table.
 *
 * @param table The table of DefineInfo structures.
 * @param num_rows The number of rows in the table.
 */
void printTable(struct DefineInfo* table, int num_rows) {
    printf("Table Contents:\n");

    for (int i = 0; i < num_rows; ++i) {
        if (table[i].id != 0 && table[i].identifier != NULL) {
            printf("| Id:%d | Identifier: %s | Content: %s |\n", table[i].id, table[i].identifier, table[i].content);
        }
    }
    
}
