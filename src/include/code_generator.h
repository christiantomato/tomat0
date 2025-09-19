/*
Code Generator

the code generator will use the abstract syntax tree to create code in assembly
it will use a recursive algorithm to traverse through the deepest nodes first
*/

#include "ast_node.h"
#include "symbol_table.h"
#include "register_manager.h"
#include <stdio.h>

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

//recursively writes the assembly based on node type
int node_to_asm(FILE* FILE, ASTNode* node, SymbolTable* table, RegisterManager* manager);
//writes the assembly code
void generate_assembly_code(FILE* file, ASTNode* root, SymbolTable* table);

#endif
