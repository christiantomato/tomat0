/*
Code Generator

the code generator will use the abstract syntax tree to generate the respective code in assembly
it will use a recursive algorithm to traverse through the deepest nodes first
*/

#include "ast_node.h"
#include "symbol_table.h"
#include "register_manager.h"
#include <stdio.h>

#ifndef ASM_GENERATION_H
#define ASM_GENERATION_H

//recursively writes the assembly based on node type
int node_to_asm(FILE* FILE, ASTNode* node, SymbolTable* table, RegisterManager* manager);
//main function to write the assembly to a file
void generate_assembly(FILE* file, ASTNode* root, SymbolTable* table);

#endif
