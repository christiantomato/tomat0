#include "include/register_tracker.h"
#include <stdlib.h>

RegisterTracker* init_register_tracker() {
    //allocate for tracker
    RegisterTracker* tracker = malloc(sizeof(RegisterTracker));
    //set up boolean array keep track of which registers are free (currently all, x0-x15 we can use)
    for(int i = 0; i < 16; i++) {
        tracker->registers[i] = true;
    }
    return tracker;
}

int allocate_register(RegisterTracker* tracker) {
    //check which register is free
    for(int i = 0; i < 16; i++) {
        if(tracker->registers[i]) {
            //set as allocated and return
            tracker->registers[i] = false;
            return i;
        }
    }
    //otherwise no registers free
    return -1;
}

int allocate_safe_register(RegisterTracker* tracker, int old_register) {
    for(int i = 8; i < 16; i++) {
        if(tracker->registers[i]) {
            //set as allocated and return
            tracker->registers[i] = false;
            //free the old register
            free_register(tracker, old_register);
            return i;
        }
    }
    //otherwise bad
    return -1;
}

void free_register(RegisterTracker* tracker, int register_num) {
    tracker->registers[register_num] = false;
}

