/* lexer.c */

#include "global.h"

char lexeme[MAX_ID_LENGTH + 1];
int  lineno = 1;
int  token_value = NONE;

int lexan()  /*  lexical analyzer  */
{
    int c;
    while(1) {
        c = getchar();
        if (c == ' ' || c == '\t')
            ;  /*  strip out white space  */
        else if (c == '\n')
            lineno = lineno + 1;
        else if (isdigit(c)) {  /*  c is a digit  */
            ungetc(c, stdin);
            scanf("%d", &token_value);
            yylval.i = token_value; // <--- Don't forget to set yylval!!!
            return NUM;
        }
        else if (isalpha(c)) {  /*  c is a letter */
            int id_number, chars = 0;
            while (isalnum(c)) {  /* c is alphanumeric  */
                lexeme[chars++] = c; 
                if (chars > MAX_ID_LENGTH)
                    error("identifier too long");
                c = getchar();
            }
            lexeme[chars] = EOS;
            if (c != EOF)
                ungetc(c, stdin);

            if(strcmp(lexeme, "while") == 0){
                return WHILE;
            }
            if(strcmp(lexeme, "if") == 0){
                return IF;
            }
            if(strcmp(lexeme, "else") == 0){
                return ELSE;
            }
            if(strcmp(lexeme, "print") == 0){
                return PRINT;
            }
            if(strcmp(lexeme, "read") == 0){
                return READ;
            }

            id_number = lookup(lexeme);
            if (id_number == -1)
                id_number = insert(lexeme, ID);
            token_value = id_number;
            yylval.i = id_number; // <--- Don't forget to set yylval!!!
            return ID;
        }
        else if (c == EOF)
            return DONE;
        else {
            token_value = NONE;
            return c;
        }
    }
}
