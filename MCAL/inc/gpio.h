/**
*Interrupt on INT0 has control sense of (falling and rising) edge only.
*/
#include "hw_gpio.h"
#include "types.h"
#ifndef GPIO_H_
#define GPIO_H_

#define INPUT  0
#define OUTPUT 1

#define HIGH 1
#define LOW  0

#define PORT_INPUT  0x00
#define PORT_OUTPUT 0xFF

#define PORT_LOW  0x00
#define PORT_HIGH 0xFF

#define MAX_PINS 7

#define PIN_NUM_0 0
#define PIN_NUM_1 1
#define PIN_NUM_2 2
#define PIN_NUM_3 3
#define PIN_NUM_4 4
#define PIN_NUM_5 5
#define PIN_NUM_6 6
#define PIN_NUM_7 7

typedef enum interrupt_pin{
    EXTERNAL_INTERRPUT_INT0_ON_PIN_PD2 = 0 ,
    EXTERNAL_INTERRPUT_INT1_ON_PIN_PD3 = 1 ,
    EXTERNAL_INTERRPUT_INT2_ON_PIN_PB2 = 2	
}interruptPin_t;

typedef enum interrupt_sense_control{
    LOW_LEVEL_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST           = 0 ,
	ANY_LOGICAL_CHANGE_ON_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST  = 1 ,
	FALLING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST        = 2 ,
	RISING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST         = 3	
}interruptSenseControl_t;

typedef struct gpio_interrupt{
  	 interruptPin_t interruptPinSelect ;
	 interruptSenseControl_t interruptSenseControl ;
	 void(*interruptFunctionPtr)(void);
}gpio_interrupt_t;

uint8 init_pin(uint8 reg, uint8 pin, uint8 dir);
uint8 init_port(uint8 reg, uint16 val);
uint8 write_pin(uint8 reg, uint8 pin, uint8 val);
uint8 write_port(uint8 reg, uint16 val);
uint8 read_pin(uint8 reg, uint8 pin, uint8 * data);
uint8 read_port(uint8 reg, uint8 *val);
uint8 toggle_pin(uint8 reg , uint8 pin);
void init_gpio_interrupt(gpio_interrupt_t *obj);

#endif /* GPIO_H_ */
