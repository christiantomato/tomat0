#include "include/register_manager.h"
#include <stdlib.h>


/*
Initialize Register Manager Function

intializes the register manager

return: pointer to the register manager structure
*/

RegisterManager* init_register_manager() {
    //allocate for tracker
    RegisterManager* manager = malloc(sizeof(RegisterManager));
    //set up boolean array keep track of which registers are free (currently all, x0-x15 we can use)
    for(int i = 0; i < 16; i++) {
        manager->registers[i] = true;
    }
    return manager;
}

/*
Allocate Register Function

allocates the next available register for use

RegisterManager* manager: the register manager

return: the number of the register that is allocated
*/

int allocate_register(RegisterManager* manager) {
    //check which register is free
    for(int i = 0; i < 16; i++) {
        if(manager->registers[i]) {
            //set as allocated and return
            manager->registers[i] = false;
            return i;
        }
    }
    //otherwise no registers free
    return -1;
}

/*
Allocate Safe Register

allocates the next available register from x8-x15, as the lower ones might be used for arguments

RegisterManager* manager: the register manager
int old_register: the old register which was being used, which now must be freed for an argument

return: the value of the new register
*/

int allocate_safe_register(RegisterManager* manager, int old_register) {
    for(int i = 8; i < 16; i++) {
        if(manager->registers[i]) {
            //set as allocated and return
            manager->registers[i] = false;
            //free the old register
            free_register(manager, old_register);
            return i;
        }
    }
    //otherwise bad
    return -1;
}

/*
Free Register Function

frees the register once it no longer needs to be used

RegisterManager* manager: the register manager
int register_num: the register to be freed
*/

void free_register(RegisterManager* manager, int register_num) {
    manager->registers[register_num] = true;
}
