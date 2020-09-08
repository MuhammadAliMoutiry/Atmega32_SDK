/*
* uart_services.c
*
* Created: 7/7/2020 11:09:59 PM
*  Author: Muhammad Ali Moutiry
*/
#include "uart_services.h"

static volatile uint8 flag=1;
static volatile uint8 receive_async_flag=0;
static volatile uint8 *send_str_async_temp;
static volatile uint8 *receive_str_async_temp;

void UART_Send_String(uint8 *str){
	uint8 i=0;
	while (str[i] !='\0')
	{
		UART_SendByte(str[i]);
		i++;
	}
}
/*************************************************************************/
static void send_asyn(void){
	static uint8 i =1;
	if (send_str_async_temp[i] !='\0'){
		UART_SendByteNoBlock_Interrupt(send_str_async_temp[i]);
		i++;
		}else{
		i=1;
		UART_TX_InterruptDisable();
	}
}

void UART_Send_StringAsync(uint8 *str){
	send_str_async_temp=str;
	UART_TX_SetCallBack(send_asyn);
	UART_TX_InterruptEnable();
	UART_SendByte(str[0]);	
}

/***********************************************************************/
static void flag_monitor(void){
	flag=1;
}

void UART_Send_StringAsync_NOCodeInInterrupt(uint8 *str){
	static uint8 i =0;
	UART_TX_SetCallBack(flag_monitor);
	UART_TX_InterruptEnable();
	if (flag){
		if (str[i]){
			UART_SendByteNoBlock_Interrupt(str[i]);
			flag=0;
			i++;
		}else{
			i=0;
		}
	}
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void UART_Receive_String(uint8 *str){
	uint8 i=0;
	do 
	{
		str[i]=UART_ReceiveByte();
		i++;
	} while (str[--i]!='#');
}
/*****************************************************************************/
static void receive_str(void){
	static uint8 i=0;
	receive_str_async_temp[i]=UART_ReceiveByteNoBlock_Interrupt();
	if (receive_str_async_temp[i] =='#'){
         receive_async_flag=1;
		 receive_str_async_temp[i]='\0';
		UART_RX_InterruptDisable();
		
	}else{
		i++;
		receive_async_flag=0;
	}
	
}

uint8 UART_Receive_StringAsync(uint8*str){
	receive_str_async_temp=str;
	UART_RX_SetCallBack(receive_str);
	UART_RX_InterruptEnable();
	return receive_async_flag;
}

/************************************************************************
 Invented protocol                                                    

Frame :string length, String1 , Number1 , String2 , Number2 , 2 bytes check sum
************************************************************************/
void UART_SendString_MyProtocol(uint8 *str){
	uint8 i=0,lens=0;
	uint16 sum = 0;
	while (str[lens] !='\0')
	{
		lens++;
		sum +=str[lens];
	}
	UART_SendByte(lens);
	for (i=0;i<lens;i++){
		UART_SendByte(str[i]);
	}
	UART_SendByte((uint8)sum);
	UART_SendByte((uint8)(sum>>8));
}

uint8 UART_ReceiveString_MyProtocol(uint8 *str){
	
	uint8 lens = UART_ReceiveByte();
	uint8 i,checkSum_firstByte=0,checkSum_secondByte=0;
	uint16 sum_received=0,sum_calculated=0;
	for(i=0;i<lens;i++){
		str[i]=UART_ReceiveByte();
		sum_calculated +=str[i];
	}
	checkSum_firstByte = UART_ReceiveByte();
	checkSum_secondByte = UART_ReceiveByte();
	sum_received = (uint16)checkSum_firstByte | ((uint16)(checkSum_secondByte<<8));
	if (sum_received == sum_calculated)return 1;
	else return 0;
}

uint8 UART_frameValues_MyProtocol(uint8 *str,uint8 *s1,uint8*s2,uint8*pnum1,uint8*pnum2)
{
	uint8 i=0,j=0,k=0,flag=0,temp,status=1;
	uint16 num1=0,num2=0;
	while(str[i]!='\0')
	{
		if (str[i]==',')
		{
			flag++;
		}
		else
		{
			if (flag==0)
			{
				s1[j]=str[i];
				j++;
			}
			else if (flag==1)
			{
				if ((str[i]>='0')&&(str[i]<='9'))
				{
					temp=str[i]-'0';
					num1=num1*10+temp;
				}
				else
				status=0;
				
			}
			else if (flag==2)
			{
				s2[k]=str[i];
				k++;
			}
			else if (flag==3)
			{
				temp=str[i]-'0';
				num2=num2*10+temp;
			}
		}
		
		i++;
	}
	s1[j]='\0';
	s2[k]='\0';
	*pnum1=num1;
	*pnum2=num2;
	if (flag!=3)
	{
		status=0;
	}
	return status;
}
