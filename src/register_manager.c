#include "include/register_manager.h"
#include <stdlib.h>

RegisterManager* init_register_manager() {
    //allocate for tracker
    RegisterManager* manager = malloc(sizeof(RegisterManager));
    //set up boolean array keep track of which registers are free (currently all, x0-x15 we can use)
    for(int i = 0; i < 16; i++) {
        manager->registers[i] = true;
    }
    return manager;
}

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

void free_register(RegisterManager* manager, int register_num) {
    manager->registers[register_num] = true;
}

