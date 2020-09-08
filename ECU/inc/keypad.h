
/*
 * keypad.h
 *
 * Created: 10/29/2019 5:56:21 AM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "gpio.h"
#ifndef  KEYPAD_H_
#define  KEYPAD_H_

#define ROWS_NUM 4
#define COL_NUM  3

typedef struct keypadPin{
	uint8 pin;
	uint8 port;
	}keypadPin_t;

typedef struct keypad{
	keypadPin_t rows[ROWS_NUM];
	keypadPin_t col[COL_NUM];
	}keypad_t;

void init_keypad(keypad_t *obj);
uint8 get_key(keypad_t *obj);
#endif