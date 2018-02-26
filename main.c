#include "elev.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

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
    int order_list[N_FLOORS][N_BUTTONS] = {{0},{0},{0}};


	// Spec. 4.1 "Oppstart"

    printf("Press STOP button to stop elevator and exit program.\n");
    elev_set_motor_direction(DIRN_UP);

    // WHy does this work?
    int *motor_direction = &(int){1};


    while (1) {
        change_of_motor_direction(motor_direction);

        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1;
    bool order_found = false;


    // MAIN LOOP       Spec. 4.1 -- 4.7

	while (1) {
    	change_of_motor_direction(motor_direction); 
        set_floor_lights();

        // Get last_passed _floor from lights ? Always the same
        if(elev_get_floor_sensor_signal() != -1) {
            last_passed_floor = elev_get_floor_sensor_signal();
        }
        
        // STOP STATE          Spec. 4.6
        if (elev_get_stop_signal()) {
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);

            while(elev_get_stop_signal()) {
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


        // IDLE STATE
        do {
            // Check if buttons are pressed and sets lights
            set_order_list_and_lights(order_list);

            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 3; j++) {
                    if(order_list[i][j] == 1){
                        order_found = true;
                        order_floor = i;
                        break;
                    }
                }
                if(order_found) {
                    break;
                }
            }
        }while(!order_found);


//        for(int i = 0; i < 4; i++) {
//               for(int j = 0; j < 3; j++) {
//                   printf("%d", order_list[i][j]);
//                }
//                printf("\n");
//            }


	   	// ORDER STATE
        // WHILE LOOP
        // NEED stop logic 		
        while(last_passed_floor != order_floor) {
        	//STOP logic
        	set_order_list_and_lights(order_list);
        	set_floor_lights();

	        if(order_floor > last_passed_floor) {
	            elev_set_motor_direction(DIRN_UP);
	            *motor_direction = 1;
	        }
	        else if(order_floor < last_passed_floor) {
	        	elev_set_motor_direction(DIRN_DOWN);
	        	*motor_direction = -1;
	        }

	        int index = -1;
	        if(*motor_direction == 1) {
	        	index = 0;
	        }
	        else if(*motor_direction == -1) {
	        	index = 1;
	        }



	        if(order_list[last_passed_floor][index] == 1 || order_list[last_passed_floor][2] == 1) {
                elev_set_motor_direction(DIRN_STOP);
                open_close_door();      // Cannot update order_list here by now ? Necessary ?
                order_list[last_passed_floor][index] = 0;
                order_list[last_passed_floor][2] = 0;

                elev_set_button_lamp(BUTTON_COMMAND, last_passed_floor, 0);
            }


	    }


/**
From here, check our direction and the corresponding column according to present floor
If BUTTON_COMMAND is high, stop anyways
*/

            // Search through order_list for an up/down order
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 3; j++) {
                    if(order_list[i][j] == 1) {
                        order_floor = i;
                        order_found = true;
                        break;
                    }
                }
                if(order_floor != -1) {
                    break;
                }

            }




/*****
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
*/

    // End of while loop
    }
  
    return 0;
}
