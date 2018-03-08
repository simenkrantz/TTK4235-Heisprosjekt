#ifndef __INCLUDE_CONTROLLER_H__
#define __INCLUDE_CONTROLLER_H__

void 
set_floor_indicator_lights(void);


void
open_close_door(int array[4][3]);


void
set_motor_direction(int order_floor, int last_floor, int* motor_dir);


void
turn_off_button_lights(int floor);

#endif