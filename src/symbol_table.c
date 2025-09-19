#include "include/symbol_table.h"
#include <stdlib.h>
#include <string.h>

/*
Initialize Table Function

creates a symbol table with a given initial capacity

*/

SymbolTable* init_table() {
    //allocate memory for the symbol table 
    SymbolTable* table = malloc(sizeof(SymbolTable));
    //set up symbols array with some initial capacity
    table->symbols = init_list(10);
    //start at 0, allocate 8 bytes for each variable once added
    table->current_offset = 0;
    return table;
}

/*
Add To Table Function

*/

void add_to_table(SymbolTable* table, const char* name, const char* type) {
    //create the symbol and add it to the list
    Symbol* new_symbol = malloc(sizeof(Symbol));
    new_symbol->name = name;
    new_symbol->type = type;
    //allocate 8 bytes for the new symbol
    new_symbol->memory_offset = table->current_offset - 8;
    //update current offset for table
    table->current_offset = new_symbol->memory_offset;
    //add to the list
    list_add(table->symbols, new_symbol);
}

/*
Look Up Symbol Function

*/

Symbol* look_up_symbol(SymbolTable* table, const char* name) {
    //do a linear search
    for(int i = 0; i < table->symbols->num_items; i++) {
        Symbol* curr_symbol = table->symbols->array[i];
        if(strcmp(curr_symbol->name, name) == 0) {
            return curr_symbol;
        }
    }
    //nothing found
    return NULL;
}
