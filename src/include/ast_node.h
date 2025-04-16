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

//define the enum for all the different types of nodes that are possible in the syntax tree
typedef enum ast_node_type {
    AST_PROGRAM,
    AST_FUNCTION_CALL,
    AST_VARIABLE_DECLARATION,
    AST_VARIABLE,
    AST_BINARY_OPR,
    AST_STRING,
} type;

//define all the different types of ast nodes with their arguments and properties
typedef struct ast_program_node {
    //program node properties
} program_node;
typedef struct ast_function_node {
    //function properties
    char* function_name;

} function_node;
typedef struct ast_var_declaration_node {
    //variable declaration properties
    char* variable_name;

} declaration_node;

//unionize all the different types of node types
typedef union ast_node_types {
    //include all types
    program_node program_node;
    function_node function_node;
    declaration_node declaration_node;
} node_type;

//each node will be of the form (type, children[])
typedef struct ast_node_struct {
    //type of node using enum
    int type;
    //list of children nodes
    list* children;
    //the union which will contain all specfic data about the actual type of node
    node_type node_data;
} ast_node;

#endif
