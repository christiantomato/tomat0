#include "include/all.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
    //lexer tests
    char contents[] = "int myVar1 = 102933;";
    lexer* my_lexer = init_lexer(contents);
    token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %d, Token value: %s \n", token->type, token->value);
    }
    
    return 0;
}