#ifndef __INCLUDE_OWNFUNCS_H__
#define __INCLUDE_OWNFUNCS_H__

/**
Compressed initialize function to have a more
straightforward main function.
Line 12-29 in the original main.c from BB.
*/
void
initialize(void);


// Sets the floorlight for the last passed floor.
void
set_floor_lights(void);


// Delays action for a given number of milliseconds.
void
time_delay(int millisecs);


// Turn direction at endpoints.
void
change_of_motor_direction(int* motor_dir);


/**
Sets the right element in the order array
@param array takes in array
*/
void
set_order_list(int array[4][3]);


/**
Checks if an UP or DOWN button is pressed in the given floor
@param array is the array containing orders
@param floor is the floor we want to check
Returns -1 if DOWN button pressed, 1 if UP button pressed, 0 if no UP/DOWN button is pressed
*/
int
check_up_down_button_pressed(int array[4][3], int floor);

/**
Sets the UP/DOWN lights on or off outside the elevator.
@param up_or_down decides if a UP or DOWN light is set. 0 is down, 1 is up.
@param floor is the given floor. Must be 0-3.
@param on_or_off: 0 is turning light off, 1 is on.
*/
void
set_outside_order_lights(int up_or_down, int floor, int on_or_off);


/**
Sets the order lights inside the elevator (1st - 4th floor buttons).
@param floor is the given floor. Must be 0-3.
@param on_or_off: 0 is off, 1 is on.
*/
void
set_floor_order_lights(int floor, int on_or_off);

int
get_motor_dir();


/**
Opens the door, sets the doorlight for 3 seconds.
*/
void
open_close_door(void);







#endif