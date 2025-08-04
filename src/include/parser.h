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
    //index for the tokens list
    unsigned int index;
} Parser;

//initialize the parser and pass in the tokens we got from lexical analysis
Parser* init_parser(List* tokens);
//main function which parses all the tokens and constructs the tree to the root
void parser_parse(Parser* parser);

//helper method to move onto the next token
void parser_advance(Parser* parser);
//helper method to look ahead in the tokens that are coming
Token* parser_peek(Parser* parser, int ahead);
//helper method to skip comments and blank lines
void parser_skip(Parser* parser);

//all parsing functions that return pointers to the subtree that they have parsed

//parse a statement, line by line
ASTNode* parse_line(Parser* parser);
//parse a variable declaration
ASTNode* parse_variable_declaration(Parser* parser);
//parse a print statement
ASTNode* parse_print_statement(Parser* parser);

//arithmetic parsing hierarchy (expressions -> terms -> factors)
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_factor(Parser* parser);

#endif