/*
Code Generator

the code generator will use the abstract syntax tree to create code in assembly
it will use a recursive algorithm to traverse through the deepest nodes first
*/

#include "ast_node.h"
#include <stdio.h>

#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

//writes the assembly code
int generate_assembly_code(FILE* file, ASTNode* root);

#endif
