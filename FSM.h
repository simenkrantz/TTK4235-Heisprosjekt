#ifndef __FSM_H__
#define __FSM_H__

/**
Initializes the hardware.
Drives up as long as the elevator hasn't reached a defined state.
@return 0 if hardware not initialized. 1 if initializing succeeded and
elevator is in a defined state.
*/
int
initialize_state_machine(void);


/**
Main program, handles state machine with a switch.
*/
void
state_machine(void);

#endif