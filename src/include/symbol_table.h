/*
Symbol Table Structure

responsible for keeping track of symbols like variables and function names
this way we can determine the values of these identifiers by looking them up

List* symbols: the array list that holds each symbol
int current_offset: stores the integer representing the last place a symbol was stored in memory
*/

#include "array_list.h"

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

//define a symbol which will be used in our symbol table (name and type should be immutable)
typedef struct symbol_struct {
    const char* name;
    const char* type;
    int memory_offset;
} Symbol;

//main structure
typedef struct symbol_table_struct {
    //linear storage for now
    List* symbols;
    int current_offset;
} SymbolTable;

//create the symbol table
SymbolTable* init_table();
//add a symbol to table
void add_to_table(SymbolTable* table, const char* name, const char* type);
//find a symbol already in table
Symbol* look_up_symbol(SymbolTable* table, const char* name);

#endif