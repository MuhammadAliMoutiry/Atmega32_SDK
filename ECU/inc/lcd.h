
/*
 * lcd.h
 *
 * Created: 10/29/2019 5:56:37 AM
 *  Author: Muhammad Ali Moutiry
 */ 
#ifndef LCD_H_
#define LCD_H_
#include <util/delay.h>
#include "types.h"
#include "gpio.h"

//#define F_CPU 8000000L

#ifndef DATA_PINS
#define DATA_PINS 4
#endif


#define CLEAR_DISPLAY_SCREEN                  0x01
#define RETURN_HOME                           0x28
#define DECREMENT_CURSOR                      0x04
#define INCREMENT_CURSOR                      0x06
#define SHIFT_DISPLAY_RIGHT                   0x05
#define SHIFT_DISPLAY_LEFT                    0x07
#define DISPLAY_OFF_CURSOR_OFF                0x08
#define DISPLAY_OFF_CURSOR_ON                 0x0A
#define DISPLAY_ON_CURSOR_OFF                 0x0C
#define DISPLAY_ON_CURSOR_BLINKING            0x0E
#define SHIFT_CURSOR_POS_TO_LEFT              0x10
#define SHIFT_CURSOR_POS_TO_RIGHT             0x14
#define SHIFT_THE_ENTIRE_DISPLAY_TO_LEFT      0x18
#define SHIFT_THE_ENTIRE_DISPLAY_TO_RIGHT     0x1C
#define FORCE_CURSOR_TO_BEGINNING_OF_1ST_LINE 0x80
#define LCD_4BIT_MODE                         0x02
#define LCD_8BIT_MODE                         0x38
#define LCD_2_LINE_4BIT                       0x28


typedef struct lcdPins{
	uint8 port;
	uint8 pin;
	}lcdPins_t;
typedef struct lcdcfg{
	lcdPins_t pins[DATA_PINS];
	lcdPins_t EN;
	lcdPins_t RS;
		}lcdCfg_t;

void init_lcd(lcdCfg_t *obj);

void lcd_cmd(lcdCfg_t *obj , uint8 cmd);
void lcd_print_char(lcdCfg_t *obj , uint8 ch);
void lcd_print_str(lcdCfg_t *obj , char *str);
void lcd_write_number(lcdCfg_t *obj,uint16 num);
void lcd_gotoXY(lcdCfg_t *obj, uint8 y , uint8 x);
void lcd_create_character(lcdCfg_t*obj, uint8 *pucPattern,uint8 cLocation);
#endif