#ifndef __INCLUDE_EMERGENCY_STOP_H__
#define __INCLUDE_EMERGENCY_STOP_H__

#include <stdbool.h>

bool
stop_state(int array[4][3], int ord_floor, int last_floor, int* motor_dir);



#endif