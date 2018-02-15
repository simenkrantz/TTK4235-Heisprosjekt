#ifndef __INCLUDE_OWNFUNCS_H__
#define __INCLUDE_OWNFUNCS_H__


//Compressed initialize function
void initialize(void);


//Sets the floorlight for the last passed floor
void set_floor_lights(void);


//Delays action for a given number of milliseconds
void time_delay(int millisecs);


//Turn direction at endpoints and set floor indicators
void change_of_motor_direction(void);


/*
Returns -1 if no up order button is pressed.
Returns 0 for 1st floor, 1 for 2nd floor, 2 for 3rd floor.
*/
int up_button_outside_pressed(void);


/*
Returns -1 if no down order button is pressed.
Returns 1 for 2nd floor, 2 for 3rd floor, 3 for 4th floor.
*/
int down_button_outside_pressed(void);



#endif