#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

    //get file contents with file reader
    char* file_contents = read_file("assemblygoal.tmt");
    
    //display what is in main.tmt
    printf("%s\n\n", file_contents);

    //create the lexer and ready the tokens list
    Lexer* my_lexer = init_lexer(file_contents);
    List* tokens_list = init_list(30);

    //tokenize the contents
    Token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %s, Token value: %s \n", token_type_as_str(token), token->value);
        //add to the list of tokens
        list_add(tokens_list, token);
    }

    //free the lexer, it has done its job
    free_lexer(my_lexer);
    printf("\n");

    //add the end of file token to the list
    Token* end_of_file_token = init_token(TOKEN_EOF, NULL);
    list_add(tokens_list, end_of_file_token);

    //bring out the parser
    Parser* my_parser = init_parser(tokens_list);

    //parse everything
    parser_parse(my_parser);

    //write from root now
    FILE* ast_file = fopen("ast_output.txt", "w");
    print_ast(ast_file, my_parser->root, 0);

    //get a reference to the root node
    ASTNode* ast_tree_root = my_parser->root;

    //parser can be freed now, it has created the tree 
    free_parser(my_parser);

    //generate the assembly code
    FILE* assembly_file = fopen("generated_code.s", "w");
    generate_assembly_code(assembly_file, ast_tree_root);
    
    //success
    return 0;
}