#include "elev.h"
#include <stdio.h>
#include <time.h>

// Own header files
#include "ownfuncs.h"

#define ARRAY_LENGTH 100

int main()
{
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    /**
    @var up_down_order_list is an array containing up/down orders with length ARRAY_LENGTH
    @var up_down_button_pressed is given by get_button_outside_pressed()
    */
    int up_down_order_list[ARRAY_LENGTH];    
    int up_down_button_pressed;


	// Spec. 4.1 "Oppstart"
    initialize();
    while(1) {
        up_down_button_pressed = get_button_outside_pressed();
        if (button_pressed != 0) {
            up_down_order_list[0] = up_down_button_pressed;
            elev_set_motor_direction(DIRN_UP);
            break;
        }
    }


    // Now we have the first order in the array

	/**
    MAIN LOOP       Spec. 4.1 -- 4.7
    */
    while (1) {
    	change_of_motor_direction(); 
        set_floor_lights();

        
        //STOP STATE          Spec. 4.6
        if (elev_get_stop_signal()) {
            elev_set_stop_lamp(1);
            elev_set_motor_direction(DIRN_STOP);

            while(get_stop_button()) {
                continue;
            }
            elev_set_stop_lamp(0);


            /**

            Erase orders
            
            while(1) {
                if(get_button_outside_pressed() != 0)
                    break;
            }
            
            printf(order_button); Check what comes out

            */
        }


        // ORDER STATE

        // Manipulate up_down_order_list

        up_down_button_pressed = get_button_outside_pressed();

    }
    return 0;
}
