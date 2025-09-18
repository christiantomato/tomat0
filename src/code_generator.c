#include "include/code_generator.h"
#include <stdlib.h>
#include <stdio.h>

/*
Generate Assembly Code Function

*/

int node_to_asm(FILE* file, ASTNode* node, SymbolTable* table, RegisterTracker* tracker) {
    //switch on the node type
    switch(node->type) {
        case AST_PROGRAM:
            //go through children nodes
            for(int i = 0; i < node->children->num_items; i++) {
                node_to_asm(file, node->children->array[i], table, tracker);
            }
            break;
        case AST_VARIABLE_DECLARATION:
            break;
        case AST_PRINT_STATEMENT: {
            //evaluate the statement inside the print statement
            int result_reg = node_to_asm(file, node->specialization.print_statement.statement, table, tracker);

            // **just work with integers right now, print strings later**

            //make sure the result reg isn't 0 or 1 because we need to use them for arguments
            if(result_reg == 0 || result_reg == 1) {
                //create a safe register and update the old register to be free
                int safe_reg = allocate_safe_register(tracker, result_reg);
                //move the value into the safe register
                fprintf(file, "\tmov x%d, x%d\n", safe_reg, result_reg);
                //update the value of the result register to safe register value
                result_reg = safe_reg;
            }

            //get the address of the integer format string
            fprintf(file, "\tadr x0, integerformatstr\n");
            //move the value in the result register to register x1
            fprintf(file, "\tmov x1, x%d\n", result_reg);
            fprintf(file, "\tstr x1, [sp]\n");
            fprintf(file, "\tbl _printf\n");
            break;
        }
            
        case AST_BINARY_OPERATION:
            
            break;
        case AST_NEGATION:
          
            break;
        case AST_VARIABLE:
           
            break;
        case AST_INTEGER: {
            //move value to a free register
            int reg = allocate_register(tracker);
            fprintf(file, "\tmov x%d, #%d\n", reg, node->specialization.integer_literal.value);
            //return the register number
            return reg;
            break;
        }
            
        case AST_STRING:
            break;
    }


    return 0;
}

int generate_assembly_code(FILE* file, ASTNode* root, SymbolTable* table) {
    //setup

    //text section
    fprintf(file, ".text\n");
    //define entry point
    fprintf(file, ".global _main\n");
    //byte align to 4
    fprintf(file, ".balign 4\n");
    fprintf(file, "\n");

    //allocate space and setup stack

    fprintf(file, "_main:\n");
    //determine space to allocate for variables 
    int var_space = -(table->current_offset);
    //determine total space needed (variables + saved register x29 and x30)
    int needed_space = var_space + 16;
    //round up to nearest 16 byte multiple
    int stack_size = (needed_space + 15) & ~15;
    //allocate the space
    fprintf(file, "\tsub sp, sp, #%d\n", stack_size);
    //store registers x29 and x30 above the current stack pointer (at the location where variables end)
    fprintf(file, "\tstp x29, x30, [sp, #%d]\n", var_space);  // #24
    //set the frame pointer x29 to point to saved registers location (variables are under at -8, -16, etc.)
    fprintf(file, "\tadd x29, sp, #%d\n", var_space);

    //create a register tracker
    RegisterTracker* tracker = init_register_tracker();
    //call recursive algorithm and generate assembly code
    node_to_asm(file, root, table, tracker);

    //exit from main
    fprintf(file, "\n");
    fprintf(file, "\tmov x0, #0\n");
    fprintf(file, "\tldp x29, x30, [sp, #16]\n");
    fprintf(file, "\tadd sp, sp, #%d\n", stack_size);
    fprintf(file, "\tret\n");

    //format strings for print statements
    fprintf(file, "\n");
    fprintf(file, "integerformatstr:\n");
    fprintf(file, "\t.asciz \"%%d\\n\"\n");
    fprintf(file, "stringformatstr:\n");
    fprintf(file, "\t.asciz \"%%s\\n\"");


    return 0;
}