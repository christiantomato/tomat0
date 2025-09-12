#include "include/symbol_table.h"

/*


*/

#include <stdlib.h>

SymbolTable* init_table() {
    //allocate memory for the symbol table 
    SymbolTable* table = malloc(sizeof(SymbolTable));
    //set up symbols array

    //set up inital count
    table->count = 0;

    return table;

}

void add_to_table(SymbolTable* table, const char* name, const char* type) {



}

void look_up_symbol(SymbolTable* table, const char* name) {

}