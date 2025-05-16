//the parser will be the one to interpret our nodes and build the correct tree structure
#include "lexer.h"
#include "ast_node.h"

#ifndef PARSER_H
#define PARSER_H

typedef struct parser_struct {
    //root of the tree (will be the program node)
    ASTNode* root;
    //give it the list of tokens that we will be parsing
    List* tokens;
    //the current token
    Token* current_token;
} Parser;

//initialize the parser and pass in the tokens we got from lexical analysis
Parser* init_parser(List* tokens);
//main function which parses all the tokens and constructs the tree to the root
void parser_parse(Parser* parser);

//helper method to move onto the next token
void parser_advance(Parser* parser);
//helper method to skip comments
void parser_skip_comments(Parser* parser);

//parsing functions that return pointers to the subtree that they have parsed

//tomat0 will be parsed line by line
ASTNode* parse_line(Parser* parser);
//arithmetic parsing hierarchy (expressions -> terms -> factors)
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_factor(Parser* parser);

#endif