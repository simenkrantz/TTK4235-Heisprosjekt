#ifndef __INCLUDE_OWNFUNCS_H__
#define __INCLUDE_OWNFUNCS_H__

/**
Compressed initialize function to have a more
straightforward main function.
Line 12-29 in the original main.c from BB.
*/
void
initialize(void);


//Sets the floorlight for the last passed floor.
void
set_floor_lights(void);


//Delays action for a given number of milliseconds.
void
time_delay(int millisecs);


//Turn direction at endpoints and set floor indicators.
void
change_of_motor_direction(void);


/**
Returns 0 if no order button is pressed.
BUTTON_CALL_UP returns positive values. 1 for 1st floor, 2 for 2nd floor, 3 for 3rd floor.
BUTTON_CALL_DOWN returns negative values. -1 for 2nd floor, -2 for 3rd floor, -3 for 4th floor. 
*/
int
button_outside_pressed(void);

/**
Returns -1 if no order button inside the elevator is pressed.
Returns 0 for 1st floor, 1 for 2nd floor, 2 for 3rd floor, 3 for 4th floor.
*/
int
order_button_inside_pressed(void);

/**
Sets the lights in the up/down buttons
outside the elevator.
@param o_b_p ranges from negative 3 to positive 3, given by button_outside_pressed()
@param value turns on or off the given light. 0 turns off, nonzero turns on.
*/
void
set_outside_order_lights(int outside_button_pressed, int value);

/**
Sets the order lights inside the elevator (1st - 4th floor buttons).
@param f_o_b is given by order_button_inside_pressed().
@param value turns on or off the given light. 0 turns off, nonzero turns on.
*/
void
set_floor_order_lights(int floor_order_button, int value);


#endif