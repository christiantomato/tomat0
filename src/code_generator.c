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
            //determine the data type of the print statement
            if(node->specialization.print_statement.statement->type == AST_INTEGER) {
                fprintf(file, "\tadr x0, integerformatstr\n");
                fprintf(file, "\tmov x1, #%d\n", node->specialization.print_statement.statement->specialization.integer_literal.value);
                fprintf(file, "\tstr x1, [sp]\n");
            }
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
            //fprintf(file, "\tmov w0, #%d\n", node->specialization.integer_literal.value);
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
    fprintf(file, ".balign 4\n");
    fprintf(file, "\n");

    //setup stack in main
    fprintf(file, "_main:\n");
    fprintf(file, "\tsub sp, sp, #64\n");
    fprintf(file, "\tstp x29, x30, [sp, #16]\n");
    fprintf(file, "\tmov x29, sp\n");
    fprintf(file, "\n");

    //call to recursive algorithm which will generate the code
    node_to_asm(file, root);

    //exit from main
    fprintf(file, "\n");
    fprintf(file, "\tmov x0, #0\n");
    fprintf(file, "\tldp x29, x30, [sp, #16]\n");
    fprintf(file, "\tadd sp, sp, #64\n");
    fprintf(file, "\tret\n");

    //format strings for print statements
    fprintf(file, "\n");
    fprintf(file, "integerformatstr:\n");
    fprintf(file, "\t.asciz \"%%d\\n\"\n");
    fprintf(file, "stringformatstr:\n");
    fprintf(file, "\t.asciz \"%%s\\n\"");


    return 0;
}