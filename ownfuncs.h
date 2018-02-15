#ifndef __INCLUDE_OWNFUNCS_H__
#define __INCLUDE_OWNFUNCS_H__

//Compressed initialize function
void initialize(void);


/*
Sets the floorlight for the last passed floor
*/
void set_floor_lights(void);

//Delays action for a given number of milliseconds
void time_delay(int millisecs);

//Turn direction at endpoints and interrupts when STOP button pressed
void change_of_motor_direction(void);





#endif