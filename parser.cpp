/* parser.c -- without the optimizations */

#include <cmath>
#include "global.h"

#include <stack>

std::stack<int> stack{};
int lookahead;

void match(int);
void assignment(), start(), list(), expr(), moreterms(), term(), morefactors(), factor();

void parse()  /*  parses and translates expression list  */
{
    lookahead = lexan();
    start();
}

void start ()
{
    /* Just one production for start, so we don't need to check lookahead */
    list(); match(DONE);
}

void assignment()
{
    int id_number = token_value;
    match(ID);
    emit(ID, id_number);
    match('=');
    expr();
    emit('=', id_number);
}

void list()
{
    if (lookahead == '(' || lookahead == ID || lookahead == NUM) {
        assignment(); match(';'); list();
    }
    else {
        /* Empty */
    }
}

void expr ()
{
    /* Just one production for expr, so we don't need to check lookahead */
    term(); moreterms();
}

void moreterms()
{
    if (lookahead == '+') {
        match('+'); term(); emit('+', token_value); moreterms();
    }
    else if (lookahead == '-') {
        match('-'); term(); emit('-', token_value); moreterms();
    }
    else {
        /* Empty */
    }
}

void term ()
{
    /* Just one production for term, so we don't need to check lookahead */
    factor(); morefactors();
}

void morefactors ()
{
    if (lookahead == '*') {
        match('*'); factor(); emit('*', token_value); morefactors();
    }
    else if (lookahead == '/') {
        match('/'); factor(); emit('/', token_value); morefactors();
    }
    else if (lookahead == DIV) {
        match(DIV); factor(); emit(DIV, token_value); morefactors();
    }
    else if (lookahead == MOD) {
        match(MOD); factor(); emit(MOD, token_value); morefactors();
    }
    else if (lookahead == '^') {
        match('^'); factor(); emit('^', token_value); morefactors();
    }
    else {
        /* Empty */
    }
}

void exparg(){
    if (lookahead == '(') {
        match('('); expr(); match(')');
    }
    else if (lookahead == ID) {
        int id_number = token_value;
        match(ID);
        emit(ID, id_number);
    }
    else if (lookahead == NUM) {
        int num_value = token_value;
        match(NUM);
        emit(NUM, num_value);
    }
    else
        error("syntax error in exparg");
}

void moreexpargs(){
    if(lookahead == '^'){
        match('^');
        exparg();
        emit('^', token_value);
        moreexpargs();
    }else{
        // Nothing
    }


}

void factor ()
{
    exparg(); moreexpargs();
}

void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error ("syntax error in match");
}

void emit (int token_type, int token_value)  /*  generates output  */
{
    int a, b;
    switch(token_type) {
        case '+':
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(a+b);
            printf("%c\n", token_type); break;
        case '-':
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(b-a);
            printf("%c\n", token_type); break;
        case '*':
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(a*b);
            printf("%c\n", token_type); break;
        case '/':
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(b/a);
            printf("%c\n", token_type); break;
        case '=':
            symtable[token_value].value = stack.top(); stack.pop();
            printf("%c\n", token_type);
            printf("Assigned '%s' to %d\n", symtable[token_value].lexeme, symtable[token_value].value);
            break;
        case '^':
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(pow(b,a));
            printf("^\n"); break;
        case DIV:
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(b/a);
            printf("DIV\n"); break;
        case MOD:
            a = stack.top(); stack.pop();
            b = stack.top(); stack.pop();
            stack.push(b % a);
            printf("MOD\n"); break;
        case NUM:
            stack.push(token_value);
            printf("%d\n", token_value); break;
        case ID:
            stack.push(symtable[token_value].value);
            printf("%s (%d)\n", symtable[token_value].lexeme, symtable[token_value].value); break;
        default:
            printf("[Unknown token %d, with value %d]\n", token_type, token_value);
    }
}