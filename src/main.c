#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    //get file contents with file reader
    char* file_contents = read_file("/Users/christiantamayo/VSCodeProjects/tomat0/examples/main.tmt");
    
    //tokenize with lexer
    printf("%s", file_contents);
    lexer* my_lexer = init_lexer(file_contents);
    token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %s, Token value: %s \n", token_type_str(token), token->value);
        //free the token as it is not needed anymore
        free(token);
    }
    
    return 0;
}