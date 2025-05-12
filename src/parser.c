#include "include/parser.h"
#include <stdlib.h>

//implenent the parser functions

Parser* init_parser(List* tokens) {
    //create a parser and allocate memory
    Parser* parser = malloc(sizeof(Parser));
    //initialize root node
    parser->root = init_node(AST_PROGRAM);
    //use the list we passed
    parser->tokens = tokens;
    //set the index to 0
    parser->index = 0;
}

//parse each line and add it to the children of the program node of our parser
void parser_parse(Parser* parser) {
    //while there is still tokens, parse line by line
    while(!is_empty(parser->tokens)) {
        list_add(parser->root->children, parse_line(parser));
    }
}

//parse the line
ASTNode* parse_line(Parser* parser) {
    
}
ASTNode* parse_expression(Parser* parser) {

}
ASTNode* parse_term(Parser* parser) {

}
ASTNode* parse_factor(Parser* parser) {

}


