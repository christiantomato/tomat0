//implement the token
#include "include/token.h"
#include <stdlib.h>

//token initializor
Token* init_token(TokenType type, char* value) {
    //allocate space for the token
    Token* token = malloc(sizeof(Token));
    //set the values to what we passed in
    token->type = type;
    token->value = value;
    //return created token
    return token;  
}

//get the token type as a string
char* token_type_str(Token* token) {
    //switch on the token type
    switch(token->type) {
        case TOKEN_KEYWORD_INT: return "TOKEN_KEYWORD_INT"; break;
        case TOKEN_KEYWORD_STRING: return "TOKEN_KEYWORD_STRING"; break;
        case TOKEN_KEYWORD_SOUT: return "TOKEN_KEYWORD_SOUT"; break;
        case TOKEN_ID: return "TOKEN_ID"; break;
        case TOKEN_STRING: return "TOKEN_STRING"; break;
        case TOKEN_NEWLINE: return "TOKEN_NEWLINE"; break;
        case TOKEN_NUM: return "TOKEN_NUM"; break;
        case TOKEN_EQUALS: return "TOKEN_EQUALS"; break;
        case TOKEN_SEMI: return "TOKEN_SEMI"; break;
        case TOKEN_LPAREN: return "TOKEN_LPAREN"; break;
        case TOKEN_RPAREN: return "TOKEN_RPAREN"; break;
        case TOKEN_FSLASH: return "TOKEN_FSLASH"; break;
        case TOKEN_BSLASH: return "TOKEN_BSLASH"; break;
        case TOKEN_PLUS: return "TOKEN_PLUS"; break;
        case TOKEN_HYPHEN: return "TOKEN_HYPHEN"; break;
        case TOKEN_ASTERIK: return "TOKEN_ASTERIK"; break;
    }
}

//free memory
int free_token(Token* token) {
    if(token == NULL) {
        //failure
        return 1;
    }
    //free token value
    free(token->value);
    //then free token
    free(token);
    //success
    return 0;
}

//wrapper for free token
void free_token_wrapper(void* token) {
    free_token((Token*) token);
}
