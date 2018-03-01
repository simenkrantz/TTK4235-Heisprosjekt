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
    int *motor_direction = &(int){1};

    while (1) {
        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1, current_floor = -1;
    bool order_found = false;


    // MAIN LOOP       Spec. 4.1 -- 4.7

	while (1) {
		set_floor_lights();
        current_floor = elev_get_floor_sensor_signal();
        if(current_floor != -1) {
            last_passed_floor = current_floor;
        }
        

        // STOP STATE          Spec. 4.6
        	/**

        	*/
        stop_state(order_list, order_floor, last_passed_floor, motor_direction);


        // IDLE STATE
        	/**

        	*/
        do {
            // Check if buttons are pressed and sets lights
            set_order_list_and_lights(order_list);


            stop_state(order_list, order_floor, last_passed_floor, motor_direction);


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



	   	// ORDER STATE
	   	/**

	   	*/
        while(last_passed_floor != order_floor) {

        	if(elev_get_stop_signal()) {
        		stop_state(order_list, order_floor, last_passed_floor, motor_direction);
        		order_found = false;
        		break;
        	}
        	
        	set_order_list_and_lights(order_list);
        	set_floor_lights();


        	// DECIDE DIRECTION FUNCTION
	        if(order_floor > last_passed_floor) {
	            elev_set_motor_direction(DIRN_UP);
	            *motor_direction = 1;
	        }
	        else if(order_floor < last_passed_floor) {
	        	elev_set_motor_direction(DIRN_DOWN);
	        	*motor_direction = -1;
	        }
	        //*************************


	        int index = -1;
	        if(*motor_direction == 1) {
	        	index = 0;
	        }
	        else if(*motor_direction == -1) {
	        	index = 1;
	        }

	        current_floor = elev_get_floor_sensor_signal();
	        if(current_floor != -1) {
	            last_passed_floor = current_floor;

	            //Specifically checking UP button 1st floor, DOWN button 4th floor
	            if(last_passed_floor == 0) {
	            	index = 0;
	            }
	            else if(last_passed_floor == 3) {
	            	index = 1;
	            }


	            printf("%d, %s", last_passed_floor, "Inside order state\n");
	        }
	        
	        if(((order_list[last_passed_floor][index] == 1) || (order_list[last_passed_floor][2] == 1))
	        	&& (elev_get_floor_sensor_signal() != -1)) {
                elev_set_motor_direction(DIRN_STOP);


                // DELETE ONLY LIGHTS CORRESPONDING TO DELETED ORDER_LIST ELEMENT
                turn_off_button_lights(last_passed_floor, motor_direction);

                open_close_door();      // Cannot update order_list here by now ? Necessary ?
                
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
