/*
 * utils.h
 *
 * Created: 7/10/2020 9:26:14 PM
 *  Author: Muhammad Ali Moutiry
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#include "types.h"

void convert_int_to_string(uint16 int_vale , uint8 *str);
uint16 convert_string_to_int(uint8 *str);
uint16 power(uint8 base , uint8 expon);

#endif /* UTILS_H_ */