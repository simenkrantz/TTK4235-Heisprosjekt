#include "elev.h"
#include <stdio.h>

#include "run_state.h"
#include "controller.h"

int main()
{
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Elevator program started up.\n");
    printf("Switch down obstruction lever to stop program\n");
    run_state_function();
    
    elev_set_motor_direction(DIRN_STOP);
    for(int i = 0; i < 4; i++) {
    	turn_off_button_lights(i);
    }
    printf("Bye bye\n");

    return 0;
}
