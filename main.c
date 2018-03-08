#include "elev.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


#include "order.h"
#include "emergency_stop.h"
#include "controller.h"


// Number of buttons for each floor
#define N_BUTTONS 3

int main()
{
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    int order_list[N_FLOORS][N_BUTTONS] = {{0},{0},{0}};

    printf("Elevator program started up.\n");
    elev_set_motor_direction(DIRN_UP);

    while (1) {
        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    int *motor_direction = &(int){1};
    int last_passed_floor = elev_get_floor_sensor_signal();
    int order_floor = -1, current_floor = -1;
    bool order_found = false, emergency_variable = false;


	while (1) {
		set_floor_indicator_lights();
        current_floor = elev_get_floor_sensor_signal();
        if(current_floor != -1) {
            last_passed_floor = current_floor;
        }
        
        emergency_variable = stop_state(order_list, order_floor, last_passed_floor, motor_direction);


        while(!order_found) {
            set_order_list_and_corresponding_lights(order_list);

            if(elev_get_stop_signal()) {
            	emergency_variable = stop_state(order_list, order_floor, last_passed_floor, motor_direction);
            	order_found = false;
            	order_floor = -1;
            }
       		
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
        }


        while(order_floor != -1) {
        	if(elev_get_stop_signal()) {
        		emergency_variable = stop_state(order_list, order_floor, last_passed_floor, motor_direction);
        		order_found = false;
        		order_floor = -1;
        		break;
        	}
        	
        	set_order_list_and_corresponding_lights(order_list);
        	set_floor_indicator_lights();
	        set_motor_direction(order_floor, last_passed_floor, motor_direction);
	        

	        current_floor = elev_get_floor_sensor_signal();
	        if(current_floor != -1) {
	            last_passed_floor = current_floor;	            
	        }
	        
	        int index = get_matrix_index(motor_direction, order_list, last_passed_floor);

	        if((order_list[last_passed_floor][index] == 1 || order_floor == last_passed_floor) 
		       	&& elev_get_floor_sensor_signal() != -1) {

	        	stop_handling_at_order_floor(motor_direction, order_list, index, last_passed_floor);
        		order_floor = -1;
        		order_found = false;
			}

/**
            // After emergency stop
            if(emergency_variable){
            	if((order_floor == last_passed_floor && elev_get_floor_sensor_signal() == -1)){
	            	if(*motor_direction == 1){
	            		elev_set_motor_direction(DIRN_DOWN);
	            		*motor_direction = -1;
	            		printf("%d\n", *motor_direction);
	            		printf("Inni stopp\n");
	            	}
	            	else if(*motor_direction == -1){
	            		elev_set_motor_direction(DIRN_UP);
	            		*motor_direction  = 1;
	            		printf("%d\n", *motor_direction);
	            		printf("Inni stopp\n");
	            	}
	            	else
	            		elev_set_motor_direction(*motor_direction);
	            	emergency_variable = false;
	            }
            }
*/
	    }
    }
  
    return 0;
}
