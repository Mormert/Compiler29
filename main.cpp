/* main.c */

#include "global.h"
#include "fstream"
#include <iostream>

int main(void)
{
    init();

    sourceCode = fopen("source.code", "r");

    if(sourceCode == NULL){
        std::cout << "source.code file not found!\n";
        exit(1);
    }

    printf("\nSource code:\n------------------------\n");
    int ch;
    do {
        ch = fgetc(sourceCode);
        if(ch > 0)
            printf("%c", ch);
    } while (ch != EOF);
    printf("\n------------------------\n\n");

    rewind(sourceCode);

    parse();
}
