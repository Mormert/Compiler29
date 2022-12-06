/* main.c */

#include "global.h"

int main(void)
{
    init();
    // printf("%d\n", yyparse());
    // lexan();
    parse();

    exit(0);    /*  successful termination  */
}
