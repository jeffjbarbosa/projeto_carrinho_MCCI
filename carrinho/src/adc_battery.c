/*
 * adc_battery.c
 *
 *  Created on: 23 de out de 2019
 *      Author: jeffe
 */

#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib/avr_gpio.h"
#include "../lib/avr_adc.h"
#include "../lib/bits.h"

#include "../lib/avr_usart.h"
#include "../lib/adc_battery.h"

void adc_init(){

	// teste com led da protecao da bateria


	/* Ref externa no pino AVCC com capacitor de 100n em VREF.
	 * Habiltiação apenas no Canal 0 */
	ADCS->AD_MUX = SET(REFS0);     // 5v ref
	/* Habilita AD:
	 * Conversão contínua
	 * IRQ ativo
	 * Prescaler de 128 */
	ADCS->ADC_SRA = SET(ADEN)  |	//ADC Enable
					SET(ADSC)  | 	// ADC Start conversion
					SET(ADATE) |	// ADC Auto Trigger
					SET(ADPS0) | SET(ADPS1) | SET(ADPS2) | //ADPS[0..2] AD Prescaler selection prsc = 128
					SET(ADIE); 		//AD IRQ ENABLE

	/* Desabilita hardware digital de PC0 e PC1*/
	ADCS->DIDr0.BITS.ADC0 = 1;
	ADCS->DIDr1.BITS.ADC1 = 1;

}

void adc_select_channel(adc_channels_t __ch)
{
	ADC_CHANNEL = __ch;
	ADMUX = (ADMUX & 0xF8) | ADC_CHANNEL; // clears the bottom 3 bits before ORing
}

int protect_bat(uint16_t adc_bat1, uint16_t adc_bat_med){
	int v_limit = 0;
	float v_bat1 = const_adc0_10bit*adc_bat1;
	float v_bat_med = const_adc1_10bit*adc_bat_med;

	if(v_bat_med <= v_min){
		//dar um jeito de parar a coisa toda
		v_limit = 1;
	}
	else if((v_bat1 - v_bat_med) <= v_min){
		// tambem dar um jeito de parar a coisa toda
		v_limit = 1;
	}
	return v_limit;
}
