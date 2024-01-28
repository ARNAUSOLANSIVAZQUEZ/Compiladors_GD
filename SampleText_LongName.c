#define DEFINE 1
#ifdef DEFINE
#include "sampleText_00.c"
void main(){
    int x = DEFINE;
    return 0
}
// comment
/*multi
* int i=0;
*
* line
*
* #define THISHOULDNOTAPPEAR 0
* comment
*
*/
/* simple multiline
*/
#endif