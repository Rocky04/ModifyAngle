/*
 * ModifyAngle.cpp
 *
 * Created: 20.05.2021 16:29:40
 * Author : User
 */ 

#include <avr/io.h>
#include "ModifyAngle/modify_angle.h"


int main(void)
{
    int16_t array[17][2];
	int16_t* temp;


	while (1)
	{
		temp = array[1];

		array[1][0] = 10; array[1][1] = 220;
		array[2][0] = 210; array[2][1] = 230;
		array[3][0] = 240; array[3][1] = 215;
		array[4][0] = 255; array[4][1] = 5;
		array[5][0] = 255; array[5][1] = -5;
		array[6][0] = 240; array[6][1] = -215;
		array[7][0] = 210; array[7][1] = -230;
		array[8][0] = 10; array[8][1] = -220;
		array[9][0] = -10; array[9][1] = -220;
		array[10][0] = -210; array[10][1] = -230;
		array[11][0] = -240; array[11][1] = -215;
		array[12][0] = -255; array[12][1] = -5;
		array[12][0] = -255; array[13][1] = 5;
		array[14][0] = -240; array[14][1] = 215;
		array[15][0] = -210; array[15][1] = 230;
		array[16][0] = -10; array[16][1] = 220;


		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
		
		convert_and_shift_directions(temp++, temp++);
	}
}
