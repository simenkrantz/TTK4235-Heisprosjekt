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
    */
    int order_list[N_FLOORS][N_BUTTONS] = {{0},{0},{0}};


	// Spec. 4.1 "Oppstart"
    printf("Press STOP button to stop elevator and exit program.\n");
    elev_set_motor_direction(DIRN_UP);

    // @var motor_direction is -1 if DIRN_DOWN, 1 if DIRN_UP.
    // Remembers the last direction the elevator had. Not included DIRN_STOP.
    int *motor_direction = &(int){1};


    while (1) {
        change_of_motor_direction(motor_direction);

        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1;	// order_floor will after this always be 0-3
    						// Change order_floor to prioritized_floor_order?
    bool order_found = false;


    // MAIN LOOP       Spec. 4.2 -- 4.7

	while (1) {

		// Remove this?
    	change_of_motor_direction(motor_direction); 
        

        set_floor_lights();

        // Will this work ?
        if(elev_get_floor_sensor_signal() != -1) {
        	if(*motor_direction == -1) {
        		last_passed_floor -= 1;
        	}
        	else if(*motor_direction == 1) {
        		last_passed_floor += 1;
        	}
        	// THIS IS TROUBLE SOMETIMES ! WHY ?
            // last_passed_floor = elev_get_floor_sensor_signal();
        }
        

        // EMERGENCY-STOP STATE          Spec. 4.6
        	/**
			State description commentary
        	*/
        // Need to LOOK AT LOGIC and put in a function
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
            
            // Punkt 24 !! Implementer
            // Punkt 25 !! Implementer

            for(int i = 0; i < 4; i++) {
               for(int j = 0; j < 3; j++) {
                   printf("%d", order_list[i][j]);
                }
                printf("\n");
            }
            break;
        }


        // IDLE STATE
            /**
			State description commentary
        	*/
        do {
            set_order_list_and_lights(order_list);

            // PUT STOP LOGIC IN HERE AS WELL

            // THIS LOGIC DOESNT WORK
            if(elev_get_floor_sensor_signal() != -1 && order_found == false) {
            	elev_set_motor_direction(DIRN_STOP);
            }


            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 3; j++) {
                    if(order_list[i][j] == 1){
                        order_found = true;
                        order_floor = i;

                        printf("Order floor is %d\n", order_floor);

                        break;
                    }
                }
                if(order_found) {
                    break;
                }
            }
        }while(!order_found);

/**
        for(int i = 0; i < 4; i++) {
               for(int j = 0; j < 3; j++) {
                   printf("%d", order_list[i][j]);
                }
                printf("\n");
            }


        printf("%d", last_passed_floor);
*/

	   	// HANDLING-ORDER STATE
	   	    /**
			State description commentary
        	*/

        // Logic to stop in 1st and 4th
        // When ordering from 1st/4th, it goes in an infinte loop!
        // Ordering to 1st/4th is OK 

        while(last_passed_floor != order_floor) {
        	
        	// PUT STOP LOGIC HERE

        	set_order_list_and_lights(order_list);

	        if(order_floor > last_passed_floor) {
	            elev_set_motor_direction(DIRN_UP);
	            *motor_direction = 1;
	        }
	        else if(order_floor < last_passed_floor) {
	        	elev_set_motor_direction(DIRN_DOWN);
	        	*motor_direction = -1;
	        }

	        // If last_passed_floor is -1, line ~200 (check if current floor has order request) 
	        // will try to access an index not available
	        if(elev_get_floor_sensor_signal() != -1) {
				if(*motor_direction == -1) {
        			last_passed_floor -= 1;
        		}
        		else if(*motor_direction == 1) {
        			last_passed_floor += 1;
        		}
	            printf("%d, %s", last_passed_floor, "Inside order state - last passed floor\n");
	        }

	        set_floor_lights();
	        
 			int index = -1;
	        if(*motor_direction == 1)
	        	index = 0;
	        else if(*motor_direction == -1)
	        	index = 1;

	        if(order_list[last_passed_floor][index] == 1
	        	|| order_list[last_passed_floor][2] == 1) {
                elev_set_motor_direction(DIRN_STOP);

                // TURN OFF ONLY LIGHTS CORRESPONDING TO DELETED ORDER_LIST ELEMENT
                turn_off_button_lights(last_passed_floor, motor_direction);
                open_close_door();
                order_list[last_passed_floor][index] = 0;
                order_list[last_passed_floor][2] = 0;
                order_found = false;

                // PRINT
                for(int i = 0; i < 4; i++) {
	               for(int j = 0; j < 3; j++) {
	                   printf("%d", order_list[i][j]);
	                }
	                printf("\n");
	            }
            }
	    }

    // End of while loop
    }
  
    return 0;
}
