/*
 * timer_app.c
 *
 * Created: 7/19/2020 6:23:49 PM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "timer_app.h"
// 
// #define F_CPU 8000000UL
// #include <util/delay.h>
// #include "gpio.h"
// #include "timer.h"
// #include "spi.h"
// #include "lcd.h"
// #include "uart.h"
// #include "uart_services.h"
// #include "utils.h"
// #include "timer_app.h"
// 
/************************************************************************/
/* Calculate function time and display it on lcd                        */
/************************************************************************/
// volatile uint16 count = 0;
// 
// void overflow(void){
// 	count++;
// 	timer0_set_count(0);
// }
// 
// int main(){
// 	
// 	lcdCfg_t lcd1 ={ {{BASE_A,0},{BASE_A,1},{BASE_A,2},{BASE_A,3}},
// 	{BASE_A,4},
// 	{BASE_A,5}};
// 	
// 	tTimerCfg_t timer0 = {PRESCALER_8,NORMAL_PORT_OPERATION_OC0_DISCONNECTED,NORMAL};
// 	uint16 time=0;
// 	init_lcd(&lcd1);
// 	init_timer0(&timer0);
// 	timer0_set_count(0);
// 	timer0_overflow_ISR(overflow);
// 	timer0_interrupt_enable(OVERFLOW_INTERRUPT);
// 	
// 	_delay_us(300);
// 	uint16 c = count;
// 	time = timer0_get_count();
// 	
// 	lcd_gotoXY(&lcd1,1,1);
// 	lcd_write_number(&lcd1,time);
// 	lcd_gotoXY(&lcd1,1,8);
// 	lcd_write_number(&lcd1,c);
// 	lcd_gotoXY(&lcd1,2,1);
// 	time = time + (c*256);
// 	lcd_write_number(&lcd1,time);
// 
// 
// 	while(1){
// 
// 	}
// }

/************************************************************************/
/* Toggle pin every 1 second                                            */
/************************************************************************/
// #define F_CPU 8000000UL
// #include <util/delay.h>
// #include "gpio.h"
// #include "timer.h"
// #include "spi.h"
// #include "lcd.h"
// #include "uart.h"
// #include "uart_services.h"
// #include "utils.h"
// #include "timer_app.h"
// 
// volatile uint16 count = 0;
// 
// void overflow(void){
// 	count++;
// 	if (count == 3906){
// 		toggle_pin(BASE_B,0);
// 		count=0;
// 		timer0_set_count(64);
// 	}
// }
// 
// int main(){
// 	
// 	lcdCfg_t lcd1 ={ {{BASE_A,0},{BASE_A,1},{BASE_A,2},{BASE_A,3}},
// 	{BASE_A,4},
// 	{BASE_A,5}};
// 	
// 	tTimerCfg_t timer0 = {PRESCALER_8,NORMAL_PORT_OPERATION_OC0_DISCONNECTED,NORMAL};
// 	uint16 time=0;
// 	init_lcd(&lcd1);
// 	init_timer0(&timer0);
// 	init_pin(BASE_B,0,HIGH);
// 	timer0_set_count(64);
// 	timer0_overflow_ISR(overflow);
// 	timer0_interrupt_enable(OVERFLOW_INTERRUPT);
// 	
// 
// 
// 	while(1){
// 
// 	}
// }








