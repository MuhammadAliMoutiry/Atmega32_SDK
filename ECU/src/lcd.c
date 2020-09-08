
/*
 * lcd.c
 *
 * Created: 10/29/2019 5:57:11 AM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "types.h"
#include "lcd.h"



void init_lcd(lcdCfg_t *obj){
	int i;
	for(i=0 ; i<DATA_PINS; i++){
		init_pin(obj->pins[i].port , obj->pins[i].pin , OUTPUT);
	}
	init_pin(obj->EN.port , obj->EN.pin , OUTPUT);
	init_pin(obj->RS.port , obj->RS.pin , OUTPUT);
	
	if(DATA_PINS == 4){
		lcd_cmd(obj,LCD_4BIT_MODE);
		lcd_cmd(obj,LCD_2_LINE_4BIT);
	}else if(DATA_PINS == 8)lcd_cmd(obj,LCD_8BIT_MODE);
	lcd_cmd(obj,CLEAR_DISPLAY_SCREEN);
	lcd_cmd(obj,DISPLAY_ON_CURSOR_BLINKING);
	lcd_cmd(obj,FORCE_CURSOR_TO_BEGINNING_OF_1ST_LINE);
}

void lcd_cmd(lcdCfg_t *obj , uint8 cmd){
	uint8 i,temp;
	write_pin(obj->RS.port , obj->RS.pin , LOW);
	if(DATA_PINS == 8){
		for(i=0 ; i< DATA_PINS ; i++){
			write_pin(obj->pins[i].port , obj->pins[i].pin , (cmd & (1 << i))>> i);
		}
		write_pin(obj->EN.port,obj->RS.pin,LOW);
		write_pin(obj->EN.port , obj->EN.pin , HIGH);
		_delay_ms(2);
		write_pin(obj->EN.port , obj->EN.pin , LOW);
		_delay_ms(20);

	}else if(DATA_PINS == 4){
		temp = cmd >>4;
		for(i=0 ; i< DATA_PINS ; i++){
			write_pin(obj->pins[i].port , obj->pins[i].pin , (temp & (1 << i))>> i);
		}
		write_pin(obj->EN.port,obj->RS.pin,LOW);
		write_pin(obj->EN.port , obj->EN.pin , HIGH);
		_delay_ms(2);
		write_pin(obj->EN.port , obj->EN.pin , LOW);
		_delay_ms(20);

		for(i=0 ; i< DATA_PINS ; i++){
			write_pin(obj->pins[i].port , obj->pins[i].pin , (cmd & (1 << i))>> i);
		}
		write_pin(obj->EN.port,obj->RS.pin,LOW);
		write_pin(obj->EN.port , obj->EN.pin , HIGH);
		_delay_ms(2);
		write_pin(obj->EN.port , obj->EN.pin , LOW);
		_delay_ms(20);
	}
	  
}

void lcd_print_char(lcdCfg_t *obj , uint8 ch){
	uint8 i,temp;
	if(DATA_PINS == 8){
	for(i=0 ; i<DATA_PINS ; i++){
		write_pin(obj->pins[i].port , obj->pins[i].pin , (ch & (1<<i))>>i);
	}
	write_pin(obj->RS.port , obj->RS.pin , HIGH);
	write_pin(obj->EN.port , obj->EN.pin , HIGH);
	_delay_ms(2);
	write_pin(obj->EN.port , obj->EN.pin , LOW);
	_delay_ms(20);
	
	}else if(DATA_PINS == 4){
		temp = ch >>4;
		for(i=0 ; i < DATA_PINS ; i++){
			write_pin(obj->pins[i].port , obj->pins[i].pin , (temp & (1<<i))>>i);
		}
		write_pin(obj->EN.port,obj->RS.pin,HIGH);
		write_pin(obj->EN.port , obj->EN.pin , HIGH);
		_delay_us(2);
		write_pin(obj->EN.port , obj->EN.pin , LOW);
		_delay_us(100);

		for(i=0 ; i<DATA_PINS ; i++){
			write_pin(obj->pins[i].port , obj->pins[i].pin , (ch & (1<<i))>>i);
		}
		write_pin(obj->EN.port,obj->RS.pin,HIGH);
		write_pin(obj->EN.port , obj->EN.pin , HIGH);
		_delay_ms(2);
		write_pin(obj->EN.port , obj->EN.pin , LOW);
		_delay_ms(20);
	}
	
}

void lcd_print_str(lcdCfg_t *obj , char *str){
	uint8 i=0;
	while(str[i] != '\0'){
		lcd_print_char(obj , str[i]);
		i++;
	}
}

void lcd_gotoXY(lcdCfg_t *obj, uint8 y , uint8 x){
	uint8 first_char[]={0x80 , 0xC0 , 0x94 , 0xD4};
		lcd_cmd(obj , (first_char[y-1]+ x-1));
}

void lcd_write_number(lcdCfg_t *obj,uint16 num){
    uint8 num_char[5],i=0,j=0;
	if (num == 0)lcd_print_char(obj,'0');
	else{	
	do 
	{
		num_char[i]=num%10 + '0';
		num = num/10;
		i++;
	} while (num !=0);
	for(j=i;j>0;j--){
		lcd_print_char(obj,num_char[j-1]);
	}
	}
}

void lcd_create_character(lcdCfg_t*obj, uint8 *pucPattern,uint8 cLocation) {

	uint8 iLoop=0;
	lcd_cmd(obj,(0x40 + (cLocation*8))); //Send the Address of CGRAM
	for(iLoop=0; iLoop < 8; iLoop++)
	lcd_print_char(obj,pucPattern[iLoop]); //Pass the bytes of pattern on LCD

}
