#include "ownfuncs.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>

void initialize(void)
{
    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    //First loop initializes startup, 4.1 "Oppstart"
    while (1) {
        change_of_motor_direction();

        if(elev_get_floor_sensor_signal() != -1) {
        	elev_set_motor_direction(DIRN_STOP);
        	return;
        }
    }
}

void set_floor_lights(void)
{
        int current_floor = elev_get_floor_sensor_signal();
        if (current_floor != -1){
        	elev_set_floor_indicator(current_floor);
        }
}

void time_delay(int millisecs)
{
	long pause;
	clock_t now, then;
	pause = millisecs*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while((now-then) < pause) {
		now = clock();
	}
}

void change_of_motor_direction(void)
{
	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }
        
        set_floor_lights();
}

int up_button_outside_pressed(void)
{
	if(elev_get_button_signal(BUTTON_CALL_UP, 0))		//Up from 1st floor
		return 0;
	else if(elev_get_button_signal(BUTTON_CALL_UP, 1))	//Up from 2nd floor
		return 1;
	else if(elev_get_button_signal(BUTTON_CALL_UP, 2))	//Up from 3rd floor
		return 2;
	else
		return -1;	//Default
}

int down_button_outside_pressed(void)
{
	if(elev_get_button_signal(BUTTON_CALL_DOWN, 1))			//Down from 2nd floor
		return 1;
	else if(elev_get_button_signal(BUTTON_CALL_DOWN, 2))	//Down from 3rd floor
		return 2;
	else if(elev_get_button_signal(BUTTON_CALL_DOWN, 3))	//Down from 4th floor
		return 3;
	else
		return -1;	//Default
}

int order_button_inside_pressed(void)
{
	if(elev_get_button_signal(BUTTON_COMMAND, 0))		//Order button 1st floor pressed
		return 0;
	else if(elev_get_button_signal(BUTTON_COMMAND, 1))	//Order button 2nd floor pressed
		return 1;
	else if(elev_get_button_signal(BUTTON_COMMAND, 2))	//Order button 3rd floor pressed
		return 2;
	else if(elev_get_button_signal(BUTTON_COMMAND, 3))	//Order button 4th floor pressed
		return 3;
	else
		return -1;	//Default
}

