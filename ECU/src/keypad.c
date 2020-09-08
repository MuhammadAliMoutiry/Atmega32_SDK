
/*
 * keypad.c
 *
 * Created: 10/29/2019 5:56:53 AM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "keypad.h"
static uint8 key_num[ROWS_NUM][COL_NUM]= {
	                                      {'1' , '2' , '3' },
										  {'4' , '5' , '6' },
										  {'7' , '8' , '9' },
										  {'*' , '0' , '#' }
};

void init_keypad(keypad_t *obj){
	int i;
	for (i=0 ; i<ROWS_NUM ; i++){
		init_pin(obj->rows[i].port , obj->rows[i].pin, OUTPUT);
		write_pin(obj->rows[i].port , obj->rows[i].pin,HIGH);
	}
	for (i=0 ; i<COL_NUM ; i++){
		init_pin(obj->col[i].port , obj->col[i].pin, INPUT);
		write_pin((obj->col[i].port) , (obj->col[i].pin) , HIGH);// for pull up res
	}
	
}

uint8 get_key(keypad_t *obj){
	uint8 i,j,num=0,data=255;
	for (i=0 ; i<ROWS_NUM ; i++){
		write_pin(obj->rows[i].port,obj->rows[i].pin,LOW);
		for (j=0; j<COL_NUM ; j++){
			read_pin(obj->col[j].port,obj->col[j].pin,&data);
		if(data == LOW){
			num = key_num[i][j];
			}
		}
		write_pin(obj->rows[i].port,obj->rows[i].pin,HIGH);
		if(data == LOW){ break;}
	}
	return num;
}
