
#include "types.h"
#include "hw_gpio.h"
#include "gpio.h"
#include "hw_types.h"
#include <avr/interrupt.h>

static void(*gpio_int0_ptr)(void); /* to catch interrupt function address an pass it to ISR function. */
static void(*gpio_int1_ptr)(void); /* to catch interrupt function address an pass it to ISR function. */
static void(*gpio_int2_ptr)(void); /* to catch interrupt function address an pass it to ISR function. */
//------------------------------------------------------------------------------------------------------
/**
* Func : init_pin
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
       : pin -> pin number (0,1,2,3,4,5,6,or 7)
	   : dir -> INPUT
	         -> OUTPUT
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 init_pin(uint8 reg, uint8 pin, uint8 dir) {
	uint8 state = S_PASS;
		if (OUTPUT == dir) {
			state = HW_WR_BIT(reg + DIR_OFFSET , pin , dir);
		} 
		else if (INPUT == dir) {
			state = HW_WR_BIT(reg + DIR_OFFSET , pin , dir);
		}
	return state;
}
//------------------------------------------------------------------
/**
* Func : init_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
	   : dir -> PORT_INPUT
	         -> PORT_OUTPUT
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 init_port(uint8 reg, uint16 val) {
	uint8 state = S_PASS;
	state = HW_WR_PORT(reg + DIR_OFFSET,val) ;
	return state;
}
//------------------------------------------------------------------
/**
* Func : write_pin
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
       : pin -> pin number (0,1,2,3,4,5,6,or 7)
	   : val -> HIGH
	         -> LOW
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 write_pin(uint8 reg, uint8 pin, uint8 val) {
   uint8 state = S_PASS ;
		if (HIGH == val) {
			state = HW_WR_BIT(reg + DATA_OFFSET , pin , val);
		} 
		else if (LOW == val) {
			state = HW_WR_BIT(reg + DATA_OFFSET ,pin , val);
			}
		
	return state;
}
//------------------------------------------------------------------
/**
* Func : write_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
	   : val -> PORT_HIGH
	         -> PORT_LOW
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 write_port(uint8 reg, uint16 val) {
	uint8 state = S_PASS;
   state = HW_WR_PORT(reg + DATA_OFFSET, val);
	return state;
}
//------------------------------------------------------------------
/**
* Func : read_pin
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
       : pin -> pin number (0,1,2,3,4,5,6,or 7)
	   : *data->pointer to return the value in
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 read_pin(uint8 reg, uint8 pin, uint8 * data) {
	uint8 state = S_PASS;
    state = HW_RD_BIT(reg + INPUT_OFFSET , pin , data);
	return state;
}
//---------------------------------------------------------------- 
/**
* Func : read_port
* Args : reg -> register name(BASE_A,BASE_B,BASE_C,or BASE_D)
       : pin -> pin number (0,1,2,3,4,5,6,or 7)
	   : *val ->pointer to return the value in
*Return : state -> it includes two possiblilities 
          S_PASS  = function success
		  E_FAIL  = function fail
*/
uint8 read_port(uint8 reg, uint8 *val) {
	uint8 state = S_PASS;
	state = HW_RD_PORT(reg + INPUT_OFFSET , val);
	return state;
}

//--------------------------------------------
uint8 toggle_pin(uint8 reg , uint8 pin){
	uint8 state = S_PASS;
	uint8 val=0 ;
	HW_RD_BIT(reg+DATA_OFFSET , pin ,&val);
	if(val == HIGH)HW_WR_BIT(reg+ DATA_OFFSET ,pin,  LOW );
	else if(val == LOW)HW_WR_BIT(reg+ DATA_OFFSET ,pin,  HIGH );
	else state = E_FAIL ;
	return state;
}

/************************************************************************/
/*                      Interrupt Functions                             */
/************************************************************************/
void init_gpio_INT0_interrupt(gpio_interrupt_t *obj){
	
	gpio_int0_ptr = obj->interruptFunctionPtr;
	HW_WR_BIT(GENERAL_INTERRUPT_CONTROL_REG , PIN_NUM_6 , HIGH);
	
	if (obj->interruptSenseControl == LOW_LEVEL_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_0 , LOW);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_1 , LOW);
	}
	else if (obj->interruptSenseControl ==ANY_LOGICAL_CHANGE_ON_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_0 , HIGH);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_1 , LOW);
	}
	else if (obj->interruptSenseControl ==FALLING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_0 , LOW);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_1 , HIGH);
	}
	else if (obj->interruptSenseControl == RISING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_0 , HIGH);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_1 , HIGH);
	}
}
//-----------------------------------------------------------------------
void init_gpio_INT1_interrupt(gpio_interrupt_t *obj){
	
	gpio_int1_ptr = obj->interruptFunctionPtr;
	HW_WR_BIT(GENERAL_INTERRUPT_CONTROL_REG , PIN_NUM_7 , HIGH);
	
	if (obj->interruptSenseControl == LOW_LEVEL_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_2 , LOW);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_3 , LOW);
	}
	else if (obj->interruptSenseControl ==ANY_LOGICAL_CHANGE_ON_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_2 , HIGH);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_3 , LOW);
	}
	else if (obj->interruptSenseControl ==FALLING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_2 , LOW);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_3 , HIGH);
	}
	else if (obj->interruptSenseControl == RISING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_2 , HIGH);
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_REG , PIN_NUM_3 , HIGH);
	}
	
}
//----------------------------------------------------------------------
void init_gpio_INT2_interrupt(gpio_interrupt_t *obj){
	
	gpio_int2_ptr = obj->interruptFunctionPtr;
	HW_WR_BIT(GENERAL_INTERRUPT_CONTROL_REG , PIN_NUM_5 , HIGH);
	
	if (obj->interruptSenseControl ==FALLING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_AND_STATUS_REG , PIN_NUM_6 , LOW);
	
	}
	else if (obj->interruptSenseControl == RISING_EDGE_OF_INTERRUPT_PIN_GENERATES_INTERRUPT_REQUEST)
	{
		HW_WR_BIT(MICRO_CONTROLLER_CONTROL_AND_STATUS_REG , PIN_NUM_6 , HIGH);
	}
	
}
//-----------------------------------------------------------------------
void init_gpio_interrupt(gpio_interrupt_t *obj){
	
	HW_WR_BIT(SET_REGISTER , PIN_NUM_7 , HIGH);
	if (obj->interruptPinSelect == EXTERNAL_INTERRPUT_INT0_ON_PIN_PD2)
	{
		init_gpio_INT0_interrupt(obj);
	}
	else if (obj->interruptPinSelect == EXTERNAL_INTERRPUT_INT1_ON_PIN_PD3)
	{
		init_gpio_INT1_interrupt(obj);
	}
	else if (obj->interruptPinSelect == EXTERNAL_INTERRPUT_INT2_ON_PIN_PB2)
	{
		init_gpio_INT2_interrupt(obj);
	}
}
//------------------------------------------
ISR(INT0_vect){
	
	(*gpio_int0_ptr)();
}
//-------------------------------------
ISR(INT1_vect){
	(*gpio_int1_ptr)();
}
//-----------------------------------
ISR(INT2_vect){
	(*gpio_int2_ptr)();
}


