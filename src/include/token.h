//define our tokens that our lexer will use
/*
- numbers
- symbols 
- strings
- operators 
- punctuation
*/

#ifndef TOKEN_H
#define TOKEN_H

//tokens will be of the form (type, value)
typedef struct token {
    //enum for the types of tokens we will be classifying
    enum type {
        //enums start at index 0.
        TOKEN_EQUALS,
        TOKEN_SEMI,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_STRING,
        TOKEN_ID,
        TOKEN_NUM,
        TOKEN_SYM,
        TOKEN_OPR,
        TOKEN_PLUS
    } token_type;
    //value token holds
    char* value;
} token; 

//declare the initializer for the token
token* init_token(int type, char* value);

#endif
