#include <stdio.h>
#include <stdbool.h>
#include "elev.h"

#include "controller.h"
#include "emergency_stop.h"
#include "order.h"

bool
stop_state(int array[4][3], int ord_floor, int last_floor, int* motor_dir)
{
	bool emergency_stop = false;
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

        emergency_stop = true;
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

        if(ord_floor == last_floor) {
        	if(*motor_dir == -1) {
        		elev_set_motor_direction(DIRN_UP);
        		*motor_dir = 1;
        	}
        	else if(*motor_dir == 1) {
        		elev_set_motor_direction(DIRN_DOWN);
        		*motor_dir = -1;
        	}
        }

        emergency_stop = true;
	}
	return emergency_stop;
}