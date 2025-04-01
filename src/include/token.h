//define our tokens that our lexer will use
/*
- numbers
- symbols 
- strings
- operators 
- punctuation
etc.
*/

#ifndef TOKEN_H
#define TOKEN_H

//enum for the types of tokens we will be classifying
typedef enum token_type {
    //enums start at index 0.
    TOKEN_ID,
    TOKEN_STRING,
    TOKEN_NUM,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN, 
    TOKEN_ADD,
    TOKEN_HYPHEN,
    TOKEN_COLON
} type;

//tokens will be of the form (type, value)
typedef struct token {
    //token type
    int type;
    //value token holds
    char* value;
} token; 

//declare the initializer for the token
token* init_token(int type, char* value);
//method to get the actual enum name which is helpful
char* token_type_str(token* token);

#endif
