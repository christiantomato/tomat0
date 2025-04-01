#include "include/all.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
    //time to do some lexer tests..?
    char contents[] = "\"four\" = \"five\"";
    printf("performing lexical analysis on: %s\n", contents);
    //we should get a string, an equals, and a string token
    lexer* my_lexer = init_lexer(contents);

    //get first token
    token* first = tokenize_next(my_lexer);
    //print type of token
    printf("first token: %d \n", first->token_type);
    printf("value stored in token: %s \n", first->value);

    //get second token
    token* second = tokenize_next(my_lexer);
    //print type of token 
    printf("second token: %d \n", second->token_type);
    printf("value stored in token: %s \n", second->value);

    //get third token
    token* third = tokenize_next(my_lexer);
    //print type of token 
    printf("third token: %d \n", third->token_type);
    printf("value stored in token: %s \n", third->value);

    return 0;
}