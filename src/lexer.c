//now we will implement the actual lexer with the specified functions
#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//lexer initializor
lexer* init_lexer(char* contents) {
    //allocate memory for the lexer
    lexer* my_lexer = malloc(sizeof(lexer));
    //make sure memory allocation went smoothly
    if(my_lexer != NULL) {
        //initialize values
        my_lexer->i = 0;
        my_lexer->contents = contents;
        //start the character at first index of contents
        my_lexer->c = contents[my_lexer->i];
        //finally return
        return my_lexer;
    }
    else {
        //something went wrong
        printf("error");
        return NULL;
    }
}

//move to the next character
void advance(lexer* lexer) {
    //if we are still in string and not at null character
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        //increment the index
        lexer->i++;
        //move to the next character
        lexer->c = lexer->contents[lexer->i];
    }
}

//to skip whitespace
void skip_whitespace(lexer* lexer) {
    //if we are on white space, move
    while(isspace(lexer->c)) {
        advance(lexer);
    }
}

//critical function that will classify tokens. 
token* get_next_token(lexer* lexer) {
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        //here we have to figure out what kind of token it is

        //first skip any whitespace
        skip_whitespace(lexer);
        
        //lets use a switch for the enum
        switch(lexer->c) {
            case '=': 
                {
                    //has to be equals (no other valid token can start with equals)
                    //create the token
                    token* my_token = init_token(5, get_current_char_as_string(lexer));
                    return continue_with_token(lexer, my_token);
                }
                break;
            case ';':
                break;
        }
    }
}
//function for how we will tokenize strings
token* tokenize_string(lexer* lexer) {

}

//continue with a token
token* continue_with_token(lexer* lexer, token* token) {
    //advance with the token
    advance(lexer);
    return token;
}

//function to get the current char as a char[]
char* get_current_char_as_string(lexer* lexer) {

}