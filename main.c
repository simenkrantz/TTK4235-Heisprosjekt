#include "elev.h"
#include <stdio.h>
#include <time.h>

// Own header files
#include "ownfuncs.h"


int main()
{
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

	// Logic to take care of spec. 4.1 "Oppstart", sets DIRN_STOP
    initialize();

    // This loop sets DIRN_UP when an outside order button is pressed
    while(1) {
        if (button_outside_pressed() != 0) {
            elev_set_motor_direction(DIRN_UP);
            break;
        }
    }


	/**
    MAIN LOOP
    Handles order buttons, spec. 4.2 -- 4.7
    */
    while (1) {

    	change_of_motor_direction();

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }

        



    }
    return 0;
}
