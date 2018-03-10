#ifndef __INCLUDE_CONTROLLER_H__
#define __INCLUDE_CONTROLLER_H__

/**
Manages floor indicator lights according to last passed floor.
*/
void 
set_floor_indicator_lights(void);


/**
Turns on door lamp for 3 seconds, then turns it off again.
Enables taking orders while door is open.
@param array is the 4 x 3 array containing the orders.
*/
void
open_close_door(int array[4][3]);


/**
Sets motor direction up or down, based on the elevators last passed floor and the target floor.
@param order_floor is the target floor of the elevator.
@param last_floor is the last floor the elevator passed.
@param motor_dir is a pointer to the last motor direction. 1 is UP, -1 is DOWN.
*/
void
set_motor_direction(int order_floor, int last_floor, int* motor_dir);


/**
Turns off all button lights in a given floor.
@param floor is the floor in which to turn off all lights.
*/
void
turn_off_button_lights(int floor);

#endif