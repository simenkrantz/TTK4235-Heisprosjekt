#include <time.h>
#include <stdio.h>
#include "elev.h"
#include "io.h"

#include "order.h"

// Delay time in seconds
static int delay_time = 3;

void
set_floor_indicator_lights(void)
{
    int current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
      	elev_set_floor_indicator(current_floor);
    }
}

void
open_close_door(int array[4][3])
{
	elev_set_door_open_lamp(1);
	time_t start_time = time(NULL), current_time;

	while(1) {
		current_time = time(NULL);
		if((current_time - start_time) == delay_time) {
			break;
		}
		set_order_matrix_and_corresponding_lights(array);
	}

	elev_set_door_open_lamp(0);
}

void
set_motor_direction(int order_floor, int last_floor, int* motor_dir)
{
	if(order_floor > last_floor) {
	    elev_set_motor_direction(DIRN_UP);
	    *motor_dir = 1;
	}
	else if(order_floor < last_floor) {
	   	elev_set_motor_direction(DIRN_DOWN);
	   	*motor_dir = -1;
	}
}

void
turn_off_button_lights(int floor)
{
	if(floor == 0) {
	    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	    elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    else if(floor == 3) {
       	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
       	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    }
    else if(floor == 1 || floor == 2){
    	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    	elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
}
