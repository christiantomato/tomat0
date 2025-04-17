//making a generic list in C, to help me store the children of the AST nodes (as they are of unknown size)
#include <stdlib.h>
#include <stdbool.h>

#ifndef ARR_LIST
#define ARR_LIST

typedef struct generic_array_list {
    //size of the data type
    size_t data_size;
    //number of items in list
    unsigned int num_items;
    //current capacity of the list
    unsigned int current_capacity;
    //the array holding the data items (double pointer, as it holds pointers to data)
    void** array;
} List;

//methods we need to implement for the list structure

//initializtion of the list
List* init_list(size_t data_size, unsigned int init_capacity);
//adds data to the end of the list - use a void pointer, as we don't know the type of the data. 
void list_add(List* list, void* data);
//remove data at a specified index, and the list will shift over so there is no gaps
void list_remove(List* list, unsigned int index);
//list helper method to expand capacity
void expand_capacity(List* list);
//check for empty list
bool is_empty(List* list);
//check for max capacity
bool is_max_capacity(List* list);
//free all memory used by the list
int free_list(List* list);

#endif
