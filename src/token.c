//implement the token
#include "include/token.h"
#include <stdlib.h>
#include <stdio.h>

token* init_token(int type, char* value) {
    //allocate space for the token
    token* my_token = malloc(sizeof(token));
    //make sure memory allocation went well
    if(my_token != NULL) {
        //set the values to what we passed in
        my_token->token_type = type;
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