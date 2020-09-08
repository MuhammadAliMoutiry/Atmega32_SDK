/*
* timer.c
*
* Created: 10/29/2019 6:17:16 AM
*  Author: Muhammad Ali Moutiry
*/
#include "timer.h"
#include "gpio.h"
#include <avr/interrupt.h>
static void(*timer0_cmp_match_isr)(void);
static void(*timer0_overflow_isr)(void);
static void(*timer2_cmp_match_isr)(void);
static void(*timer2_overflow_isr)(void);

static void(*timer1_cmpA_match_isr)(void);
static void(*timer1_cmpB_match_isr)(void);
static void(*timer1_overflow_isr)(void);
static void(*timer1_ICU_isr)(void);

void init_timer0(tTimerCfg_t *obj){
	if(obj->wave_mode == NORMAL){
		HW_WR_BIT(TMR_CTRL_REG_0 , 6 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 3 , LOW);
		}else if(obj->wave_mode == PHASE_CORRECT_PWM){
		HW_WR_BIT(TMR_CTRL_REG_0 , 6 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 3 , LOW);
		}else if(obj->wave_mode == COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_0 , 6 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 3 , HIGH);
		}else if(obj->wave_mode == FAST_PWM){
		HW_WR_BIT(TMR_CTRL_REG_0 , 6 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 3 , HIGH);
	}
	if(obj->cmp_match_output_mode == NORMAL_PORT_OPERATION_OC0_DISCONNECTED){
		HW_WR_BIT(TMR_CTRL_REG_0 , 4 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 5 , LOW);
		}else if(obj->cmp_match_output_mode == TOGGLE_OC0_ON_COMPARE_MATCH_NON_PWM_MODE){
		HW_WR_BIT(TMR_CTRL_REG_0 , 4 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 5 , LOW);
		init_pin(BASE_B,3,OUTPUT);
		}else if(obj->cmp_match_output_mode == CLEAR_OC0_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_0 , 4 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 5 , HIGH);
		init_pin(BASE_B,3,OUTPUT);
		}else if(obj->cmp_match_output_mode == SET_OC0_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_0 , 4 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 5 , HIGH);
		init_pin(BASE_B,3,OUTPUT);
	}
	if(obj->clock_cource == NO_CLOCK_SOURCE){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , LOW);
		}else if(obj->clock_cource == NO_PRESCALER){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_8){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_64){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_256){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , HIGH);
		}else if(obj->clock_cource == PRESCALER_1024){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , HIGH);
		}else if(obj->clock_cource == EXT_ON_T0_PIN_FALLING_EDGE){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , HIGH);
		}else if(obj->clock_cource == EXT_ON_T0_PIN_RISING_EDGE){
		HW_WR_BIT(TMR_CTRL_REG_0 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , HIGH);
	}
	
}

void init_timer2(tTimerCfg_t *obj){
	if(obj->wave_mode == NORMAL){
		HW_WR_BIT(TMR_CTRL_REG_2 , 6 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 3 , LOW);
		}else if(obj->wave_mode == PHASE_CORRECT_PWM){
		HW_WR_BIT(TMR_CTRL_REG_2 , 6 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 3 , LOW);
		}else if(obj->wave_mode == COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_2 , 6 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 3 , HIGH);
		}else if(obj->wave_mode == FAST_PWM){
		HW_WR_BIT(TMR_CTRL_REG_2 , 6 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 3 , HIGH);
	}
	if(obj->cmp_match_output_mode == NORMAL_PORT_OPERATION_OC2_DISCONNECTED){
		HW_WR_BIT(TMR_CTRL_REG_2 , 4 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 5 , LOW);
		}else if(obj->cmp_match_output_mode == TOGGLE_OC2_ON_COMPARE_MATCH_NON_PWM_MODE){
		HW_WR_BIT(TMR_CTRL_REG_2 , 4 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 5 , LOW);
		init_pin(BASE_D,7,OUTPUT);
		}else if(obj->cmp_match_output_mode == CLEAR_OC2_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_2 , 4 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 5 , HIGH);
		init_pin(BASE_D,7,OUTPUT);
		}else if(obj->cmp_match_output_mode == SET_OC2_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_2 , 4 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 5 , HIGH);
		init_pin(BASE_D,7,OUTPUT);
	}
	if(obj->clock_cource == NO_CLOCK_SOURCE){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_0 , 2 , LOW);
		}else if(obj->clock_cource == NO_PRESCALER){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_8){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_64){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_256){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 2 , HIGH);
		}else if(obj->clock_cource == PRESCALER_1024){
		HW_WR_BIT(TMR_CTRL_REG_2 , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_2 , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_2 , 2 , HIGH);
	}
	
}


void init_timer1(tTimerCfg_t *obj){
	if(obj->wave_mode==NORMAL){
		HW_WR_BIT(TMR_CTRL_REG_1A,0,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,1,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,3,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,4,LOW);
		}else if(obj->wave_mode==COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_1A,0,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,1,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,3,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B,4,LOW);
		}else if(obj->wave_mode == FAST_PWM){
		HW_WR_BIT(TMR_CTRL_REG_1A,0,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,1,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,3,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,4,LOW);
		}else if(obj->wave_mode == PHASE_CORRECT_PWM){
		HW_WR_BIT(TMR_CTRL_REG_1A,0,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,1,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,3,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B,4,LOW);
	}
	if(obj->clock_cource == NO_CLOCK_SOURCE){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , LOW);
		}else if(obj->clock_cource == NO_PRESCALER){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_8){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_64){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , LOW);
		}else if(obj->clock_cource == PRESCALER_256){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , HIGH);
		}else if(obj->clock_cource == PRESCALER_1024){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , HIGH);
		}else if(obj->clock_cource == EXT_ON_T1_PIN_FALLING_EDGE){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , LOW);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , HIGH);
		}else if(obj->clock_cource == EXT_ON_T1_PIN_RISING_EDGE){
		HW_WR_BIT(TMR_CTRL_REG_1B , 0 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 1 , HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1B , 2 , HIGH);
	}
	if (obj->cmp_match_output_mode == NORMAL_PORT_OPERATION_OC1A_DISCONNECTED){
		HW_WR_BIT(TMR_CTRL_REG_1A,6,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,7,LOW);
		}else if (obj->cmp_match_output_mode ==TOGGLE_OCA1_ON_COMPARE_MATCH ){
		HW_WR_BIT(TMR_CTRL_REG_1A,6,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,7,LOW);
		init_pin(BASE_D,5,OUTPUT);
		}else if (obj->cmp_match_output_mode == CLEAR_OCA1_ON_COMPARE_MATCH ){
		HW_WR_BIT(TMR_CTRL_REG_1A,6,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,7,HIGH);
		init_pin(BASE_D,5,OUTPUT);
		}else if (obj->cmp_match_output_mode == SET_OCA1_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_1A,6,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,7,HIGH);
		init_pin(BASE_D,5,OUTPUT);
		}else if (obj->cmp_match_output_mode == NORMAL_PORT_OPERATION_OC1B_DISCONNECTED ){
		HW_WR_BIT(TMR_CTRL_REG_1A,4,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,5,LOW);
		}else if (obj->cmp_match_output_mode == TOGGLE_OCB1_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_1A,4,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,5,LOW);
		init_pin(BASE_D,4,OUTPUT);
		}else if (obj->cmp_match_output_mode == CLEAR_OCB1_ON_COMPARE_MATCH){
		HW_WR_BIT(TMR_CTRL_REG_1A,4,LOW);
		HW_WR_BIT(TMR_CTRL_REG_1A,5,HIGH);
		init_pin(BASE_D,4,OUTPUT);
		}else if (obj->cmp_match_output_mode == SET_OCB1_ON_COMPARE_MATCH ){
		HW_WR_BIT(TMR_CTRL_REG_1A,4,HIGH);
		HW_WR_BIT(TMR_CTRL_REG_1A,5,HIGH);
		init_pin(BASE_D,4,OUTPUT);
	}
	
}



void timer0_interrupt_enable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == OUTPUT_COMPARE_MATCH_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,1,HIGH);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,0,HIGH);
	}
}

void timer0_interrupt_disable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == OUTPUT_COMPARE_MATCH_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,1,LOW);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,0,LOW);
	}
}

void timer0_set_output_compare(uint8 value){
	HW_WR_PORT(TMR_OUTPUT_CMP_REG_0,value);
}

void timer2_interrupt_enable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == OUTPUT_COMPARE_MATCH_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,7,HIGH);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,6,HIGH);
	}
}

void timer2_interrupt_disable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == OUTPUT_COMPARE_MATCH_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,7,LOW);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,6,LOW);
	}
}

void timer2_set_output_compare(uint8 value){
	HW_WR_PORT(TMR_OUTPUT_CMP_REG_2,value);
}

void timer1_interrupt_enable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == TIMER1_OCMA_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,4,HIGH);
		}else if (interrupt == TIMER1_OCMB_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,3,HIGH);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,2,HIGH);
	}
}

void timer1_interrupt_disable(tTimerInterrupt_t interrupt){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	if(interrupt == TIMER1_OCMA_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,4,LOW);
		}else if (interrupt == TIMER1_OCMB_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,3,LOW);
		}else if(interrupt == OVERFLOW_INTERRUPT){
		HW_WR_BIT(TMR_INTERR_MASK_REG,2,LOW);
	}
}


void timer0_OCM_ISR(void(* compare_match_isr)(void)){
	timer0_cmp_match_isr = compare_match_isr;
}

void timer0_overflow_ISR(void (*overflow_isr)(void)){
	timer0_overflow_isr = overflow_isr;
}

void timer2_OCM_ISR(void(* compare_match_isr)(void)){
	timer2_cmp_match_isr = compare_match_isr;
}

void timer2_overflow_ISR(void (*overflow_isr)(void)){
	timer2_overflow_isr = overflow_isr;
}

void timer1_OCMA_ISR(void(* compare_matchA_isr)(void)){
	timer1_cmpA_match_isr = compare_matchA_isr;
}

void timer1_OCMB_ISR(void(* compare_matchB_isr)(void)){
	timer1_cmpB_match_isr = compare_matchB_isr;
}

void timer1_overflow_ISR(void (*overflow_isr)(void)){
	timer1_overflow_isr = overflow_isr;
}

void timer1_ICU_ISR(void (*ICU_isr)(void)){
	timer1_ICU_isr = ICU_isr;
}

void timer1_input_capture_noise_canceler_enable(){
	HW_WR_BIT(TMR_CTRL_REG_1B,7,HIGH);
}

void timer1_ICU_edge_select(tICUedgeSelect_t edge){
	HW_WR_BIT(TMR_CTRL_REG_1B,6,edge);
	init_pin(BASE_D,6,INPUT);
}

uint16 timer1_ICU_read(){
	uint16 value=0;
	value = HW_READ_REG(TMR_INPUT_CAPTURE_REG_1L);
	value |= (HW_READ_REG(TMR_INPUT_CAPTURE_REG_1H))<<8;
	return value;
}

void timer1_ICU_clear_flag(){
	HW_WR_BIT(TMR_INTERR_FLAG_REG,5,HIGH);
}

void timer1_ICU_wait_for_edge(){
	while (HW_READ_BIT(TMR_INTERR_FLAG_REG,5)==0);
}
void timer1_ICU_interrupt_enable(){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	HW_WR_BIT(TMR_INTERR_MASK_REG,5,HIGH);
}

void timer1_ICU_interrupt_disable(){
	HW_WR_BIT(STATUS_REG,7,HIGH); // enable global interrupt
	HW_WR_BIT(TMR_INTERR_MASK_REG,5,LOW);
}

void set_duty_cycle(tTimerSelect_t timer,uint8 duty){
	uint16 temp = 0;
	temp = ((duty * 256)/100) - 1 ;
	if(timer == TIMER0_8BIT){
		HW_WR_PORT(TMR_OUTPUT_CMP_REG_0 ,temp);
		}else if(timer == TIMER2_8BIT){
		HW_WR_PORT(TMR_OUTPUT_CMP_REG_2 ,temp);
		}else if (timer == TIMER1_16BIT_CHA){
		HW_WR_PORT(TMR_OUTPUT_CMP_REG_1AL,temp);
		}else if (timer == TIMER1_16BIT_CHB){
		HW_WR_PORT(TMR_OUTPUT_CMP_REG_1BL,temp);
	}
	
}

uint8 timer0_get_count(void){
	return HW_READ_REG(TMR_COUNT_REG_0);
}
void timer0_set_count(uint8 value){
	HW_WR_PORT(TMR_COUNT_REG_0,value);
}
uint8 timer2_get_count(void){
	return HW_READ_REG(TMR_COUNT_REG_2);
}
void timer2_set_count(uint8 value){
	HW_WR_PORT(TMR_COUNT_REG_2,value);
}




ISR(TIMER0_COMP_vect){
	timer0_cmp_match_isr();
}

ISR(TIMER0_OVF_vect){
	timer0_overflow_isr();
}

ISR(TIMER2_COMP_vect){
	timer2_cmp_match_isr();
}

ISR(TIMER2_OVF_vect){
	timer2_overflow_isr();
}

ISR(TIMER1_OVF_vect){
	timer1_overflow_isr();
}

ISR(TIMER1_COMPA_vect){
	timer1_cmpA_match_isr();
}

ISR(TIMER1_COMPB_vect){
	timer1_cmpB_match_isr();
}

ISR(TIMER1_CAPT_vect){
	timer1_ICU_isr();
}

