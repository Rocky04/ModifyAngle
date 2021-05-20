/*
 * ModifyAngle.h
 *
 * Created: 20.05.2021 16:37:28
 *  Author: User
 */ 


#ifndef MODIFYANGLE_H_
#define MODIFYANGLE_H_

#pragma once


#include <avr/io.h>

void convert_and_shift_directions(int16_t* x, int16_t* y);
void convert(int16_t* x, int16_t* y);


#endif /* MODIFYANGLE_H_ */
