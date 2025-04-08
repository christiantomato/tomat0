//making a generic list in C, to help me store the children of the AST nodes (as they are of unknown size)
#include "stdlib.h"

typedef struct generic_list {
    //size of the data type
    size_t data_size;

} list;

//methods we need to implement for the list structure

//initializtion of the list
list* init_list(size_t data_size);
//add data to the list - use a void pointer, as we don't know the type of the data. 
list* add(list* list, void* data, size_t data_size);
bool is_empty(list);