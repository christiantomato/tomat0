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
    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_STRING,
    TOKEN_KEYWORD_SOUT,
    TOKEN_ID,
    TOKEN_STRING,
    TOKEN_NEWLINE,
    TOKEN_NUM,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_LPAREN,
    TOKEN_RPAREN, 
    TOKEN_LCHEVRON,
    TOKEN_RCHEVRON,
    TOKEN_FSLASH,
    TOKEN_BSLASH,
    TOKEN_PLUS,
    TOKEN_HYPHEN,
    TOKEN_ASTERIK
} TokenType;

//tokens will be of the form (type, value)
typedef struct token_struct {
    //token type from enum
    TokenType type;
    //the value the token holds
    char* value;
} Token; 

//declare the initializer for the token
Token* init_token(TokenType type, char* value);
//method to get the token type enum name
char* token_type_str(Token* token);
//method to free memory from tokens (good practice)
int free_token(Token* token);
//wrapper for free token so we can free tokens from out parser tokens list
void free_token_wrapper(void* token);

#endif
