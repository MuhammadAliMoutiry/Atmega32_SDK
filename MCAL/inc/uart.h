/*
 * uart.h
 *
 * Created: 10/29/2019 6:15:40 AM
 *  Author: Muhammad Ali Moutiry
 */ 


#ifndef UART_H_
#define UART_H_
#include "hw_uart.h"
#include "hw_types.h"
#include "types.h"
/******************* UART configuration*********************************/
#define  SPEED_MODE         NORMAL_SPEED
#define  CPU_F               _8_MHZ
#define  BUAD_RATE          BAUD_9600
#define  SYNCH_MODE         ASYNCH
#define  PARITY_MODE        NO_PARITY
#define  N_DATA_BITS        _8_DATA_BITS
#define  N_STOP_BITS        ONE_STOP_BIT


/********************speed mode*************************/
#define NORMAL_SPEED      0
#define DOUBLE_SPEED      1
#define TOTAL_SPEED_MODE  2
/********************cpu freqs***************************/
#define   _4_MHZ         0
#define   _8_MHZ         1
#define  _16_MHZ         2
#define  TOTAL_CPU_F     3
/*******************baud rate *****************************/
#define  BAUD_2400       0
#define  BAUD_4800       1
#define  BAUD_9600       2
#define  BAUD_14400      3
#define  BAUD_19200      4
#define  BAUD_28800      5
#define  TOTAL_BAUD_RATE 6
/*******************parity mode*************************/
#define NO_PARITY    0
#define EVEN_PARITY  1
#define ODD_PARITY   2
/*************** number of data bits********************/
#define  _5_DATA_BITS    5
#define  _6_DATA_BITS    6
#define  _7_DATA_BITS    7
#define  _8_DATA_BITS    8
#define  _9_DATA_BITS    9

/***************      sync mode*************************/
#define  SYNCH  0
#define  ASYNCH 1
/************    number of stop bits*****************/
#define  ONE_STOP_BIT   1
#define  TWO_STOP_BIT   2


void UART_Init(void);

void UART_SendByte(uint8 data);
uint8 UART_ReceiveByte(void);
uint8 UART_Receive_NoBlock(uint8*pdata);



void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));


void UART_SendByteNoBlock_Interrupt(uint8 data);
uint8 UART_ReceiveByteNoBlock_Interrupt(void);
#endif /* UART_H_ */