/*
Symbol Table Structure

responsible for keeping track of symbols like variables and function names
this way we can determine the values of these identifiers by looking them up
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct symbol_struct {
    char* name;
    char* type;
} Symbol;

typedef struct symbol_table_struct {
    Symbol symbols;
    int count;
} SymbolTable;

SymbolTable* init_table();
void add_to_table(SymbolTable* table, const char* name, const char* type);
void look_up_symbol(SymbolTable* table, const char* name);

#endif