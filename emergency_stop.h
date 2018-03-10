#ifndef __INCLUDE_EMERGENCY_STOP_H__
#define __INCLUDE_EMERGENCY_STOP_H__

/**
Handles spec. 4.6, when the stop button is pressed.
Erases orders, turns off all lights.
@param array is the 4 x 3 array containing the orders.
@param motor_dir is a pointer to the last motor direction.
*/
void
stop_state(int array[4][3], int* motor_dir);


/**
Handles the first order after emergency stop button is pressed.
Sends the elevator in the correct direction according to order.
@return Default -1. If order found, returns the found floor.
@param motor_dir is a pointer to the last motor direction.
@param array is the 4 x 3 array containing the orders.
@param last_floor is the last floor the elevator passed.
*/
int
order_handling_after_emergency_stop(int* motor_dir, int array[4][3], int last_floor);


#endif