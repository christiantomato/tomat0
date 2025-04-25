#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    //get file contents with file reader
    char* file_contents = read_file("examples/main.tmt");
    
    //tokenize with lexer
    printf("%s", file_contents);
    Lexer* my_lexer = init_lexer(file_contents);
    Token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %s, Token value: %s \n", token_type_str(token), token->value);
        //free the token as it is not needed anymore
        free_token(token);
    }
    free_lexer(my_lexer);
    printf("\n");

    //test out ast nodes and lists together
    ASTNode* main_node = init_node(AST_PROGRAM);
    //create 2 variable declaration children nodes
    ASTNode* var_dec_1 = init_node(AST_VARIABLE_DECLARATION);
    ASTNode* var_dec_2 = init_node(AST_VARIABLE_DECLARATION);
    //initialize the list for the 2 children
    main_node->children = init_list(2);
    //assign the children to the main node
    list_add(main_node->children, var_dec_1);
    list_add(main_node->children, var_dec_2);
    //check the size of the main node (should be 40 bytes)
    printf("%lu\n", sizeof(*main_node));
    //free everything
    free_node(main_node);
    
    return 0;
}