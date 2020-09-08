/*
 * hw_gpio.h
 *
 *  Created on: ???/???/????
 *      Author: hossam
 */

#ifndef HW_GPIO_H_
#define HW_GPIO_H_
/************************************************************************/
/*        register definition                                           */
/************************************************************************/
#define BASE_A            0x39
#define BASE_B            0x36
#define BASE_C            0x33
#define BASE_D            0x30

#define INPUT_OFFSET      0x00
#define DIR_OFFSET        0x01
#define DATA_OFFSET       0x02

/************************************************************************/
/* Interrupt registers                                                  */
/************************************************************************/

#define SET_REGISTER                             0x5F
#define GENERAL_INTERRUPT_CONTROL_REG            0x5B
#define GENERAL_INTERRUPT_FLAG_REG               0x5A
#define MICRO_CONTROLLER_CONTROL_REG             0x55
#define MICRO_CONTROLLER_CONTROL_AND_STATUS_REG  0x54

#endif /* HW_GPIO_H_ */
