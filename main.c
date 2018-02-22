#include "elev.h"
#include <stdio.h>
#include <time.h>

// Own header files
#include "ownfuncs.h"


// Number of buttons for each floor
#define N_BUTTONS 3

int main()
{

    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    /**
    @var order_list: Elements in the array are set to 1 if the associated button is pressed
	[ [UP from 1st, 	0		 , to 1st],
	[  UP from 2nd, DOWN from 2nd, to 2nd],
	[  UP from 3rd, DOWN from 3rd, to 3rd],
	[  		0	  , DOWN from 4th, to 4th]]

	@var motor_direction is a pointer, is -1 if DIRN_DOWN, 0 if DIRN_STOP, 1 if DIRN_UP
    */
    int order_list[N_FLOORS][N_BUTTONS] = {0};

   
	// Spec. 4.1 "Oppstart"
    initialize();
    int* motor_direction = 0;      

    
	/**
    MAIN LOOP       Spec. 4.1 -- 4.7
    */
	while (1) {
    	change_of_motor_direction(motor_direction); 
        set_floor_lights();

        // Check if buttons are pressed
        set_order_list(order_list);

        
        //STOP STATE          Spec. 4.6
        if (elev_get_stop_signal()) {
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);
            &motor_direction = 0;

            while(get_stop_button()) {
                continue;
            }
            elev_set_stop_lamp(0);

            // Erase orders
            for(int i = 0; i < 4; i++) {
            	for(int j = 0; j < 3; j++) {
            		order_list[i][j] = 0;
            	}
            }
            
            // Checks if array has order
            while(1) {
                if(check_up_down_button_pressed(order_list) != -1)
                    break;
            }   
	   	}


	   	// ORDER STATE

	   	
	   	if ((elev_get_floor_sensor_signal() != -1) && (check_up_down_button_pressed(order_list) != -1)) {
            if (check_up_down_button_pressed(order_list) < last_detected_floor) {
	            elev_set_motor_direction(DIRN_DOWN);
	            &motor_direction = -1;
	        }

	        else if (check_up_down_button_pressed(order_list) > last_detected_floor) {
	            elev_set_motor_direction(DIRN_UP);
	            &motor_direction = 1;
	        }
	        
        }




    // End of while loop
    }

    return 0;
}
