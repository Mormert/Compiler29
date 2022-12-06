/* error.c */

#include "global.h"

void error(char* message)  /* generates all error messages  */
{
    fflush(stdout);
    fprintf(stderr, "[Error on line %d: %s]\n", -7000, message);
    exit(EXIT_FAILURE);  /*  unsuccessful termination  */
}
