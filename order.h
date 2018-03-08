#ifndef __INCLUDE_ORDER_H__
#define __INCLUDE_ORDER_H__

int
get_matrix_index(int* motor_dir, int array[4][3], int last_floor);


void
set_order_list_and_corresponding_lights(int array[4][3]);


void
stop_handling_at_order_floor(int* motor_dir, int array[4][3], int index, int last_floor);


#endif