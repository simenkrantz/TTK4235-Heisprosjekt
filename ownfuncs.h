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
change_of_motor_direction(void);


/**
Returns 0 if no order button is pressed.
BUTTON_CALL_UP returns positive values. 1: 1st floor, 2: 2nd floor, 3: 3rd floor.
BUTTON_CALL_DOWN returns negative values. -1: 2nd floor, -2: 3rd floor, -3: 4th floor. 
*/
int
get_button_outside_pressed(void);


/**
Returns -1 if no order button inside the elevator is pressed.
Returns 0 for 1st floor, 1 for 2nd floor, 2 for 3rd floor, 3 for 4th floor.
*/
int
get_order_button_inside_pressed(void);


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


/**
Opens the door, sets the doorlight for 3 seconds.
*/
void open_close_door(void);


#endif