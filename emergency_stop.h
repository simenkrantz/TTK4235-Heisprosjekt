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


#endif