/* main.c */

#include "global.h"

int main(void)
{
    init();
    printf("%d\n", yyparse());
    // lexan();
    exit(0);    /*  successful termination  */
}
