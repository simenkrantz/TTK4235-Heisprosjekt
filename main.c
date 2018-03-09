#include "elev.h"
#include <stdio.h>

#include "run_state.h"

int main()
{
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Elevator program started up.\n");
    run_state_function();

    return 0;
}
