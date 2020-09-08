/*
* spi.c
*
* Created: 10/29/2019 6:17:05 AM
*  Author: Muhammad Ali Moutiry
*/
#include "spi.h"
#include "gpio.h"
#include <avr/interrupt.h>
static void(*spi_STC_isr)(void);

void init_spi(sSpiConfig_t *obj){
	
	if(obj->data_order == SPI_SEND_LSB_FIRST){
		HW_WR_BIT(SPI_CONTROL_REG,5,HIGH);
		}else if(obj->data_order == SPI_SEND_MSB_FIRST){
		HW_WR_BIT(SPI_CONTROL_REG,5,LOW);
	}
	if(obj->spi_mode == SPI_MASTER_MODE){
		init_pin(BASE_B,4,OUTPUT);//SS
		write_pin(BASE_B,4,LOW);
		init_pin(BASE_B,5,OUTPUT);//MOSI
		init_pin(BASE_B,6,INPUT);//MISO
		init_pin(BASE_B,7,OUTPUT);//CLK
		HW_WR_BIT(SPI_CONTROL_REG,4,HIGH);
		
		}else if(obj->spi_mode == SPI_SLAVE_MODE){
		HW_WR_BIT(SPI_CONTROL_REG,4,LOW);
		init_pin(BASE_B,4,INPUT);//SS
		init_pin(BASE_B,5,INPUT);//MOSI
		init_pin(BASE_B,6,OUTPUT);//MISO
		init_pin(BASE_B,7,INPUT);//CLK
	}
	if(obj->spi_clock_polarity == SPI_LEADING_RISING__TRAILING_FALLING){
		HW_WR_BIT(SPI_CONTROL_REG,3,LOW);
		}else if(obj->spi_clock_polarity == SPI_LEADING_FALLING__TRAILING_RISING){
		HW_WR_BIT(SPI_CONTROL_REG,3,HIGH);
	}
	if(obj->spi_clock_phase == SPI_SAMPLE_ON_LEADING_EDGE){
		HW_WR_BIT(SPI_CONTROL_REG,2,LOW);
		}if(obj->spi_clock_phase == SPI_SAMPLE_ON_TRAILING_EDGE){
		HW_WR_BIT(SPI_CONTROL_REG,2,HIGH);
	}
	if(obj->spi_clock_rate == SPI_PRESCALER_4){
		HW_WR_BIT(SPI_CONTROL_REG,0,LOW);
		HW_WR_BIT(SPI_CONTROL_REG,1,LOW);
		HW_WR_BIT(SPI_STATUS_REG,0,LOW);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_16){
		HW_WR_BIT(SPI_CONTROL_REG,0,HIGH);
		HW_WR_BIT(SPI_CONTROL_REG,1,LOW);
		HW_WR_BIT(SPI_STATUS_REG,0,LOW);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_64){
		HW_WR_BIT(SPI_CONTROL_REG,0,LOW);
		HW_WR_BIT(SPI_CONTROL_REG,1,HIGH);
		HW_WR_BIT(SPI_STATUS_REG,0,LOW);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_128){
		HW_WR_BIT(SPI_CONTROL_REG,0,HIGH);
		HW_WR_BIT(SPI_CONTROL_REG,1,HIGH);
		HW_WR_BIT(SPI_STATUS_REG,0,LOW);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_2){
		HW_WR_BIT(SPI_CONTROL_REG,0,LOW);
		HW_WR_BIT(SPI_CONTROL_REG,1,LOW);
		HW_WR_BIT(SPI_STATUS_REG,0,HIGH);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_8){
		HW_WR_BIT(SPI_CONTROL_REG,0,HIGH);
		HW_WR_BIT(SPI_CONTROL_REG,1,LOW);
		HW_WR_BIT(SPI_STATUS_REG,0,HIGH);
		}else if(obj->spi_clock_rate == SPI_PRESCALER_32){
		HW_WR_BIT(SPI_CONTROL_REG,0,LOW);
		HW_WR_BIT(SPI_CONTROL_REG,1,HIGH);
		HW_WR_BIT(SPI_STATUS_REG,0,HIGH);
	}
	
	HW_WR_BIT(SPI_CONTROL_REG,6,HIGH);//enable SPI
}

void spi_send_data(uint8 data){
	HW_WR_PORT(SPI_DATA_REG,data);
	while(HW_READ_BIT(SPI_STATUS_REG,7) == 0);
}

uint8 spi_receive_data(void){
	while(HW_READ_BIT(SPI_STATUS_REG,7) == 0);
	return (HW_READ_REG(SPI_DATA_REG));
}

void init_spi_interrupt(){
	HW_WR_BIT(SPI_GLOBAL_INTERRUPT_EN_REG,7,HIGH); // enable global interrupt
	HW_WR_BIT(SPI_CONTROL_REG,7,HIGH);
}

void spi_transfer_complete_ISR(void(* transfer_complete_isr)(void)){
	spi_STC_isr = transfer_complete_isr;
}
ISR(SPI_STC_vect){
	spi_STC_isr();
}

uint8 spi_read_data_interrupt(){
	return HW_READ_REG(SPI_DATA_REG);
}