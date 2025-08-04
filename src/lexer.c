#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Initialize Lexer Function

creates a lexer and passes in the contents for it to analyze

char* contents: the string of text to analyze (read from the .tmt file)

return: pointer to the created lexer
*/

Lexer* init_lexer(char* contents) {
    //allocate memory for the lexer
    Lexer* lexer = malloc(sizeof(Lexer));
    //set up initial values
    lexer->index = 0;
    lexer->curr = contents[lexer->index];
    lexer->contents = contents;
    return lexer;
}

/*
Lexer Advance Function

advances to the next character in the contents

Lexer* lexer: the lexer that is advanced
*/

void lexer_advance(Lexer* lexer) {
    //if we are still in string and not at null character
    if(lexer->curr != '\0' && lexer->index < strlen(lexer->contents)) {
        //increment the index
        lexer->index++;
        //move to the next character
        lexer->curr = lexer->contents[lexer->index];
    }
}

/*
Lexer Skip Whitespace Function

skips any blank space between characters as they are irrelvant, 
but takes into account new lines as tomat0 uses them as delimeters

Lexer* lexer: the lexer to skip whitespace
*/

void lexer_skip_whitespace(Lexer* lexer) {
    //skip blank space - but not newlines!
    while(isspace(lexer->curr) && lexer->curr != '\n') {
        lexer_advance(lexer);
    }
}

//critical method that will classify tokens
Token* tokenize_next(Lexer* lexer) {
    //while we are not on null character and are still within contents
    while(lexer->curr != '\0' && lexer->index < strlen(lexer->contents)) {
        //first skip any whitespace
        lexer_skip_whitespace(lexer);

        //check for number first (variables cannot start with numbers in tomat0)
        if(isdigit(lexer->curr)) {
            //tokenize the entire number
            return tokenize_number(lexer);
        }
        //for variables, keywords
        if(isalpha(lexer->curr)) {
            //tokenize the variable/keyword
            return tokenize_ID(lexer);
        }
        
        //use a switch paired with the token type enum
        switch(lexer->curr) {
            case '"':
                //since we have a quotation, we need to tokenize the string following it
                return tokenize_string(lexer); break;
            //all other easy punctuations
            case '\n': return continue_with_token(lexer, init_token(TOKEN_NEWLINE, lexer_char_as_str(lexer))); break;
            case '=': return continue_with_token(lexer, init_token(TOKEN_EQUALS, lexer_char_as_str(lexer))); break;
            case ';': return continue_with_token(lexer, init_token(TOKEN_SEMI, lexer_char_as_str(lexer))); break;
            case '(': return continue_with_token(lexer, init_token(TOKEN_LPAREN, lexer_char_as_str(lexer))); break;
            case ')': return continue_with_token(lexer, init_token(TOKEN_RPAREN, lexer_char_as_str(lexer))); break;
            case '<': return continue_with_token(lexer, init_token(TOKEN_LCHEVRON, lexer_char_as_str(lexer))); break;
            case '>': return continue_with_token(lexer, init_token(TOKEN_RCHEVRON, lexer_char_as_str(lexer))); break;
            case '/': return continue_with_token(lexer, init_token(TOKEN_FSLASH, lexer_char_as_str(lexer))); break;
            case '\\': return continue_with_token(lexer, init_token(TOKEN_BSLASH, lexer_char_as_str(lexer))); break;
            case '+': return continue_with_token(lexer, init_token(TOKEN_PLUS, lexer_char_as_str(lexer))); break;
            case '-': return continue_with_token(lexer, init_token(TOKEN_HYPHEN, lexer_char_as_str(lexer))); break;
            case '*': return continue_with_token(lexer, init_token(TOKEN_ASTERIK, lexer_char_as_str(lexer))); break;
            default: return NULL;
        }
    }
    return NULL;
}

//method for how we will tokenize strings
Token* tokenize_string(Lexer* lexer) {
    //skip the initial quotation
    lexer_advance(lexer);
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as we have not reached next quotation
    while(lexer->curr != '"') {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = lexer_char_as_str(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));
        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);
        //advance to next
        lexer_advance(lexer);
    }
    //ignore closing quote
    lexer_advance(lexer);
    //once finisished, return string as token
    return init_token(TOKEN_STRING, strValue);
}

//method to tokenize identifiers (and keywords)
Token* tokenize_ID(Lexer* lexer) {
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as our ID is alpha numeric (therefore variable names are only alphanumeric!!!)
    while(isalnum(lexer->curr)) {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = lexer_char_as_str(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));
        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);
        //advance to next character
        lexer_advance(lexer);
    }

    //check if it is a keyword
    if(strcmp(strValue, "int") == 0) {
        //integer declaration keyword
        return init_token(TOKEN_KEYWORD_INT, strValue);
    }
    else if(strcmp(strValue, "string") == 0) {
        //string declaration keyword
        return init_token(TOKEN_KEYWORD_STRING, strValue);
    }
    else if(strcmp(strValue, "sout") == 0) {
        //print statement keyword
        return init_token(TOKEN_KEYWORD_SOUT, strValue);
    }
    else {
        //return as a regular identifier (for function or variable names)
        return init_token(TOKEN_ID, strValue);
    }
}

//method to tokenize numbers
Token* tokenize_number(Lexer* lexer) {
    //allocate memory for the string we will be returning
    char* strValue = malloc(sizeof(char));
    //make sure no garbage values, set null character
    strValue[0] = '\0';
    //build the string as long as we are still on a number
    while(isdigit(lexer->curr)) {
        //create a temp char that will store the current char as a string, so we can concat it later
        char* temp = lexer_char_as_str(lexer);
        //reallocating memory as needed, since adding the next char (+2 for new char and null terminator which isn't counted)
        strValue = realloc(strValue, (strlen(strValue) + 2) * sizeof(char));
        //concatenate it
        strcat(strValue, temp);
        //free temp as its no longer needed
        free(temp);
        //advance to next character
        lexer_advance(lexer);
    }
    //once finisished, return string as token
    return init_token(TOKEN_NUM, strValue);
}

//just advance the lexer, and return the token we just tokenized
Token* continue_with_token(Lexer* lexer, Token* token) {
    //advance with the token
    lexer_advance(lexer);
    return token;
}

//method to get the current char as a char[]
char* lexer_char_as_str(Lexer* lexer) {
    //special case for new line
    if(lexer->curr == '\n') {
        return strdup("\\n");
    }
    //lexer->c is char, we need to make it a proper null terminated string
    char* char_as_str = malloc(2*sizeof(char));
    //build the null terminated string
    char_as_str[0] = lexer->curr;
    char_as_str[1] = '\0';
    //return the char as a string
    return char_as_str;
}

//free all the memory that is being used by the lexer
int free_lexer(Lexer* lexer) {
    if(lexer == NULL) {
        //bad return 1
        return 1;
    }
    //free the contents
    free(lexer->contents);
    //free the lexer
    free(lexer);
    //return 0 for success
    return 0;
}
