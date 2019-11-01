/*
 * motor.c
 *
 *  Created on: 22 de out de 2019
 *      Author: jefferson
 */


#include <avr/io.h>
#include <util/delay.h>
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_gpio.h"
#include "../lib/motor.h"

void set_dutty(uint8_t dutty){

	if (dutty <= TIMER_0->OCRA)
		TIMER_0->OCRB = dutty;

	if (dutty <= TIMER_2->OCRA)
			TIMER_2->OCRB = dutty;
}

void timer0_pwm_hardware_init(){

	/* PD5: pino OC0B como saida */
	GPIO_D->DDR |= SET(PD5);

	/* Table 15-6.  Compare Output Mode, Fast PWM Mode */
	/* COM0B1   COM0B0  Desc:
	    0       0       Normal port operation, OC0B disconnected.
	    0       1       Reserved
	    1       0       Clear OC0B on Compare Match, set OC0B at BOTTOM (non-inverting mode)
	    1       1       Set OC0B on Compare Match, clear OC0B at BOTTOM (inverting mode).*/

	/* WGM02, WGM01 WGM00 setados: modo PWM rápido com TOP em OCRA */
	TIMER_0->TCCRA = SET(WGM01) | SET(WGM00) | SET(COM0B1);
	TIMER_0->TCCRB = SET(WGM02) | SET(CS01) | SET(CS00);
	//CLR(CS02)

	/* OCRA define frequência do PWM */
	TIMER_0->OCRA = 124;

	/* OCRB define razão cíclica:  OCRB / OCRA */
	TIMER_0->OCRB = 150;
}

void timer2_pwm_hardware_init(){

	/* PD3: pino OC2B como saida */
	GPIO_D->DDR |= SET(PD3);

	/* Table 15-6.  Compare Output Mode, Fast PWM Mode */
	/* COM0B1   COM0B0  Desc:
	    0       0       Normal port operation, OC0B disconnected.
	    0       1       Reserved
	    1       0       Clear OC0B on Compare Match, set OC0B at BOTTOM (non-inverting mode)
	    1       1       Set OC0B on Compare Match, clear OC0B at BOTTOM (inverting mode).*/

	/* WGM02, WGM01 WGM00 setados: modo PWM rápido com TOP em OCRA */
	TIMER_2->TCCRA = SET(WGM21) | SET(WGM20) | SET(COM2B1);
	TIMER_2->TCCRB = SET(WGM22) | SET(CS21) | SET(CS20);
	//CLR(CS22)
	/* OCRA define frequência do PWM */
	TIMER_2->OCRA = 249;

	/* OCRB define razão cíclica:  OCRB / OCRA */
	TIMER_2->OCRB = 150;
}
