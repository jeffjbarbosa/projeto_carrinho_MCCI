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
#include "../lib/avr_adc.h"
#include "../lib/adc_battery.h"
#include "../lib/avr_usart.h"

volatile uint16_t bat1=0;
volatile uint16_t bat_med=0;

int main(){

	/* Obtem o stream de depuracao */
		FILE *debug = get_usart_stream();

		/* Inicializa hardware da USART */
			USART_Init(B9600);

	//uint8_t valor_pwm = 50;

	/* inicia adc */
	adc_init();

	/* Configura timer em modo PWM */
	//timer0_pwm_hardware_init();

	//timer2_pwm_hardware_init();
	sei();
	//set_dutty(valor_pwm);
	while (1){
		//set_dutty(valor_pwm);
		//valor_pwm+=10;
		//_delay_ms(10);
		_delay_ms(500);
		fprintf(debug, "%d\n\r", bat1);
		fprintf(debug, "%d\n\r", bat_med);

		if (protect_bat(bat1, bat_med) == 1){
			fprintf(debug, "tensao da bateria caiu!\n\r");
		}
	}

	return 0;
}

ISR(ADC_vect){
	switch (ADC_CHANNEL)
		{
			case 0:
			bat1 = ADC;
			// seleciona o proximo canal (ADC_CHANNEL_1  eh uma enumeracao)
			adc_select_channel(ADC1);
			ADC_CHANNEL = ADC1;
			break;

			case 1:
			bat_med = ADC;
			adc_select_channel(ADC0);
			ADC_CHANNEL = ADC0;
			break;
		}
}
