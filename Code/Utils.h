#ifndef UTILS
#define UTILS

#include <stdio.h>




/*
Returns the contents of the file located in directory. If an error happens, GetFileContents()
will return NULL. size_sorce_code is an out value and may be anything; it will be overwritted
to the size of the source code. 
*/
char* GetFileContents(char* directory, size_t* size_source_code); 









#endif