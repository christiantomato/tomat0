/*
Register Tracker Structure

*/

#include <stdbool.h>

#ifndef REGISTER_TRACKER_H
#define REGISTER_TRACKER_H

typedef struct register_tracker_struct {
    //true if free, false otherwise
    bool registers[16];
} RegisterTracker;

//initializes the tracker
RegisterTracker* init_register_tracker();
//returns the number of the register that was allocated
int allocate_register(RegisterTracker* tracker);
//returns a register from x8-x15 so old register isn't clobbered by function arguments
int allocate_safe_register(RegisterTracker* tracker, int old_register);
//frees the specified register
void free_register(RegisterTracker* tracker, int register_num);

#endif