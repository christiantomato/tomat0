//making a generic list in C, to help me store the children of the AST nodes (as they are of unknown size)
#include <stdlib.h>
#include <stdbool.h>

typedef struct generic_list {
    //size of the data type
    size_t data_size;
    //number of items in list
    unsigned int num_items;
    //current capacity of the list
    unsigned int current_capacity;
    //the array holding the data items (double pointer, as it holds pointers to data)
    void** array;
} list;

//methods we need to implement for the list structure

//initializtion of the list
list* init_list(size_t data_size, unsigned int init_capacity);
//add data to the list - use a void pointer, as we don't know the type of the data. 
void add(list* list, void* data);
//list helper method to expand capacity
void expand_capacity(list* list);
//check for empty list
bool is_empty(list* list);
//check for max capacity
bool is_max_capacity(list* list);
//free all memory used by the list
int free_list(list* list);