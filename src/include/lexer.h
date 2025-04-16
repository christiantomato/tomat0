//file containing definition and declarations of the lexer structure

#include "token.h"

#ifndef LEXER_H
#define LEXER_H

//struct to store current state of lexer
typedef struct lexer_struct {
    //current char
    char c;
    //index, acting as the cursor through contents
    unsigned int i;
    //the code we are going to do lexical analysis on
    char* contents;
} Lexer;

//lexer methods

//lexer initializor
Lexer* init_lexer(char* contents);
//move to the next character
void lexer_advance(Lexer* lexer);
//to skip whitespace
void skip_whitespace(Lexer* lexer);
//to get the next token
Token* tokenize_next(Lexer* lexer);
//method for how we will tokenize strings
Token* tokenize_string(Lexer* lexer); 
//method to tokenize words, like variables and keywords (but not strings!)
Token* tokenize_ID(Lexer* lexer);
//method to tokenize numbers
Token* tokenize_number(Lexer* lexer);
//continuing on a token (just advancing the lexer and returning our token to prepare for next tokenization)
Token* continue_with_token(Lexer* lexer, Token* token);
//method to get the current lexer char as a string
char* lexer_char_as_string(Lexer* lexer);
//final method to free memory from the lexer! (this is good practice)
int free_lexer(Lexer* lexer);

#endif
