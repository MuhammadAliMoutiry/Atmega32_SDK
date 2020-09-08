/*
 * spi.h
 *
 * Created: 10/29/2019 6:15:29 AM
 *  Author: Muhammad Ali Moutiry
 */ 
#include "types.h"
#include "hw_types.h"
#include "hw_spi.h"

#ifndef SPI_H_
#define SPI_H_

typedef enum spi_data_order{
	SPI_SEND_LSB_FIRST = 0,
	SPI_SEND_MSB_FIRST
	}sSpiDataOrder_t;

typedef enum spiMode{
	SPI_SLAVE_MODE = 0,
	SPI_MASTER_MODE
	}sSpiModeSel_t;

typedef enum spiClockPolarity{
	SPI_LEADING_RISING__TRAILING_FALLING=0,
	SPI_LEADING_FALLING__TRAILING_RISING	
	}sSpiClockPolarity_t;
	
typedef enum spiClockPhase{
	SPI_SAMPLE_ON_LEADING_EDGE = 0,
	SPI_SAMPLE_ON_TRAILING_EDGE
	}sSpiClockPhase_t;
	
typedef enum spiClockRate{
	SPI_PRESCALER_4=0,
	SPI_PRESCALER_16,
	SPI_PRESCALER_64,
	SPI_PRESCALER_128,
	SPI_PRESCALER_2,
	SPI_PRESCALER_8,
	SPI_PRESCALER_32,	
	}sSpiClockRate_t;
	
typedef struct spiConfig{
	sSpiDataOrder_t data_order;
	sSpiModeSel_t spi_mode;
	sSpiClockPolarity_t spi_clock_polarity;
	sSpiClockPhase_t spi_clock_phase;
	sSpiClockRate_t spi_clock_rate;
	}sSpiConfig_t;
	
void init_spi(sSpiConfig_t *obj);
void spi_send_data(uint8 data);
uint8 spi_receive_data(void);

void init_spi_interrupt();
void spi_transfer_complete_ISR(void(* transfer_complete_isr)(void));
uint8 spi_read_data_interrupt();
#endif /* SPI_H_ */