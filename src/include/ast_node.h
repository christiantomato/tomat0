//define nodes for the abstract syntax tree
/*
- variable assignments
- factors vs terms
- identifiers
- statements
*/

#include "array_list.h"

#ifndef AST_NODE
#define AST_NODE

//define the enum for all the different types of nodes in the syntax tree
typedef enum ast_node_type {
    AST_PROGRAM,
    AST_FUNCTION_CALL,
    AST_VARIABLE_DECLARATION,
    AST_VARIABLE,
    AST_BINARY_OPR,
    AST_STRING,
} type;

//each node will be of the form (type, children[])
typedef struct ast_node_struct {
    //type of node
    int type;
    //list of children
    list* children;

    //use a union to differentiate the different properties of each type of node
    typedef union node_definitions {
        //define a variable definition
        typedef struct variable_declaration {
            
        } variable_dec;

    } node_def;

} ast_node;

#endif
