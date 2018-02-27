#include "elev.h"
#include <time.h>
#include <stdio.h>

#include "ownfuncs.h"

// Delay time in milliseconds
#define DELAY_TIME 3000

void
set_floor_lights(void)
{
        int current_floor = elev_get_floor_sensor_signal();
        if (current_floor != -1){
        	elev_set_floor_indicator(current_floor);
        }
}


// NEED TO ORDER IN THIS FUNCTION!
void
time_delay(int millisecs)
{
	long pause;
	clock_t now, then;
	pause = millisecs*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while ((now-then) < pause) {
		now = clock();

		// Have set_order_list_and_lights() here ?
	}
}


// DO we need this ? 
void
change_of_motor_direction(int* motor_dir)
{
	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
            *motor_dir = -1;
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            *motor_dir = 1;
        }
}


void
open_close_door(void)
{
	elev_set_door_open_lamp(1);
	time_delay(DELAY_TIME);
	elev_set_door_open_lamp(0);
}


void
set_order_list_and_lights(int array[4][3])
{
	if (elev_get_button_signal(BUTTON_CALL_UP, 0)) {			// UP from 1st floor
		array[0][0] = 1;
		elev_set_button_lamp(BUTTON_CALL_UP, 0, 1);
	}
	else if (elev_get_button_signal(BUTTON_CALL_UP, 1)) {		// UP from 2nd floor
		array[1][0] = 1;
		elev_set_button_lamp(BUTTON_CALL_UP, 1, 1);
	}
	else if (elev_get_button_signal(BUTTON_CALL_UP, 2)) {		// UP from 3rd floor
		array[2][0] = 1;
		elev_set_button_lamp(BUTTON_CALL_UP, 2, 1);
	}
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 1)) {		// DOWN from 2nd floor
		array[1][1] = 1;
		elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 1);
	}
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 2)) {		// DOWN from 3rd floor
		array[2][1] = 1;
		elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 1);
	}
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 3)) {		// DOWN from 4th floor
		array[3][1] = 1;
		elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 1);
	}
	else if (elev_get_button_signal(BUTTON_COMMAND, 0)) {		// Order button 1st floor pressed
		array[0][2] = 1;
		elev_set_button_lamp(BUTTON_COMMAND, 0, 1);
	}
	else if (elev_get_button_signal(BUTTON_COMMAND, 1)) {		// Order button 2nd floor pressed
		array[1][2] = 1;
		elev_set_button_lamp(BUTTON_COMMAND, 1, 1);
	}
	else if (elev_get_button_signal(BUTTON_COMMAND, 2)) {		// Order button 3rd floor pressed
		array[2][2] = 1;
		elev_set_button_lamp(BUTTON_COMMAND, 2, 1);
	}
	else if (elev_get_button_signal(BUTTON_COMMAND, 3)) {		// Order button 4th floor pressed
		array[3][2] = 1;
		elev_set_button_lamp(BUTTON_COMMAND, 3, 1);
	}
	return;
}

// We dont use this yet
int
check_up_down_button_pressed(int array[4][3], int floor) {
	switch(floor) {
		case 0:
			if(array[0][0] == 1)
				return 1;
			break;
		case 1:
			if(array[1][0] == 1)
				return 1;
			else if(array[1][1] == 1)
				return -1;
			break;
		case 2:
			if(array[2][0] == 1)
				return 1;
			else if(array[2][1] == 1)
				return -1;
			break;
		case 3:
			if(array[3][1] == 1)
				return -1;
			break;
	}
	return 0;
}


void
turn_off_button_lights(int floor, int* motor_dir)
{
	if(floor == 0) {
	    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	    elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    else if(floor == 3) {
       	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
       	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    }
    else if((floor == 1 || floor == 2) && (*motor_dir == -1)) {
	    elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	}
	else if((floor == 1 || floor == 2) && (*motor_dir == 1)) {
	    elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
	}
}