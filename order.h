#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__

/**
Search for button pressed in the order matrix,
based on the elevators direction and its last passed floor.
@return the matrix column to check for next order.
@param motor_dir is a pointer to the last motor direction. 1 is UP, -1 is DOWN.
@param array is the 4 x 3 array containing the orders.
@param last_floor is the last floor the elevator passed.
*/
int
get_button_index(int* motor_dir, int array[4][3], int last_floor);


/**
Checks if an order button is pressed.
If so, the corresponding light is turned on and the order is added to the order matrix.
@param array is the 4 x 3 array containing the orders.
*/
void
set_order_matrix_and_corresponding_lights(int array[4][3]);

/**
Open and close the door. Erase the order for the given floor and turn off the lights.
@param array is the 4 x 3 array containing the orders.
@param last_floor is the last floor the elevator passed.
*/
void
stop_handling_at_order_floor(int array[4][3], int last_floor);


/**
Searches through the order matrix for an order.
Enables taking orders while the function is called.
@return Default is -1. If order found, returns the found floor.
@param array is the 4 x 3 array containing the order. 
*/
int
search_after_order_in_matrix(int array[4][3]);

#endif