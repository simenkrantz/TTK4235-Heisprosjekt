#include <stdio.h>
#include <stdbool.h>

#include "elev.h"

#include "controller.h"
#include "emergency_stop.h"
#include "order.h"

void
stop_state(int array[4][3], int* motor_dir)
{
	if(elev_get_floor_sensor_signal() != -1 && elev_get_stop_signal()) {

		elev_set_motor_direction(DIRN_STOP);

		while(elev_get_stop_signal()) {
			elev_set_stop_lamp(1);
			continue;
		}

		elev_set_stop_lamp(0);
		open_close_door(array);

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 3; j++) {
                array[i][j] = 0;
        	}
        	turn_off_button_lights(i);
        }
	}

	else if(elev_get_stop_signal()) {

		elev_set_motor_direction(DIRN_STOP);

		while(elev_get_stop_signal()) {
			elev_set_stop_lamp(1);
			continue;
		}

		elev_set_stop_lamp(0);

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 3; j++) {
                array[i][j] = 0;
        	}
        	turn_off_button_lights(i);
        }
    }
}



int
order_handling_after_emergency_stop(int* motor_dir, int array[4][3], int last_floor)
{    
    int return_value = search_after_order_in_matrix(array);

    if(return_value == last_floor) {
        if(*motor_dir == -1) {
            elev_set_motor_direction(DIRN_UP);
            *motor_dir = 1;
        }
        else if(*motor_dir == 1) {
            elev_set_motor_direction(DIRN_DOWN);
            *motor_dir = -1;
        }
    }
    return return_value;
}