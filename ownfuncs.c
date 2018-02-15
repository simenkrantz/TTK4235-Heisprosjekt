#include "ownfuncs.h"
#include "elev.h"
#include <time.h>
#include <stdio.h>

void initialize(void) {
	
    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);


    //First loop initializes startup, 4.1 "Oppstart"
    while (1) {
        change_of_motor_direction();

        if(elev_get_floor_sensor_signal() != -1) {
        	elev_set_motor_direction(DIRN_STOP);
        	break;
        }
    }
}

void set_floor_lights(void) {
        int current_floor = elev_get_floor_sensor_signal();
        if (current_floor != -1){
        	elev_set_floor_indicator(current_floor);
        }
}

void time_delay(int millisecs) {
	long pause;
	clock_t now, then;

	pause = millisecs*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while((now-then) < pause) {
		now = clock();
	}
}


void change_of_motor_direction(void) {
	// Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            return;
        }
        
        set_floor_lights();
}

