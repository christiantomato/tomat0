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
    AST_VARIABLE_DECLARATION,
    AST_BINARY_OP,
    AST_INTEGER,
} NodeType;

//forward declare our AST node structure
struct ast_node_struct;

//define all the different type of ast nodes that have special properties and attributes
typedef struct ast_variable_declaration_node {
    char* variable_type;
    char* variable_name;
    struct ast_node_struct* assignment;
} VariableDeclarationNode;
typedef struct ast_binary_operation {
    struct ast_node_struct* left;
    struct ast_node_struct* right;
    char* operand;
} BinaryOperationNode;
typedef struct ast_int_node {
    int value;
} IntegerNode;

//unionize all the different node types
typedef union ast_node_structs {
    VariableDeclarationNode declaration_node;
    BinaryOperationNode binary_operation_node;
    IntegerNode integer_node;
} SpecializedNode;

//fully declare the ast node - each node will be of the form (type, children[], node data (arguments, properties, etc.))
typedef struct ast_node_struct {
    //type of node using enum
    NodeType type;
    //list of children nodes
    List* children;
    //utilizing the union, we can assign the correct data to the type of node
    SpecializedNode attributes;
} ASTNode;

#endif
