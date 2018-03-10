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
