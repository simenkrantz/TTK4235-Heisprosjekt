#include "elev.h"
#include <time.h>
#include <stdio.h>

#include "ownfuncs.h"

// Delay time in milliseconds
#define DELAY_TIME 3000

void
initialize(void)
{
    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        change_of_motor_direction();

        if (elev_get_floor_sensor_signal() != -1) {
        	elev_set_motor_direction(DIRN_STOP);
        	return;
        }
    }
}

void
set_floor_lights(void)
{
        int current_floor = elev_get_floor_sensor_signal();
        if (current_floor != -1){
        	elev_set_floor_indicator(current_floor);
        }
}

void
time_delay(int millisecs)
{
	long pause;
	clock_t now, then;
	pause = millisecs*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while ((now-then) < pause) {
		now = clock();
	}
}

void
change_of_motor_direction(int* motor_dir)
{
	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
            &motor_dir = -1;
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
            &motor_dir = 1;
        }
}


void
open_close_door(void)
{
	// Cannot open door between floors
	if(elev_get_floor_sensor_signal != -1) {
		elev_set_door_open_lamp(1);
		time_delay(DELAY_TIME);
		elev_set_door_open_lamp(0);
	}
}


///////// ADD LIGHT LOGIC
void
set_order_list(int array[4][3])
{
	if (elev_get_button_signal(BUTTON_CALL_UP, 0))			// UP from 1st floor
		array[0][0] = 1;
	else if (elev_get_button_signal(BUTTON_CALL_UP, 1))		// UP from 2nd floor
		array[1][0] = 1;
	else if (elev_get_button_signal(BUTTON_CALL_UP, 2))		// UP from 3rd floor
		array[2][0] = 1;
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 1))	// DOWN from 2nd floor
		array[1][1] = 1;
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 2))	// DOWN from 3rd floor
		array[2][1] = 1;
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 3))	// DOWN from 4th floor
		array[3][1] = 1;
	else if (elev_get_button_signal(BUTTON_COMMAND, 0))		// Order button 1st floor pressed
		array[0][2] = 1;
	else if (elev_get_button_signal(BUTTON_COMMAND, 1))		// Order button 2nd floor pressed
		array[1][2] = 1;
	else if (elev_get_button_signal(BUTTON_COMMAND, 2))		// Order button 3rd floor pressed
		array[2][2] = 1;
	else if (elev_get_button_signal(BUTTON_COMMAND, 3))		// Order button 4th floor pressed
		array[3][2] = 1;
	else
		return;
}

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
set_outside_order_lights(int up_or_down, int floor, int on_or_off)
{
	// Turning lights off
	if(on_or_off == 0) {

		// Turn off the DOWN button
		if(up_or_down == 0) {
			elev_set_button_lamp(BUTTON_CALL_DOWN, floor, on_or_off);
		}

		// Turn off the UP button
		else {
			elev_set_button_lamp(BUTTON_CALL_UP, floor, on_or_off);
		}
	}

	// Turning lights on
	else {

		// Turn on the DOWN button
		if(up_or_down == 0) {
			elev_set_button_lamp(BUTTON_CALL_DOWN, floor, on_or_off);
		}

		// Turn on the UP button
		else {
			elev_set_button_lamp(BUTTON_CALL_UP, floor, on_or_off);
		}
	}
}

void
set_floor_order_lights(int floor, int on_or_off)
{
	// Turns light off
	if (on_or_off == 0) {
		elev_set_button_lamp(BUTTON_COMMAND, floor, on_or_off);
	}

	// Turns light on
	else {
		elev_set_button_lamp(BUTTON_COMMAND, floor, on_or_off);
	}
}



