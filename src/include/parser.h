//the parser will be the one to interpret our nodes and build the correct tree structure
#include "lexer.h"
#include "ast_node.h"

#ifndef PARSER_H
#define PARSER_H

typedef struct parser_struct {
    //root of the tree (program node)
    ASTNode* root;
    //the tokens we are parsing
    List* tokens;

} Parser;

Parser* init_parser(List* tokens);

//all parsing functions, that will return a pointer to the tree it has parsed
ASTNode* parse_expression();
ASTNode* parse_factor();
ASTNode* parse_term();

#endif