#include "include/asm_generation.h"
#include <stdlib.h>
#include <stdio.h>

/*
Node To Assembly Function

writes the appropriate assembly based on the node type

FILE* file: the file we are writing the asm to
ASTNode* node: the current node we are translating
SymbolTable* table: the symbol table containing all our symbols
RegisterManager* manager: the manager keeping the registers in check

return: can return information about last used register
*/

int node_to_asm(FILE* file, ASTNode* node, SymbolTable* table, RegisterManager* manager) {
    //switch on the node type
    switch(node->type) {
        case AST_PROGRAM:
            //go through children nodes
            for(int i = 0; i < node->children->num_items; i++) {
                node_to_asm(file, node->children->array[i], table, manager);
            }
            break;
        case AST_VARIABLE_DECLARATION:
            //
            break;
        case AST_PRINT_STATEMENT: {
            //evaluate the statement inside the print statement
            int result_reg = node_to_asm(file, node->specialization.print_statement.statement, table, manager);

            // **just work with integers right now, print strings later**
            fprintf(file, "\t//print\n");

            //make sure the result reg isn't 0 or 1 because we need to use them for arguments
            if(result_reg == 0 || result_reg == 1) {
                //create a safe register and update the old register to be free
                int safe_reg = allocate_safe_register(manager, result_reg);
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
            //free used register
            free_register(manager, result_reg);
            break;
        }
            
        case AST_BINARY_OPERATION: {
            //get the registers with the left and right statements
            int left_reg = node_to_asm(file, node->specialization.binary_operation.left, table, manager);
            int right_reg = node_to_asm(file, node->specialization.binary_operation.right, table, manager);
            //allocate space for a register that will store the value
            int result_reg = allocate_register(manager);

            //switch on the operand (make sure to dereference)
            fprintf(file, "\t//binary operation\n");
            switch(*node->specialization.binary_operation.operand) {
                case '+':
                    //add the two values 
                    fprintf(file, "\tadd x%d, x%d, x%d\n", result_reg, left_reg, right_reg);
                    break;
                case '-':
                    fprintf(file, "\tsub x%d, x%d, x%d\n", result_reg, left_reg, right_reg);
                    break;
                case '*':
                    fprintf(file, "\tmul x%d, x%d, x%d\n", result_reg, left_reg, right_reg);
                    break;
                case '/':
                    fprintf(file, "\tsdiv x%d, x%d, x%d\n", result_reg, left_reg, right_reg);
                    break;
            }
            //free the used left and right registers
            free_register(manager, left_reg);
            free_register(manager, right_reg);
            //return the register containing result
            return result_reg;
            break;
        }
        case AST_NEGATION:
          
            break;
        case AST_VARIABLE:
           
            break;
        case AST_INTEGER: {
            //move value to a free register
            int reg = allocate_register(manager);
            fprintf(file, "\t//move value to register\n");
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

/*
Generate Assembly Function

generates all the assembly and writes it to a file

FILE* file: the file we are writing to
ASTNode* root: the root of the AST (the program node)
SymbolTable* table: the symbol table with all important symbol information
*/

void generate_assembly(FILE* file, ASTNode* root, SymbolTable* table) {
    //setup

    fprintf(file, "//setup\n");
    //text section
    fprintf(file, ".text\n");
    //define entry point
    fprintf(file, ".global _main\n");
    //byte align to 4
    fprintf(file, ".balign 4\n");
    fprintf(file, "\n");

    //allocate space and setup stack

    fprintf(file, "//entry point and stack setup\n");
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
    fprintf(file, "\n");

    //create a register tracker
    RegisterManager* manager = init_register_manager();
    //call recursive algorithm and generate assembly code
    fprintf(file, "\t//Code Gen Starts Here: \n\n");
    node_to_asm(file, root, table, manager);

    //exit from main
    fprintf(file, "\n");
    fprintf(file, "\t//exit and clean up\n");
    fprintf(file, "\tmov x0, #0\n");
    fprintf(file, "\tldp x29, x30, [sp, #16]\n");
    fprintf(file, "\tadd sp, sp, #%d\n", stack_size);
    fprintf(file, "\tret\n");

    //format strings for print statements
    fprintf(file, "\n");
    fprintf(file, "//data\n");
    fprintf(file, "integerformatstr:\n");
    fprintf(file, "\t.asciz \"%%d\\n\"\n\n");
    fprintf(file, "stringformatstr:\n");
    fprintf(file, "\t.asciz \"%%s\\n\"");

    //free the register manager once done
    free(manager);
}
