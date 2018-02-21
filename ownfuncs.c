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
change_of_motor_direction(void)
{
	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
}


int
get_button_outside_pressed(void)
{
	if (elev_get_button_signal(BUTTON_CALL_UP, 0))			// UP from 1st floor
		return 1;
	else if (elev_get_button_signal(BUTTON_CALL_UP, 1))		// UP from 2nd floor
		return 2;
	else if (elev_get_button_signal(BUTTON_CALL_UP, 2))		// UP from 3rd floor
		return 3;

	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 1))	// DOWN from 2nd floor
		return -1;
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 2))	// DOWN from 3rd floor
		return -2;
	else if (elev_get_button_signal(BUTTON_CALL_DOWN, 3))	// DOWN from 4th floor
		return -3;
	else
		return 0;	// Default
}


int
get_order_button_inside_pressed(void)
{
	if (elev_get_button_signal(BUTTON_COMMAND, 0))		// Order button 1st floor pressed
		return 0;
	else if (elev_get_button_signal(BUTTON_COMMAND, 1))	// Order button 2nd floor pressed
		return 1;
	else if (elev_get_button_signal(BUTTON_COMMAND, 2))	// Order button 3rd floor pressed
		return 2;
	else if (elev_get_button_signal(BUTTON_COMMAND, 3))	// Order button 4th floor pressed
		return 3;
	else
		return -1;	// Default
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
