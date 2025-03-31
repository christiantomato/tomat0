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
        //figure out what kind of token it is

        //first skip any whitespace
        skip_whitespace(lexer);
        
        //lets use a switch for the enum
        switch(lexer->c) {
            //equals sign
            case '=': 
                {
                    //create the token to return whilst advancing lexer
                    token* equals_token = init_token(0, get_current_char_as_string(lexer));
                    return continue_with_token(lexer, equals_token);
                }
                break;

            //semicolon
            case ';':
                {
                    token* semicolon_token = init_token(1, get_current_char_as_string(lexer));
                    return continue_with_token(lexer, semicolon_token);
                }
                break;
            //left paren
            case '(':
            {
                token* lparen_token = init_token(2, get_current_char_as_string(lexer));
                return continue_with_token(lexer, lparen_token);
            }
                break;
            //right paren
            case ')':
            {
                token* rparen_token = init_token(3, get_current_char_as_string(lexer));
                return continue_with_token(lexer, rparen_token);
            }
                break;
            //quotation (string)
            case '"':
                //since we have a quotation, we need to tokenize the string following it
                return tokenize_string(lexer);
                break;
            default:
                return NULL;
        }
    }
    return NULL;
}

//function for how we will tokenize strings
token* tokenize_string(lexer* lexer) {
    //skip the initial quotation
    advance(lexer);
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as we have not reached next quotation
    while(lexer->c != '"') {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = get_current_char_as_string(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));

        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);

        //advance to next
        advance(lexer);
    }
    //ignore closing quote
    advance(lexer);
    //once finisished, return string as token
    return init_token(4, strValue);
}

//continue with a token
token* continue_with_token(lexer* lexer, token* token) {
    //advance with the token
    advance(lexer);
    return token;
}

//function to get the current char as a char[]
char* get_current_char_as_string(lexer* lexer) {
    //lexer->c is char, we need to make it a proper null terminated string
    char* char_as_str = malloc(2*sizeof(char));
    //build the null terminated string
    char_as_str[0] = lexer->c;
    char_as_str[1] = '\0';
    //return the char as a string
    return char_as_str;
}