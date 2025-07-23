#include "include/parser.h"
#include <stdlib.h>

Parser* init_parser(List* tokens) {
    //create a parser and allocate memory
    Parser* parser = malloc(sizeof(Parser));
    //initialize the root node to be a PROGRAM node
    parser->root = init_node(AST_PROGRAM);
    //use the list of tokens passed in
    parser->tokens = tokens;
    //set the initial token
    parser->current_token = parser->tokens->array[0];
    return parser;
}

//parse each line and add it to the children of the program node of our parser
void parser_parse(Parser* parser) {
    //while there are still tokens, parse line by line
    while(!is_empty(parser->tokens)) {
        parser_skip_comments(parser);
        list_add(parser->root->children, parse_line(parser));
    }
}

//"consumes" the token it is on, and sets the new current token to the next in the list
void parser_advance(Parser* parser) {
    //remove the current from the tokens list, list will shift things over to index 0, and set the new current token
    list_remove(parser->tokens, 0, free_token_wrapper);
    //update
    parser->current_token = parser->tokens->array[0];
}

//look ahead to the next token, to help with parsing logic
Token* parser_peek(Parser* parser, int ahead) {
    //return the token at however many places ahead
    return parser->tokens->array[ahead];
}


void parser_skip_comments(Parser* parser) {
    //skip all comments until we reach an actual line to parse
    while(true) {
        //look at the first token on the line
        if(parser->current_token->type == TOKEN_RCHEVRON) {
            //skip the line by advancing until the next one
            while(parser->current_token->type != TOKEN_NEWLINE) {
                parser_advance(parser);
            }
            //move past the token newline to get onto next line, and then we check for comments again
            parser_advance(parser);
        }
        else {
            //done skipping all comments, parsing will take place
            break;
        }
    }
}

//parsing functions returning a node


//parse the line (tomat0 is line by line, so this will simplify our life)
ASTNode* parse_line(Parser* parser) {
    //go through each type of statement it could be 
    if(parser->current_token->type == TOKEN_KEYWORD_INT || parser->current_token->type == TOKEN_KEYWORD_STRING) {
       //parsing a variable declaration
       return parse_variable_declaration(parser);
    }
    if(parser->current_token->type == TOKEN_KEYWORD_SOUT) {
        //parsing a print statement
        return parse_print_statement(parser);
    }
}

ASTNode* parse_variable_declaration(Parser* parser) {
    //create the node we will return
    ASTNode* declarationNode = init_node(AST_VARIABLE_DECLARATION);

    //first step is to determine the variable type
    if(parser->current_token->type == TOKEN_KEYWORD_INT) {
        declarationNode->specialization.variable_declaration.variable_type = "int";
    }
    else if(parser->current_token->type == TOKEN_KEYWORD_STRING) {
        declarationNode->specialization.variable_declaration.variable_type = "string";
    }

    //advance to next token
    parser_advance(parser);

    //second step is to get the variable name

}

ASTNode* parse_print_statement(Parser* parser) {

}

ASTNode* parse_expression(Parser* parser) {

}

ASTNode* parse_term(Parser* parser) {

}

ASTNode* parse_factor(Parser* parser) {

}


