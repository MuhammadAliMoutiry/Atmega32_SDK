/*
 * uart_services.h
 *
 * Created: 7/7/2020 11:10:33 PM
 *  Author: Muhammad Ali Moutiry
 */ 

#include "uart.h"
#include "utils.h"
#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

void UART_Send_String(uint8 *str);
void UART_Send_StringAsync(uint8 *str);

void UART_Send_StringAsync_NOCodeInInterrupt(uint8 *str);//used inside while(1)
void UART_Receive_String(uint8 *str);
uint8 UART_Receive_StringAsync(uint8*str);

void UART_SendString_MyProtocol(uint8 *str);
uint8 UART_ReceiveString_MyProtocol(uint8 *str);
uint8 UART_frameValues_MyProtocol(uint8 *str,uint8 *s1,uint8*s2,uint8*pnum1,uint8*pnum2);


#endif /* UART_SERVICES_H_ */