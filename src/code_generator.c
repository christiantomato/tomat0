#include "include/code_generator.h"
#include <stdlib.h>
#include <stdio.h>

/*
Generate Assembly Code Function

*/

int generate_assembly_code(FILE* file, ASTNode* root) {
    //setup
    fprintf(file, ".text\n");
    fprintf(file, ".global _main\n");
    fprintf(file, ".align 2\n\n");
    fprintf(file, "_main:\n\t");

    //recursive algorithm goes here



    return 0;
}