#include "elev.h"
#include <stdio.h>
#include <time.h>

#include "ownfuncs.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    initialize();

    //Main loop, handles order buttons
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
