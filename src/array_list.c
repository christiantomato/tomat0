//implement our list
#include "include/array_list.h"
#include <stdio.h>

//list initializor
List* init_list(size_t data_size, unsigned int init_capacity) {
    //memory allocate for list
    List* list = malloc(sizeof(list));
    //set data size
    list->data_size = data_size;
    //start at 0 items
    list->num_items = 0;
    //set capacity
    list->current_capacity = init_capacity;
    //initialize the amount of locations in memory available (our array holds void pointers)
    list->array = malloc(init_capacity * sizeof(void*));
    //return the list
    return list;
}

//adds data to our list 
void list_add(List* list, void* data) {
    //if we are at max capacity, expand
    if(is_max_capacity(list)) {
        expand_capacity(list);
    }
    //allocate the data size to the next memory location we are going to add to
    list->array[list->num_items] = malloc(list->data_size);
    //add the data item
    list->array[list->num_items] = data;
    //increase count
    list->num_items++;
}

//removes data from our list
void list_remove(List* list, unsigned int index) {
    //make sure the index is valid
    if(index >= list->num_items) {
        //bad
        printf("cannot remove");
        return;
    }
    //goodbye data
    list->array[index] = NULL;
    //shift stuff over
    for(int i = index + 1; i < list->num_items; i++) {
        //shift to previous
        list->array[i-1] = list->array[i];
    }
    //update item count
    list->num_items--;
}

//helper method to expand list capacity
void expand_capacity(List* list) {
    //create a new array with greater capacity, lets say double the original
    void** new_array = malloc(list->current_capacity * 2 * sizeof(void*));
    //update the current capacity
    list->current_capacity = list->current_capacity * 2;
    //copy the values
    for(int i = 0; i < list->num_items; i++) {
        //allocate the space for the new array location
        new_array[i] = malloc(list->data_size);
        new_array[i] = list->array[i];
    }
    //free the old list array
    free(list->array);
    //give it the new array
    list->array = new_array;
}

//is list empty
bool is_empty(List* list) {
    return list->num_items == 0;
}

//is list full
bool is_max_capacity(List* list) {
    return list->num_items == list->current_capacity;
}

int free_list(List* list) {
    if(list == NULL) {
        //failure
        return 1;
    }
    //free all contents in the array, then the array, then the list itself. 
    for(int i = 0; i < list->num_items; i++) {
        //free pointer to data in the array
        free(list->array[i]);
    }
    //free pointer to the array
    free(list->array);
    //free the list
    free(list);
    //success
    return 0;
}
