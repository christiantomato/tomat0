//implement the token
#include "include/token.h"
#include <stdlib.h>
#include <stdio.h>

//token initialization
token* init_token(int type, char* value) {
    //allocate space for the token
    token* my_token = malloc(sizeof(token));
    //make sure memory allocation went well
    if(my_token != NULL) {
        //set the values to what we passed in
        my_token->type = type;
        my_token->value = value;
        //return created token
        return my_token;
    }
    else {
        //something went wrong
        printf("error in allocation");
        return NULL;
    }
}

//get the token type as a string
char* token_type_str(token* token) {
    //switch on the token type
    switch(token->type) {
        case TOKEN_ID: return "TOKEN_ID"; break;
        case TOKEN_STRING: return "TOKEN_STRING"; break;
        case TOKEN_NUM: return "TOKEN_NUM"; break;
        case TOKEN_EQUALS: return "TOKEN_EQUALS"; break;
        case TOKEN_SEMI: return "TOKEN_SEMI"; break;
        case TOKEN_LPAREN: return "TOKEN_LPAREN"; break;
        case TOKEN_RPAREN: return "TOKEN_RPAREN"; break;
        case TOKEN_ADD: return "TOKEN_ADD"; break;
        case TOKEN_HYPHEN: return "TOKEN_HYPHEN"; break;
        case TOKEN_COLON: return "TOKEN_COLON"; break;
        default: return "TOKEN_UNIDENTIFIED";
    }
}

//free memory
void free_token(token* token) {
    //free token value
    free(token->value);
    //then free token
    free(token);
}
