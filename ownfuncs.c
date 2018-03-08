#include "elev.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#include "ownfuncs.h"


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
		set_order_list_and_corresponding_lights(array);
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


int
get_matrix_index(int* motor_dir, int array[4][3], int last_floor)
{
	int value = -1;
	if(last_floor == 0)
		value = 0;
	else if(last_floor == 3)
		value = 1;
	else if(*motor_dir == 1){
	    for(int i = last_floor + 1; i < 4; i++) {
	    	for(int j = 0; j < 3; j++) {
	    		if(array[i][j] == 1)
	    			value = j;
	   		}
	   	}
	}
	else if(*motor_dir == -1){
		for(int i = last_floor - 1; i >= 0; i--) {
	    	for(int j = 0; j < 3; j++) {
	    		if(array[i][j] == 1)
	    			value = j;
       		}
       	}
    }
	return value;
}


void
set_order_list_and_corresponding_lights(int array[4][3])
{
	for(int i = 0; i < 4; i++) {
		if(i == 0) {
			if(elev_get_button_signal(BUTTON_CALL_UP, i)) {
				array[i][0] = 1;
				elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
			}
			else if(elev_get_button_signal(BUTTON_COMMAND, i)) {
				array[i][2] = 1;
				elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			}
		}
		else if(i == 3) {
			if(elev_get_button_signal(BUTTON_CALL_DOWN, i)){
				array[i][1] = 1;
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
			}
			else if(elev_get_button_signal(BUTTON_COMMAND, i)){
				array[i][2] = 1;
				elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			}
		}
		else {
			if(elev_get_button_signal(BUTTON_CALL_UP, i)) {
				array[i][0] = 1;
				elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
			}
			else if(elev_get_button_signal(BUTTON_CALL_DOWN, i)) {
				array[i][1] = 1;
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
			}
			else if(elev_get_button_signal(BUTTON_COMMAND, i)) {
				array[i][2] = 1;
				elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			}
		}
	}
}


void
stop_handling_at_order_floor(int* motor_dir, int array[4][3], int index, int last_floor)
{
    elev_set_motor_direction(DIRN_STOP);               
    open_close_door(array);
    for(int i = 0; i < 3; i++){
       	array[last_floor][i] = 0;
    }
    turn_off_button_lights(last_floor);
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