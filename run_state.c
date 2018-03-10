#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "elev.h"

#include "run_state.h"
#include "order.h"
#include "emergency_stop.h"
#include "controller.h"

#define N_BUTTONS 3

int
initialize_state_machine(void)
{
	if(!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 0;
    }

    printf("Elevator program started up.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            return 1;
        }
    }
}


void
state_machine(void)
{
	if(!initialize_state_machine())
		return;

    enum State {IDLE = 0, ORDER = 1, EMERGENCY_STOP = 2};
    enum State current_state = IDLE;

    int order_matrix[N_FLOORS][N_BUTTONS] = {{0},{0},{0}};
    int *motor_direction = &(int){1};
    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1, current_floor = -1, button_index = 0;

	while (1) {
		set_floor_indicator_lights();

        current_floor = elev_get_floor_sensor_signal();
        if(current_floor != -1) {
            last_passed_floor = current_floor;
        }
        
        switch(current_state) {
        	case IDLE:

            	if(elev_get_stop_signal()) {
	            	current_state = EMERGENCY_STOP;
	            	order_floor = -1;
	            	break;
	            }
	       		
	       		set_order_matrix_and_corresponding_lights(order_matrix);
	       		order_floor = search_after_order_in_matrix(order_matrix);

	            if(order_floor != -1) {
		    		current_state = ORDER;
		    		break;
		    	}
	        	break;

        	case ORDER:

        		if(elev_get_stop_signal()) {
        			current_state = EMERGENCY_STOP;
		        	order_floor = -1;
		        	break;
		        }

        		set_order_matrix_and_corresponding_lights(order_matrix);
		        set_floor_indicator_lights();
			    set_motor_direction(order_floor, last_passed_floor, motor_direction);
			        
			    current_floor = elev_get_floor_sensor_signal();
			    if(current_floor != -1) {
			        last_passed_floor = current_floor;	            
			    }
	        
			    button_index = get_button_index(motor_direction, order_matrix, last_passed_floor);

			    if((order_matrix[last_passed_floor][button_index] == 1 || order_floor == last_passed_floor) 
				   	&& elev_get_floor_sensor_signal() != -1) {

			       	stop_handling_at_order_floor(order_matrix, last_passed_floor);
		        	order_floor = -1;
		        	current_state = IDLE;
		        	break;
				}
			    break;

		    case EMERGENCY_STOP:

		    	stop_state(order_matrix, motor_direction);
		    	order_floor = order_handling_after_emergency_stop(motor_direction, order_matrix, last_passed_floor);
		    			    	
		    	if(order_floor != -1) {
		    		current_state = ORDER;
		    		break;
		    	}
		    	break;
        }
    }
}
