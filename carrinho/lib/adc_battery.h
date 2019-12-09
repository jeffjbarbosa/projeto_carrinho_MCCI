/*
 * adc_battery.h
 *
 *  Created on: 23 de out de 2019
 *      Author: jeffe
 */

#ifndef LIB_ADC_BATTERY_H_
#define LIB_ADC_BATTERY_H_

#define v_min 0.0
//#define const_adc0_10bit 0.017034566 // multiplicar const pelo valor do ADC resultara no valor da bateria
//#define const_adc1_10bit 0.007324218 // vbat = ((15/2)/1024)*ADC1 relacao do ganho do ampop para o ADC

#define const_adc1_10bit 0.004882812
#define const_adc0_10bit 0.004882812

typedef volatile enum adc_channels{
	ADC0, ADC1
} adc_channels_t;

static adc_channels_t ADC_CHANNEL = ADC0;

void adc_select_channel(adc_channels_t __ch);

void adc_init();

int protect_bat(uint16_t adc_bat1, uint16_t adc_bat_med);

#endif /* LIB_ADC_BATTERY_H_ */
