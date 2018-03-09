#ifndef __INCLUDE_CONTROLLER_H__
#define __INCLUDE_CONTROLLER_H__

/**
Turns on the light to the last passed floor, on the floor panel.
*/
void 
set_floor_indicator_lights(void);


/**
Turns on door lamp for 3 seconds, then turns it off again.
@param array is the 4 x 3 array containing the orders.
*/
void
open_close_door(int array[4][3]);


/**
If the ordered floor is higher than the last passed floor, 
set motor direction up.
If the ordered floor is lower than the last passed floor,
set motor direction down.
@param order_floor is the floor where it is an order.
@param last_floor is the last floor the elevator passed.
@param motor_dir is a pointer to the last motor direction.
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