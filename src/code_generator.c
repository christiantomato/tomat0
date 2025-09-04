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
           
            break;   
        case AST_VARIABLE_DECLARATION:
   
            break;
        case AST_PRINT_STATEMENT:
            
            break;
        case AST_BINARY_OPERATION:
            
            break;
        case AST_NEGATION:
          
            break;
        case AST_VARIABLE:
           
            break;
        case AST_INTEGER:
 
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

    //recursive algorithm goes here (inorder traversal)



    //exit
    //fprintf(file, "\tmov w0, #0\n");
    //fprintf(file, "\tret\n");



    return 0;
}