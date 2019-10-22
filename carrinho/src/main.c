/*
 * main.c
 *
 *  Created on: 22 de out de 2019
 *      Author: jefferson
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/bits.h"
#include "../lib/avr_timer.h"
#include "../lib/avr_gpio.h"
#include "../lib/motor.h"

int main(){

	uint8_t valor_pwm = 1;

	/* Configura timer em modo PWM */
	timer0_pwm_hardware_init();

	timer2_pwm_hardware_init();

	sei();

	/* Exeplo: aumenta em 10 a razão cíclica do PWM a cada 100ms */
	while (1){
		set_dutty(valor_pwm);
		valor_pwm+=10;
		_delay_ms(10);
	}

	return 0;
}
