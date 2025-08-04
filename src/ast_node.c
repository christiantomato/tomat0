//implementation of the ast node definition
#include "include/ast_node.h"
#include <stdlib.h>

//node initialization
ASTNode* init_node(NodeType type) {
    //allocate memory for the node
    ASTNode* node = malloc(sizeof(ASTNode));
    //initialize values
    node->type = type;
    node->children = init_list(5);
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
        case AST_NEGATION:
            node->specialization.negation.factor = NULL;
            break;
        case AST_VARIABLE:
            node->specialization.variable.variable_name = NULL;
            node->specialization.variable.value = NULL;
            break;
        case AST_INTEGER:
            node->specialization.integer_literal.value = 0;
            break;
        case AST_STRING:
            node->specialization.string_literal.value = "\0";
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
    //switch on the node type
    switch(node->type) {
        case AST_PROGRAM: return "AST_PROGRAM"; break;
        case AST_VARIABLE_DECLARATION: return "AST_VARIABLE_DECLARATION"; break;
        case AST_PRINT_STATEMENT: return "AST_PRINT_STATEMENT"; break;
        case AST_BINARY_OPERATION: return "AST_BINARY_OPERATION"; break;
        case AST_NEGATION: return "AST_NEGATION"; break;
        case AST_VARIABLE: return "AST_VARIABLE"; break;
        case AST_INTEGER: return "AST_INTEGER"; break;
        case AST_STRING: return "AST_STRING"; break;
    }
}

//writes the ast to a file
void print_ast(FILE* file, ASTNode* root, int indent) {
    //print the indentation
    print_indent(file, indent);

    //always start with node title
    fprintf(file, "NODE: %s\n", node_type_str(root));

    //switch on the node type
    switch(root->type) {

        case AST_PROGRAM:
            //iterate through the children statements and write them to file
            for(int i = 0; i < root->children->num_items; i++) {
                //(indent always 1)
                print_ast(file, root->children->array[i], 1);
            }
            break;
            
        case AST_VARIABLE_DECLARATION:
            //list out the relevant information, remembering to indent our information
            print_indent(file, indent);
            fprintf(file, "data_type = %s\n", root->specialization.variable_declaration.variable_type);
            print_indent(file, indent);
            fprintf(file, "variable_name = %s\n", root->specialization.variable_declaration.variable_name);
            //assignment is also a node, so recurse into that
            print_indent(file, indent);
            fprintf(file, "assignment = \n");
            print_ast(file, root->specialization.variable_declaration.assignment, indent + 1);
            break;

        case AST_PRINT_STATEMENT:
            //list parameters
            print_indent(file, indent);
            fprintf(file, "output = \n");
            //output is a node, recurse
            print_ast(file, root->specialization.print_statement.statement, indent + 1);
            break;

        case AST_BINARY_OPERATION:
            //left node
            print_indent(file, indent);
            fprintf(file, "left = \n");
            print_ast(file, root->specialization.binary_operation.left, indent + 1);
            //right node
            print_indent(file, indent);
            fprintf(file, "right = \n");
            print_ast(file, root->specialization.binary_operation.right, indent + 1);
            //operand
            print_indent(file, indent);
            fprintf(file, "operand = %s\n", root->specialization.binary_operation.operand);
            break;

        case AST_NEGATION:
            print_indent(file, indent);
            fprintf(file, "negate (-) = \n");
            print_ast(file, root->specialization.negation.factor, indent + 1);
            break;

        case AST_VARIABLE:
            print_indent(file, indent);
            fprintf(file, "variable_name = %s\n", root->specialization.variable.variable_name);
            print_indent(file, indent);
            fprintf(file, "value = UNRESOLVED\n");
            //print_ast(file, root->specialization.variable.value, indent + 1);
            break;

        case AST_INTEGER:
            print_indent(file, indent);
            fprintf(file, "value = %d\n", root->specialization.integer_literal.value);
            break;

        case AST_STRING:
            print_indent(file, indent);
            fprintf(file, "value = '%s'\n", root->specialization.string_literal.value);
            break;
    }
}

//helper
void print_indent(FILE* file, int indent) {
    for(int i = 0; i < indent; i++) {
        fprintf(file, "\t");
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
        case AST_NEGATION:
            free(node->specialization.negation.factor);
            break;
        case AST_VARIABLE:
            free(node->specialization.variable.value);
            free(node->specialization.variable.variable_name);
        case AST_INTEGER: 
            //not needed as not dynamically allocated memory lol
            //free(node->specialization.integer_literal.value);
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