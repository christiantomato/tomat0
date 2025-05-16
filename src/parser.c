#include "include/parser.h"
#include <stdlib.h>

Parser* init_parser(List* tokens) {
    //create a parser and allocate memory
    Parser* parser = malloc(sizeof(Parser));
    //initialize root node
    parser->root = init_node(AST_PROGRAM);
    //use the list we passed
    parser->tokens = tokens;
    //set the initial token
    parser->current_token = parser->tokens->array[0];
}

//parse each line and add it to the children of the program node of our parser
void parser_parse(Parser* parser) {
    //while there are still tokens, parse line by line
    while(!is_empty(parser->tokens)) {
        parser_skip_comments(parser);
        list_add(parser->root->children, parse_line(parser));
    }
}

void parser_advance(Parser* parser) {
    //remove from the tokens list, list will shift to index 0 allowing current token to become the next one!
    list_remove(parser->tokens, 0, free_token_wrapper);
}

void parser_skip_comments(Parser* parser) {
    //skip all comments until we reach an actual line to parse
    while(true) {
        //look at the first token on the line
        if(parser->current_token->type == TOKEN_LPAREN) {
            //skip the line by advancing until the next one
            while(parser->current_token->type != TOKEN_NEWLINE) {
                parser_advance(parser);
            }
            //move past the token newline to get onto next line, and then we check for comments again
            parser_advance(parser);
        }
        else {
            //we need to start parsing
            break;
        }
    }
}

//parse the line
ASTNode* parse_line(Parser* parser) {
    //the node to be returned
    ASTNode* line_node;
    //parse until we reach the newline token
    while(parser->current_token->type != TOKEN_NEWLINE) {
        //deal with all cases
        
    }
    //advance past the newline now
    parser_advance(parser);
    //return the node
    return line_node;
}
ASTNode* parse_expression(Parser* parser) {

}
ASTNode* parse_term(Parser* parser) {

}
ASTNode* parse_factor(Parser* parser) {

}


