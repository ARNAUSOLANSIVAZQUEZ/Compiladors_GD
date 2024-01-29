#ifndef HEADER_MAIN
#define HEADER_MAIN

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>
#include <stddef.h>
#include "multistring.h"
#include "preprocessor.h"


#define BASIC_CAPACITY 5
#define ARRAY_GROWTH_FACTOR 3/2
#define INCLUDE_FILE_PATTERN_DETECTION_LEN 9
#define TABLE_ROWS 5
#define ARRAY_GROWTH_FACTOR 3/2
#define MAX_LENGTH_INCLUDE 100 //the max length of #incude<{HERE}>
#define MIN_ARGUMENTS 2 // Minimum arguments to properly execute the preprocessor
#define BYTES_TO_MB_CONVERSION_FACTOR 1/1048576  // (1/1024**2 = 2**-20)
#define BASIC_PATTERN_STR_LEN 20


int main(int argc, char** argv);

#endif
