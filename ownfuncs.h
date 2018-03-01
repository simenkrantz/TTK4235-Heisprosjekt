#ifndef __INCLUDE_OWNFUNCS_H__
#define __INCLUDE_OWNFUNCS_H__

// Sets the floorlight for the last passed floor.

// CHANGE NAME to set_floor_indicator_lights() ?
void 
set_floor_lights(void);

/**

*/
void
open_close_door(int array[4][3]);


/**
Sets the right element in the order array.
Sets the corresponding button light high.
@param array takes in array
*/

// CHANGE NAME to and_corresponding_light ?
void
set_order_list_and_lights(int array[4][3]);


/**
Checks if an UP or DOWN button is pressed in the given floor
@param array is the array containing orders
@param floor is the floor we want to check
Returns -1 if DOWN button pressed, 1 if UP button pressed, 0 if no UP/DOWN button is pressed
*/
int
check_up_down_button_pressed(int array[4][3], int floor);


/**
Opens the door, sets the doorlight for 3 seconds.
*/
void
open_close_door(int array[4][3]);

/**
Turns off all lights in the given direction the elevator have.
If UP and DOWN is pressed in 2nd floor, and the elevator is coming down from 3rd going to 1st,
the UP light is turned off once the elevator comes back up from 1st floor
@param floor is the given floor we wants to turn off the lights in
@param motor_dir is the current motor direction
*/
void
turn_off_button_lights(int floor, int* motor_dir);


void
stop_state(int array[4][3], int ord_floor, int last_floor, int* motor_dir);


#endif