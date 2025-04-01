//file containing definition and declarations of the lexer structure

#include "token.h"
#ifndef LEXER_H
#define LEXER_H

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
token* tokenize_next(lexer* lexer);
//function for how we will tokenize strings
token* tokenize_string(lexer* lexer); 
//continuing on a token (just advancing the lexer and returning our token to prepare for next tokenization)
token* continue_with_token(lexer* lexer, token* token);
//function to get the current lexer char as a string
char* lexer_char_as_string(lexer* lexer);

#endif