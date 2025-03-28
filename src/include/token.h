//define our toxens that the lexer will use
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
    //enum for the types of tokens
    enum type {
        //enums start at index 0.
        TOKEN_ID,
        TOKEN_NUM,
        TOKEN_SYM,
        TOKEN_STR,
        TOKEN_OPR,
        TOKEN_EQUALS,
        TOKEN_PLUS,
        //punctuation special tokens
        TOKEN_SEMI,
        TOKEN_LPAREN,
        TOKEN_RPAREN
    } token_type;
    //value
    char* value;
} token; 

//declare the initializer for the token
token* init_token(int type, char* value);

#endif
