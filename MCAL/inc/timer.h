/*
 * timer.h
 *
 * Created: 10/29/2019 6:15:14 AM
 *  Author: Muhammad Ali Moutiry
 */ 

#include "types.h"
#include "hw_types.h"
#include "hw_timer.h"

#ifndef TIMER_H_
#define TIMER_H_

typedef enum timersel{
	TIMER0_8BIT =0,
	TIMER1_16BIT_CHA,
	TIMER1_16BIT_CHB,
	TIMER2_8BIT
	}tTimerSelect_t;
	
typedef enum tWaveMode{
	NORMAL=0 ,PHASE_CORRECT_PWM , COMPARE_MATCH , FAST_PWM
	}tWaveMode_t;

typedef enum tCmpMatchOutputMode{
	NORMAL_PORT_OPERATION_OC0_DISCONNECTED =0,
	TOGGLE_OC0_ON_COMPARE_MATCH_NON_PWM_MODE,
	CLEAR_OC0_ON_COMPARE_MATCH ,
	SET_OC0_ON_COMPARE_MATCH,
	
	NORMAL_PORT_OPERATION_OC2_DISCONNECTED,
	TOGGLE_OC2_ON_COMPARE_MATCH_NON_PWM_MODE  ,
	CLEAR_OC2_ON_COMPARE_MATCH,
	SET_OC2_ON_COMPARE_MATCH,
	
	NORMAL_PORT_OPERATION_OC1A_DISCONNECTED,
	TOGGLE_OCA1_ON_COMPARE_MATCH ,
	CLEAR_OCA1_ON_COMPARE_MATCH ,
	SET_OCA1_ON_COMPARE_MATCH,
	
	NORMAL_PORT_OPERATION_OC1B_DISCONNECTED,
	TOGGLE_OCB1_ON_COMPARE_MATCH ,
	CLEAR_OCB1_ON_COMPARE_MATCH ,
	SET_OCB1_ON_COMPARE_MATCH,
	
	}tCmpMatchOutputMode_t;

typedef enum tClockSource{
	NO_CLOCK_SOURCE , NO_PRESCALER , PRESCALER_8 , PRESCALER_64 ,
    PRESCALER_256 , PRESCALER_1024 , EXT_ON_T0_PIN_FALLING_EDGE ,
    EXT_ON_T0_PIN_RISING_EDGE, EXT_ON_T1_PIN_FALLING_EDGE ,
    EXT_ON_T1_PIN_RISING_EDGE
	}tClockSource_t;
	

typedef struct tTimerCfg{
	tClockSource_t clock_cource;
	tCmpMatchOutputMode_t cmp_match_output_mode;
	tWaveMode_t wave_mode;
	}tTimerCfg_t;

typedef enum timerInterrupt{
	OUTPUT_COMPARE_MATCH_INTERRUPT,
	OVERFLOW_INTERRUPT,
	TIMER1_OCMA_INTERRUPT,
	TIMER1_OCMB_INTERRUPT
	}tTimerInterrupt_t;
	
typedef enum ICU_edge{
	ICU_FALLING_EDGE=0,
	ICU_RISING_EDGE
	}tICUedgeSelect_t;
	
void init_timer0(tTimerCfg_t *obj);
void timer0_interrupt_enable(tTimerInterrupt_t interrupt);
void timer0_interrupt_disable(tTimerInterrupt_t interrupt);
uint8 timer0_get_count(void);
void timer0_set_count(uint8 value);
void timer0_set_output_compare(uint8 value);
void timer0_OCM_ISR(void(* compare_match_isr)(void));
void timer0_overflow_ISR(void (*overflow_isr)(void));

void init_timer2(tTimerCfg_t *obj);
void timer2_interrupt_enable(tTimerInterrupt_t interrupt);
void timer2_interrupt_disable(tTimerInterrupt_t interrupt);
uint8 timer2_get_count(void);
void timer2_set_count(uint8 value);
void timer2_set_output_compare(uint8 value);
void timer2_OCM_ISR(void(* compare_match_isr)(void));
void timer2_overflow_ISR(void (*overflow_isr)(void));

void init_timer1(tTimerCfg_t *obj);
void timer1_interrupt_enable(tTimerInterrupt_t interrupt);
void timer1_interrupt_disable(tTimerInterrupt_t interrupt);
void timer1_OCMA_ISR(void(* compare_matchA_isr)(void));
void timer1_OCMB_ISR(void(* compare_matchB_isr)(void));
void timer1_overflow_ISR(void (*overflow_isr)(void));

void timer1_input_capture_noise_canceler_enable();
void timer1_ICU_edge_select(tICUedgeSelect_t edge);
void timer1_ICU_clear_flag();
void timer1_ICU_wait_for_edge();
uint16 timer1_ICU_read();
void timer1_ICU_interrupt_enable();
void timer1_ICU_interrupt_disable();
void timer1_ICU_ISR(void (*ICU_isr)(void));

void set_duty_cycle(tTimerSelect_t timer,uint8 duty);

#endif /* TIMER_H_ */