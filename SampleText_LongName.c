
char* remove_single_line_comments(char* source_code, size_t* size_source_code); 



/*
Removes all the multiline comments ( /* comment   * /  )


source code is the string of the code to be pre-processed. And size_source_code is the 
length of source_code. remove_multi_line_comments() is now the owner (and responsable) 
of source_code. 

Returns a (possibly new) string and size_source_code is updated to the new size. 

*/

char* remove_multi_line_comments(char* source_code, size_t* size_source_code); 

