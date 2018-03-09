#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__

/**
@return the matrix row to check next.
@param motor_dir is a pointer to the last motor direction.
@param array is the 4 x 3 array containing the orders.
@param last_floor is the last floor the elevator passed.
*/
int
get_matrix_index(int* motor_dir, int array[4][3], int last_floor);


/**
Checks if an order button is pressed.
If so, the corresponding light is turned on.
@param array is the 4 x 3 array containing the orders.
*/
void
set_order_matrix_and_corresponding_lights(int array[4][3]);

/**
Handles an order when elevator arrives at an ordered floor.
Erase the order for the given floor and turn off the lights.
@param motor_dir is a pointer to the last motor direction.
@param array is the 4 x 3 array containing the orders.
@param last_floor is the last floor the elevator passed.
*/
void
stop_handling_at_order_floor(int* motor_dir, int array[4][3], int last_floor);


#endif