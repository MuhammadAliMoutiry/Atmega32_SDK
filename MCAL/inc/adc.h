/*
* adc.h
*
* Created: 9/9/2016 8:32:35 PM
*  Author: Muhammad Ali
*/
#include "types.h"

#ifndef ADC_H_
#define ADC_H_

/*uncomment the next line to enable differential input*/
//#define ENABLE_ADC_DIFFERENTIAL_INPUT

/*Uncomment the next line to Enable Auto trigger sources*/
//#define ENABLE_AUTO_TRIGGER_SOURCE

typedef enum voltageReference{
	VoltageReferenceAt_AREF_pin = 0 ,
	VoltageReferenceAt_AVCC_pinWithExternalCapacitorAt_AREF_pin,
	Internal_2560mV_VoltageReferanceWithExternalCapacitorAt_AREF_pin
}referenceVoltageSelect_t;

typedef enum channel{
	Single_Ended_Input_On_Channel_0_ADC0 = 0 ,
	Single_Ended_Input_On_Channel_1_ADC1 ,
	Single_Ended_Input_On_Channel_2_ADC2 ,
	Single_Ended_Input_On_Channel_3_ADC3 ,
	Single_Ended_Input_On_Channel_4_ADC4 ,
	Single_Ended_Input_On_Channel_5_ADC5 ,
	Single_Ended_Input_On_Channel_6_ADC6 ,
	Single_Ended_Input_On_Channel_7_ADC7 ,
	
	
	DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0  ,
	DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0 ,
	DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2  ,
	DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2 ,
	DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC2

}channelSelect_t;

typedef enum prescaler{
	DivisionBy_2 = 0 ,
	DivisionBy_4 ,
	DivisionBy_8 ,
	DivisionBy_16 ,
	DivisionBy_32 ,
	DivisionBy_64 ,
	DivisionBy_128
}adcPrescaler_t;

typedef enum autotrigger{
	AutoTriggerIS_Disabled = 0    ,
	Free_Running_Mode             ,
	Analog_Comparator             ,
	External_Interrupt_Request_0  ,
	Timer_Counter0_Compare_Match  ,
	Timer_Counter0_Overflow       ,
	Timer_Counter_Compare_Match_B ,
	Timer_Counter1_Overflow       ,
	Timer_Counter1_Capture_Event
}autoTriggerSource_t;

typedef struct adcConfig{
	referenceVoltageSelect_t select_reference_voltage ;
	channelSelect_t select_ADC_channel ;
	adcPrescaler_t select_ADC_prescaler ;
	autoTriggerSource_t select_AutoTrigger_source ;
	
}adcConfig_t;


uint8 init_adc(adcConfig_t *obj);
uint8 adc_read(uint16 *data );
uint8 init_adc_interrupt( void(*adcInterruptFunctionPtr)(void) );

#endif /* ADC_H_ */