#include "elev.h"
#include <time.h>
#include <stdio.h>

#include "ownfuncs.h"

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
        
        set_floor_lights();
}


int
button_outside_pressed(void)
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
order_button_inside_pressed(void)
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


// button_outside_pressed() gives the int outside_button_pressed in main()
void
set_outside_order_lights(int outside_button_pressed, int value)
{
	// Turns light off
	if(value == 0) {
		switch(outside_button_pressed) {
			case 1:
				elev_set_button_lamp(BUTTON_CALL_UP, 0, 0);	// Light off in 1st floor UP button
				break;
			case 2:
				elev_set_button_lamp(BUTTON_CALL_UP, 1, 0);	// Light off in 2nd floor UP button
				break;
			case 3:
				elev_set_button_lamp(BUTTON_CALL_UP, 2, 0);	// Light off in 3rd floor UP button
				break;

			case -1:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 0); // Light off in 2nd floor DOWN button
				break;
			case -2:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 0); // Light off in 3rd floor DOWN button
				break;
			case -3:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 0); // Light off in 4th floor DOWN button
				break;
	}

	// Turns light on
	else {
		switch(outside_button_pressed) {
			case 1:
				elev_set_button_lamp(BUTTON_CALL_UP, 0, 1);	// Light in 1st floor UP button
				break;
			case 2:
				elev_set_button_lamp(BUTTON_CALL_UP, 1, 1);	// Light in 2nd floor UP button
				break;
			case 3:
				elev_set_button_lamp(BUTTON_CALL_UP, 2, 1);	// Light in 3rd floor UP button
				break;

			case -1:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 1); // Light in 2nd floor DOWN button
				break;
			case -2:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 1); // Light in 3rd floor DOWN button
				break;
			case -3:
				elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 1); // Light in 4th floor DOWN button
				break;
		}
	}
}


// order_button_inside_pressed() gives the int floor_order_button in main()
void
set_floor_order_lights(int floor_order_button, int value)
{
	// Turns light off
	if (value == 0) {
		switch(floor_order_button) {
			case 0:
				elev_set_button_lamp(BUTTON_COMMAND, 0, 0);
				break;
			case 1:
				elev_set_button_lamp(BUTTON_COMMAND, 1, 0);
				break;
			case 2:
				elev_set_button_lamp(BUTTON_COMMAND, 2, 0);
				break;
			case 3:
				elev_set_button_lamp(BUTTON_COMMAND, 3, 0);
				break;
		}
	}

	// Turns light on
	else {
		switch(floor_order_button) {
			case 0:
				elev_set_button_lamp(BUTTON_COMMAND, 0, 1);
				break;
			case 1:
				elev_set_button_lamp(BUTTON_COMMAND, 1, 1);
				break;
			case 2:
				elev_set_button_lamp(BUTTON_COMMAND, 2, 1);
				break;
			case 3:
				elev_set_button_lamp(BUTTON_COMMAND, 3, 1);
				break;
		}
	}
}


