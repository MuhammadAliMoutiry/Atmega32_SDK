/*
 * hw_types.h
 *
 * Created: 9/7/2016 1:24:35 PM
 *  Author: Muhammad Ali
 */ 

#include "types.h"
#ifndef HW_TYPES_H_
#define HW_TYPES_H_

#define HW_READ_BIT(REG,BIT_NUM) ((*(volatile uint8*)REG &(1<<BIT_NUM))>>BIT_NUM)
#define HW_READ_REG(REG) (*(volatile uint8*)REG)
static inline uint8 HW_WR_BIT(uint16 reg ,uint8 pin , uint8 val){
	uint8 state = S_PASS ;
	if (pin>MAX_PINS)
	{
		state = E_FAIL ;
	}
	else{
	if (val == HIGH)
	{
		*(volatile uint8*)reg |=(1<<pin);
	}
	else if (val == LOW)
	{
		*(volatile uint8*)reg &=~(1<<pin);
	}
	}
	 return state ;
}
//----------------------------------------------------------
static inline uint8 HW_RD_BIT(uint16 reg , uint8 pin , uint8 *data){
	uint8 state = S_PASS ;
	if (pin>MAX_PINS)
	{
		state = E_FAIL ;
	}
	else
	{
		*data = (*(volatile uint8*)reg &(1<<pin))>>pin;
	}
	 
	return state;
}
//----------------------------------------------------------
static inline uint8 HW_WR_PORT(uint16 reg ,uint8 val){
	uint8 state = S_PASS;
	if (val > 255) {
		state = E_FAIL;
	}
	else 
	{
		*(volatile uint8*)reg = val ;
	}
	
	return state ;
}
//------------------------------------------------------------
static inline uint8 HW_RD_PORT(uint16 reg ,uint8 *val){
	uint8 state = S_PASS ;
	*val = *(volatile uint8*)reg ;
	return state ;
}
/*******************************************************************************/
#define SET_REG(Reg) Reg=0xFF
#define CLEAR_REG(Reg) Reg=0x00
#define TOOGLE_REG(Reg) Reg^=0xFF
#define SET_BITS_REG(Reg,Mask) Reg|=(Mask)
#define CLEAR_BITS_REG(Reg,Mask) Reg=(Reg&(~Mask))
#define SET_BIT(Reg,bit) Reg|=(1<<bit)
#define CLEAR_BIT(Reg,bit) Reg=(Reg&(~(1<<bit)))
#define TOOGLE_BIT(Reg,bit) Reg^=(1<<bit)
#define CHECK_BIT(Reg,bit) ((Reg>>bit)&1)

#endif /* HW_TYPES_H_ */