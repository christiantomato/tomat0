#include "include/parser.h"
#include <stdlib.h>

Parser* init_parser(List* tokens) {
    //create a parser and allocate memory
    Parser* parser = malloc(sizeof(Parser));
    //initialize the root node to be a PROGRAM node
    parser->root = init_node(AST_PROGRAM);
    //use the list of tokens passed in
    parser->tokens = tokens;
    //set the initial token to starting position in array
    parser->current_token = parser->tokens->array[0];
    //initialize the index at zero
    parser->index = 0;
    return parser;
}

//parse each line and add it to the children of the program node of our parser
void parser_parse(Parser* parser) {
    //parse until we reach the end of file token
    while(parser->current_token->type != TOKEN_EOF) {
        //first skip everything that does not need to be parsed
        parser_skip(parser);
        //check again for end of file again after skipping
        if(parser->current_token->type == TOKEN_EOF) {
            //finished parsing
            break;
        }
        //now we can parse lines and add to the children of the program node safely
        list_add(parser->root->children, parse_line(parser));
    }
}

//"consumes" the token it is on, and sets the new current token to the next in the list
void parser_advance(Parser* parser) {
    parser->index++;
    //update
    parser->current_token = parser->tokens->array[parser->index];
}

//look ahead to the next token, to help with parsing logic
Token* parser_peek(Parser* parser, int ahead) {
    //return the token at however many places ahead
    return parser->tokens->array[ahead];
}

//skip comments and blank lines
void parser_skip(Parser* parser) {
    while(true) {
        //if rchevron, skip the comment
        if(parser->current_token->type == TOKEN_RCHEVRON) {
            //skip everything until we hit a newline or end token
            while(parser->current_token->type != TOKEN_NEWLINE && parser->current_token->type != TOKEN_EOF) {
                parser_advance(parser);
            }
        }
        //if we have a blank line
        else if(parser->current_token->type == TOKEN_NEWLINE) {
            //skip it
            parser_advance(parser);
        }
        else {
            //once all the unneccesary stuff is skipped, exit
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
    else if(parser->current_token->type == TOKEN_KEYWORD_SOUT) {
        //parsing a print statement
        return parse_print_statement(parser);
    }
    else {
        return NULL;
    }
}

//parse a variable declaration / assignment (declarations in tomat0 must have a value aswell)
ASTNode* parse_variable_declaration(Parser* parser) {
    //create the node we will return
    ASTNode* var_dec_node = init_node(AST_VARIABLE_DECLARATION);

    //first step is to determine the variable type

    if(parser->current_token->type == TOKEN_KEYWORD_INT) {
        //set the variable type to integer
        var_dec_node->specialization.variable_declaration.variable_type = "int";
    }
    else if(parser->current_token->type == TOKEN_KEYWORD_STRING) {
        //set the variable type to string
        var_dec_node->specialization.variable_declaration.variable_type = "string";
    }

    //advance to the next token
    parser_advance(parser);

    //second step is to expect/get the variable name

    if(parser->current_token->type == TOKEN_ID) {
        //assign the variable name
        var_dec_node->specialization.variable_declaration.variable_name = parser->current_token->value;
    }
    else {
        //problem
        return NULL;
    }

    //advance to next
    parser_advance(parser);

    //third step is to expect an equals

    if(parser->current_token->type == TOKEN_EQUALS) {
        //this is expected, we can move on
        parser_advance(parser);
    }
    else {
        //problem
        return NULL;
    }

    //last step is to get the value that is being assigned
    var_dec_node->specialization.variable_declaration.assignment = parse_expression(parser);
    
    //return the node
    return var_dec_node;
}

//parse a print statement - sout(statement)
ASTNode* parse_print_statement(Parser* parser) {
    //create the node we will return
    ASTNode* print_node = init_node(AST_PRINT_STATEMENT);

    //expect and eat the LPAREN
    if(parser->current_token->type == TOKEN_LPAREN) {
        //expected, EAT
        parser_advance(parser);
    }
    else {
        //problem 
        return NULL;
    }

    //next we have to evaluate the statement inside the parens
    print_node->specialization.print_statement.statement = parse_expression(parser);

    //after that, ensure a closing paren
    if(parser->current_token->type == TOKEN_RPAREN) {
        //expected, CONSUME
        parser_advance(parser);
    }
    else {
        //bad syntax, problem
        return NULL; 
    }

    //return the print statement node
    return print_node;
}

/*
Grammar for our LL(1) Recursive Descent Parser

E -> T E'
E' -> (+ -) T E' | epsilon
T -> F T'
T' -> (* /) F T' | epsilon
F -> TOKEN_ID | Literal | (E) | -F
*/

//build up the expression tree using the given grammar rules
ASTNode* parse_expression(Parser* parser) {
    //parse the left term
    ASTNode* left = parse_term(parser);

    //continue the loop as long as we are doing addition or subtraction to build up our tree
    while(parser->current_token->type == TOKEN_PLUS || parser->current_token->type == TOKEN_HYPHEN) {
        //get the operand
        char* operand = parser->current_token->value;

        //move past
        parser_advance(parser);

        //parse the right term
        ASTNode* right = parse_term(parser);

        //create the binary operation node
        ASTNode* binary_op_node = init_node(AST_BINARY_OPERATION);
        binary_op_node->specialization.binary_operation.left = left;
        binary_op_node->specialization.binary_operation.operand = operand;
        binary_op_node->specialization.binary_operation.right = right;

        //left is now this new node, building up the tree with correct associativity
        left = binary_op_node;
    }

    //once done return left
    return left;
}

//same concept as expression, just different operand
ASTNode* parse_term(Parser* parser) {
    //parse the left term
    ASTNode* left = parse_factor(parser);

    //continue the loop as long as we are doing addition or subtraction to build up our tree
    while(parser->current_token->type == TOKEN_ASTERIK || parser->current_token->type == TOKEN_FSLASH) {
        //get the operand
        char* operand = parser->current_token->value;

        //move past
        parser_advance(parser);

        //parse the right term
        ASTNode* right = parse_factor(parser);

        //create the binary operation node
        ASTNode* binary_op_node = init_node(AST_BINARY_OPERATION);
        binary_op_node->specialization.binary_operation.left = left;
        binary_op_node->specialization.binary_operation.operand = operand;
        binary_op_node->specialization.binary_operation.right = right;

        //left is now this new node, building up the tree with correct associativity
        left = binary_op_node;
    }

    //once done return left
    return left;
}

//Contains the terminals, just a bunch of if statements
ASTNode* parse_factor(Parser* parser) {

    //check for parenthesized expression
    if(parser->current_token->type == TOKEN_LPAREN) {
        //advance to the expression
        parser_advance(parser);

        //parse the expression
        ASTNode* expression_node = parse_expression(parser);

        //expect a closing parenthesis
        if(parser->current_token->type == TOKEN_RPAREN) {
            //advance past it
            parser_advance(parser);
            //return the expression node
            return expression_node;
        }
        else {
            //problem
            return NULL;
        }
    }

    //check for negation
    if(parser->current_token->type == TOKEN_HYPHEN) {
        //advance to the factor
        parser_advance(parser);
        //create the negation node
        ASTNode* negation_node = init_node(AST_NEGATION);
        //assign
        negation_node->specialization.negation.factor = parse_factor(parser);
        //return the node
        return negation_node;
    }

    //check for an identifier
    if(parser->current_token->type == TOKEN_ID) {
        //create the AST_VARIABLE
        ASTNode* variable_node = init_node(AST_VARIABLE);
        //set the name
        variable_node->specialization.variable.variable_name = parser->current_token->value;
        //advance past
        parser_advance(parser);
        //return the node
        return variable_node;
    }

    //check for an integer literal
    if(parser->current_token->type == TOKEN_NUM) {
        //create the AST_INTEGER
        ASTNode* integer_node = init_node(AST_INTEGER);
        //assign
        integer_node->specialization.integer_literal.value = atoi(parser->current_token->value);
        //advance past the number
        parser_advance(parser);
        //return the node
        return integer_node;
    }

    //nothing expected, problem
    return NULL;
}



