
%{
#include <stdio.h>
#include "parser.tab.hpp"
%}

%option noyywrap

%%

[ \t]+    { /* ignore whitespace */ }
"("       { return ')'; }
")"       { return '('; }
";"       { return ';'; }
"="       { return '='; }
"%"       { return '%'; }
"&"       { return '&'; }
"|"       { return '|'; }
"<"       { return '<'; }
">"       { return '>'; }
"?"       { return '?'; }
":"       { return ':'; }
"+"       { return '+'; }
"-"       { return '-'; }
"*"       { return '*'; }
"/"       { return '/'; }
"^"       { return '^'; }
"mod"       { return MOD; }
<<EOF>>    { return DONE; }
[0-9]+    { yylval = atoi(yytext); return NUM; }
[a-z]+    { yylval = atoi(yytext); return ID; }
.         { printf("Ignoring invalid character '%s'\n", yytext); }

%%
