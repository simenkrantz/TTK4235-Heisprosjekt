#include <time.h>
#include <stdbool.h>

#include "run_state.h"
#include "order.h"
#include "emergency_stop.h"
#include "controller.h"

#define N_BUTTONS 3

void
run_state_function(void)
{
	elev_set_motor_direction(DIRN_UP);
    while (1) {
        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    enum State {IDLE = 0, ORDER = 1, EMERGENCY_STOP = 2};
    enum State current_state = IDLE;

    int order_matrix[N_FLOORS][N_BUTTONS] = {{0},{0},{0}};
    int *motor_direction = &(int){1};
    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1, current_floor = -1;
    bool order_found = false;

	while (1) {
		set_floor_indicator_lights();
        current_floor = elev_get_floor_sensor_signal();
        if(current_floor != -1) {
            last_passed_floor = current_floor;
        }
        
        switch(current_state) {
        	case IDLE:
        		printf("IDLE is 0: %d\n", current_state);
        		while(!order_found) {
            		set_order_matrix_and_corresponding_lights(order_matrix);

	            	if(elev_get_stop_signal()) {
	            		current_state = EMERGENCY_STOP;
	            		order_found = false;
	            		order_floor = -1;
	            		break;
	            	}
	       		
	            	for(int i = 0; i < 4; i++) {
	                	for(int j = 0; j < 3; j++) {
	                    	if(order_matrix[i][j] == 1){
	                        	order_found = true;
	                        	order_floor = i;
	                        	current_state = ORDER;
	                        	break;
	                    	}
	                	}
	                	if(order_found)
	                    	break;
	            	}
	        	}
        	case ORDER:
        		printf("ORDER is 1: %d\n", current_state);
        		while(order_floor != -1) {
        			if(elev_get_stop_signal()) {
        				current_state = EMERGENCY_STOP;
		        		order_found = false;
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
	        
			        int index = get_matrix_index(motor_direction, order_matrix, last_passed_floor);

			        if((order_matrix[last_passed_floor][index] == 1 || order_floor == last_passed_floor) 
				       	&& elev_get_floor_sensor_signal() != -1) {

			        	stop_handling_at_order_floor(motor_direction, order_matrix, last_passed_floor);
		        		order_floor = -1;
		        		order_found = false;
		        		current_state = IDLE;
		        		break;
					}
			    }
		    case EMERGENCY_STOP:
		    	printf("STOP is 2: %d\n", current_state);
		    	stop_state(order_matrix, order_floor, last_passed_floor, motor_direction);
		    	current_state = IDLE;
		    	break;
        }
    }
}
