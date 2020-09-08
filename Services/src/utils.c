/*
 * utils.c
 *
 * Created: 7/10/2020 9:28:04 PM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "utils.h"

void convert_int_to_string(uint16 int_vale , uint8 *str){
	 uint8 i=0,len=0;
	 uint16 num = int_vale,rem=0;
	 if (int_vale == 0)str[i]='0';
	 else{
		 while (num !=0){
			 len++;
			 num /=10;
		 }
		 for (i=0;i<len;i++){
			 rem = int_vale%10;
			 int_vale = int_vale/10;
			 str[len-(i+1)]= rem + '0';
		 }
		 str[len]='\0';
		 
	 }
}

uint16 convert_string_to_int(uint8 *str){
	uint8 i=0,lens=0;
	uint16 num=0;
	while(str[lens]!='\0'){
		lens++;
	}
	for (i=0;i<lens;i++){
		num = num + (((str[lens-(i+1)]-'0'))*power(10,i));
	}
	return num;
}

uint16 power(uint8 base , uint8 expon){
	uint8 i;
	uint16 num=1;
	for (i=0;i<expon;i++){
		num = num * base;
	}
	return num;
}