//implement the lexer with the specified functions
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
        my_lexer->c = contents[my_lexer->i];
        my_lexer->i = 0;
        my_lexer->contents = contents;
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

//lexer skip over whitespace 
void skip_whitespace(lexer* lexer) {
    //advance until no longer on whitespace
    while(isspace(lexer->c)) {
        advance(lexer);
    }
}

//critical method that will classify tokens
token* tokenize_next(lexer* lexer) {
    //while we are not on null character and are still within contents
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        //first skip any whitespace
        skip_whitespace(lexer);

        //check for number first (variables cannot start with numbers in tomat0)
        if(isnumber(lexer->c)) {
            //tokenize the entire number
            return tokenize_number(lexer);
        }
        //for variables, keywords
        if(isalnum(lexer->c)) {
            //tokenize the variable/keyword
            return tokenize_ID(lexer);
        }
        
        //use a switch paired with the token type enum
        switch(lexer->c) {
            case '"':
                //since we have a quotation, we need to tokenize the string following it
                return tokenize_string(lexer); break;
            //all other easy punctuations
            case '=': return continue_with_token(lexer, init_token(TOKEN_EQUALS, lexer_char_as_string(lexer))); break;
            case ';': return continue_with_token(lexer, init_token(TOKEN_SEMI, lexer_char_as_string(lexer))); break;
            case '(': return continue_with_token(lexer, init_token(TOKEN_LPAREN, lexer_char_as_string(lexer))); break;
            case ')': return continue_with_token(lexer, init_token(TOKEN_RPAREN, lexer_char_as_string(lexer))); break;
            case '+': return continue_with_token(lexer, init_token(TOKEN_ADD, lexer_char_as_string(lexer))); break;
            case '-': return continue_with_token(lexer, init_token(TOKEN_HYPHEN, lexer_char_as_string(lexer))); break;
            case ':': return continue_with_token(lexer, init_token(TOKEN_COLON, lexer_char_as_string(lexer))); break;
            default: return NULL;
        }
    }
    return NULL;
}

//method for how we will tokenize strings
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
        char* temp = lexer_char_as_string(lexer);
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
    return init_token(TOKEN_STRING, strValue);
}

//method to tokenize IDs (variables and keywords)
token* tokenize_ID(lexer* lexer) {
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as our ID is alpha numeric
    while(isalnum(lexer->c)) {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = lexer_char_as_string(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));
        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);
        //advance to next character
        advance(lexer);
    }
    //once finisished, return string as token
    return init_token(TOKEN_ID, strValue);
}

//method to tokenize numbers
token* tokenize_number(lexer* lexer) {
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as we are still on a number
    while(isnumber(lexer->c)) {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = lexer_char_as_string(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));
        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);
        //advance to next character
        advance(lexer);
    }
    //once finisished, return string as token
    return init_token(TOKEN_NUM, strValue);
}

//just advance the lexer, and return the token we just tokenized
token* continue_with_token(lexer* lexer, token* token) {
    //advance with the token
    advance(lexer);
    return token;
}

//method to get the current char as a char[]
char* lexer_char_as_string(lexer* lexer) {
    //lexer->c is char, we need to make it a proper null terminated string
    char* char_as_str = malloc(2*sizeof(char));
    //build the null terminated string
    char_as_str[0] = lexer->c;
    char_as_str[1] = '\0';
    //return the char as a string
    return char_as_str;
}

//free all the memory that is being used by the lexer
void free_lexer(lexer* lexer) {
    //free the contents
    free(lexer->contents);
    //free the lexer
    free(lexer);
}
