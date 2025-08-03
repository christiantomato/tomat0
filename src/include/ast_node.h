//define nodes for the abstract syntax tree
/*
- Declarations
- Function Calls
- Keywords
- Binary Operations
- Literals
*/

#include "array_list.h"
#include <stdio.h>

#ifndef AST_NODE
#define AST_NODE

//define the enum for all the different types of nodes that are possible in the syntax tree
typedef enum ast_node_type {
    AST_PROGRAM,
    AST_VARIABLE_DECLARATION,
    AST_PRINT_STATEMENT,
    AST_BINARY_OPERATION,
    AST_NEGATION,
    AST_VARIABLE,
    AST_INTEGER,
} NodeType;

//forward declare our AST node structure
struct ast_node_struct;

//define all the different type of ast nodes that have special properties and attributes
typedef struct ast_variable_declaration {
    char* variable_type;
    char* variable_name;
    struct ast_node_struct* assignment;
} VariableDeclaration;

typedef struct ast_print_statement {
    struct ast_node_struct* statement;
} PrintStatement;

typedef struct ast_binary_operation {
    struct ast_node_struct* left;
    struct ast_node_struct* right;
    char* operand;
} BinaryOperation;

typedef struct ast_negation {
    struct ast_node_struct* factor;
} Negation;

typedef struct ast_variable {
    char* variable_name;
    struct ast_node_struct* value;
} Variable;

typedef struct ast_integer {
    int value;
} IntegerLiteral;

//unionize all the different node types
typedef union ast_node_specializations {
    VariableDeclaration variable_declaration;
    PrintStatement print_statement;
    BinaryOperation binary_operation;
    Negation negation;
    Variable variable;
    IntegerLiteral integer_literal;
} ASTSpecialization;

//fully declare the ast node - each node will be of the form (type, children[], node specialization (arguments, properties, etc.))
typedef struct ast_node_struct {
    //type of node using enum
    NodeType type;
    //list of children nodes
    List* children;
    //utilizing the union, we can assign the correct data to the type of node
    ASTSpecialization specialization;
} ASTNode;

//initialize a node
ASTNode* init_node(NodeType type);
//get the node type enum name
char* node_type_str(ASTNode* node);
//write to file the tree representation from any node
void print_ast(ASTNode* root, int indent);
//helper method for indentation
void print_indent(FILE* file, int indent);
//free memory of a node
int free_node(ASTNode* node);
//wrapper for free node, so we can pass it in to our free_complex_list for the children
void free_node_wrapper(void* node);

#endif
