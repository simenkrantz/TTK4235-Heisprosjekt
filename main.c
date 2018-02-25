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

	@var motor_direction is last direction, is -1 if DIRN_DOWN, 1 if DIRN_UP
    */
    int order_list[N_FLOORS][N_BUTTONS] = {0};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d", order_list[i][j]);
        }
        printf("\n");
    }
/**   
	// Spec. 4.1 "Oppstart"
    int* motor_direction;

    printf("Press STOP button to stop elevator and exit program.\n");
    elev_set_motor_direction(DIRN_UP);

    while (1) {
        change_of_motor_direction(motor_direction);

        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

//    int* elevator_caller = -1;


    

    // MAIN LOOP       Spec. 4.1 -- 4.7

    
	while (1) {
    	change_of_motor_direction(motor_direction); 
        set_floor_lights();

        // Check if buttons are pressed
        set_order_list(order_list);

*/

        /**
		Update function runs all the time

		Checks if a button is pressed through elev_get_button_signal()
		and sets button lamps. Needs to update the matrix with set_order_list()
        */

/**        
        //STOP STATE          Spec. 4.6
        if (elev_get_stop_signal()) {
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);

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
            	for(int floor = 0; floor < 4; floor++) {
            		if(check_up_down_button_pressed(order_list, floor) != 0)
            			break;
            	}
            }   
	   	}


	   	// ORDER STATE

	   	// Sends elevevator to first up/down request ?
	   	if (elev_get_floor_sensor_signal() != -1) {
	   		for(int i = 0; i < 4; i++) {
		   		if(check_up_down_button_pressed(order_list, i) != 0) {
	            	&elevator_caller = i;
	            	if (&elevator_caller < elev_get_floor_sensor_signal()) {
		            	elev_set_motor_direction(DIRN_DOWN);
		            	&motor_direction = -1;
		        	}
		        	else if (&elevator_caller > elev_get_floor_sensor_signal()) {
		            	elev_set_motor_direction(DIRN_UP);
		            	&motor_direction = 1;
		        	}
		        	break;
	        	}
	        	&elevator_caller = -1;
        	}
		}

        if(elev_get_floor_sensor_signal() == &elevator_caller) {
        	open_close_door();

        	// From here we take BUTTON_COMMAND orders 1st -- 4th floor
        	//



        }


    // End of while loop
    }
*/
    return 0;
}
