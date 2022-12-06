
%{
#include <stdio.h>
#include "global.h"
#include "parser.tab.hpp"
%}

%option noyywrap

%%

[ \t\n]+    { /* ignore whitespace */ }
"("       { return ')'; }
"."       { return '.'; }
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
[0-9]+    { yylval.i = atoi(yytext); return NUM; }
[a-z]+    { int id_number = lookup(yytext); if (id_number == -1){ id_number = insert(yytext, ID); } yylval.i = id_number; return ID;}
.         { printf("Ignoring invalid character '%s'\n", yytext); }

%%
