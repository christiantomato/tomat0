//implementation of the ast node definition
#include "include/ast_node.h"
#include <stdlib.h>

//node initialization
ASTNode* init_node(NodeType type) {
    //allocate memory for the node
    ASTNode* node = malloc(sizeof(ASTNode));
    //initialize values
    node->type = type;
    node->children = NULL;
    //initialize values needed for each node specilization
    switch(type) {
        case AST_VARIABLE_DECLARATION:
            node->specialization.variable_declaration.variable_type = NULL;
            node->specialization.variable_declaration.variable_name = NULL;
            node->specialization.variable_declaration.assignment = NULL;
            break;
        case AST_PRINT_STATEMENT:
            node->specialization.print_statement.statement = NULL;
            break;
        case AST_BINARY_OPERATION:
            node->specialization.binary_operation.left = NULL;
            node->specialization.binary_operation.right = NULL;
            node->specialization.binary_operation.operand = NULL;
            break;
        case AST_INTEGER:
            node->specialization.integer.value = 0;
            break;
        default:
            //specialization not needed (ex. AST_PROGRAM)
            break;
    }
    //return the node 
    return node;
}

//node type as string
char* node_type_str(ASTNode* node) {
    //switch on the token type
    switch(node->type) {
        case AST_PROGRAM: return "AST_PROGRAM"; break;
        case AST_VARIABLE_DECLARATION: return "AST_VARIABLE_DECLARATION"; break;
        case AST_PRINT_STATEMENT: return "AST_PRINT_STATEMENT"; break;
        case AST_BINARY_OPERATION: return "AST_BINARY_OPERATION"; break;
        case AST_INTEGER: return "AST_INTEGER"; break;
    }
}

//free memory
int free_node(ASTNode* node) {
    //make sure not null
    if(node == NULL) {
        return 1;
    }
    //free any dynamically allocated memory needed for specialized nodes
    switch(node->type) {
        case AST_VARIABLE_DECLARATION:
            free(node->specialization.variable_declaration.variable_type);
            free(node->specialization.variable_declaration.variable_name);
            free(node->specialization.variable_declaration.assignment);
            break;
        case AST_PRINT_STATEMENT:
            free(node->specialization.print_statement.statement);
            break;
        case AST_BINARY_OPERATION:
            free(node->specialization.binary_operation.left);
            free(node->specialization.binary_operation.right);
            free(node->specialization.binary_operation.operand);
            break;
        default:
            //no additional specialized data to be freed
            break;
    }
    //free all children nodes recursively
    if(node->children != NULL) {
        free_complex_list(node->children, free_node_wrapper);
    }
    //free node itself
    free(node);
    return 0;
}

//wrapper for free node
void free_node_wrapper(void* node) {
    free_node((ASTNode*) node);
}