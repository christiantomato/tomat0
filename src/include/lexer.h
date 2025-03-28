//this file contains our definition for the lexer structure
#ifndef LEXER_H
#define LEXER_H
//include our token definition
#include "token.h"
//declarations for the lexer

//struct to store current state of lexer
typedef struct lexer {
    //current char
    char c;
    //index, acting as the cursor through contents
    unsigned int i;
    //the code we are going to do lexical analysis on
    char* contents;
} lexer;

//functions

//lexer initializor
lexer* init_lexer(char* contents);
//move to the next character
void advance(lexer* lexer);
//to skip whitespace
void skip_whitespace(lexer* lexer);
//to get the next token
token* get_next_token(lexer* lexer);
//function for how we will tokenize strings
token* tokenize_string(lexer* lexer); 
//continuing on a token (like a string or long number)
token* continue_with_token(lexer* lexer, token* token);
//function to get the current char as a char[]
char* get_current_char_as_string(lexer* lexer);

#endif