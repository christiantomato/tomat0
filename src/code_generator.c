#include "include/code_generator.h"
#include <stdlib.h>
#include <stdio.h>

/*
Generate Assembly Code Function

*/

int node_to_asm(FILE* file, ASTNode* node) {

    //switch on the node type
    switch(node->type) {
        case AST_PROGRAM:
            //go through children nodes
            for(int i = 0; i < node->children->num_items; i++) {
                node_to_asm(file, node->children->array[i]);
            }
            break;
        case AST_VARIABLE_DECLARATION:
   
            break;
        case AST_PRINT_STATEMENT:
            //generate code for what we are printing
            node_to_asm(file, node->specialization.print_statement.statement);
            //generate the assembly code for printing something to terminal
            fprintf(file, "\tbl _printf\n");
            break;
        case AST_BINARY_OPERATION:
            
            break;
        case AST_NEGATION:
          
            break;
        case AST_VARIABLE:
           
            break;
        case AST_INTEGER:
            //move value to register
            fprintf(file, "\tmov w0, #%d\n", node->specialization.integer_literal.value);
            break;
        case AST_STRING:
         
            break;
    }


    return 0;
}

int generate_assembly_code(FILE* file, ASTNode* root) {
    //setup
    fprintf(file, ".text\n");
    fprintf(file, ".global _main\n");
    fprintf(file, ".align 2\n\n");
    fprintf(file, "_main:\n");

    //recursive algorithm
    node_to_asm(file, root);


    //exit
    fprintf(file, "\tmov w0, #0\n");
    fprintf(file, "\tret\n");



    return 0;
}