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
    AST_GLOBAL,
    AST_VARIABLE_DECLARATION,
    AST_VARIABLE,
    AST_BINARY_OPR,
    AST_STRING,
    AST_FUNCTION_CALL,
} type;

//each node will be of the form (type, children[])
typedef struct ast_node_struct {
    //ast node type based on the enum
    int type;
    //have a reference to the children (differs depending on the specific type of ast node)
    list* children;
} ast_node;

#endif
