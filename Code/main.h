#ifndef HEADER_MAIN
#define HEADER_MAIN

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include <memory.h>


#include "handle_backslash.h"
#include "handle_comments.h"
#include "handle_constants.h"
#include "handle_includes.h"
#include "handle_defines.h"
#include "handle_ifdef_endif.h"

#include "preprocessor.h"
#include "patternmatcher.h"
#include "Utils.h"
#include "datastructures.h"




int main(int argc, char** argv);

#endif
