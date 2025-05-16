#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    //get file contents with file reader
    char* file_contents = read_file("examples/main.tmt");
    
    printf("%s", file_contents);
    Lexer* my_lexer = init_lexer(file_contents);
    List* tokens_list = init_list(50);

    //tokenize
    Token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %s, Token value: %s \n", token_type_str(token), token->value);
        //add to list
        list_add(tokens_list, token);
    }
    free_lexer(my_lexer);
    printf("\n");

    //test out tokens list
    printf("%s\n", token_type_str(tokens_list->array[20]));
    Token* tok = (Token*)tokens_list->array[20];
    printf("%s\n", tok->value);

    //test out ast nodes and lists together
    ASTNode* main_node = init_node(AST_PROGRAM);
    //create 2 variable declaration children nodes
    ASTNode* var_dec_1 = init_node(AST_VARIABLE_DECLARATION);
    ASTNode* binary_op_1 = init_node(AST_BINARY_OPERATION);
    //initialize the list for the 2 children
    main_node->children = init_list(2);
    //assign the children to the main node
    list_add(main_node->children, var_dec_1);
    list_add(main_node->children, binary_op_1);
    //check the size of the main node (should be 40 bytes)
    printf("%lu\n", sizeof(*main_node));

    //test remove again
    printf("%s\n", node_type_str(main_node->children->array[0]));
    //remove the front element, odn't forget to pass in the free function for the data type. 
    list_remove(main_node->children, 0, free_node_wrapper);
    //see if shifting worked
    printf("%s\n", node_type_str(main_node->children->array[0]));
    //free everything
    free_node(main_node);
    //free the tokens list
    free_complex_list(tokens_list, free_token_wrapper);
    
    return 0;
}