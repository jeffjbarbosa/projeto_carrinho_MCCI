/*
 * adc_battery.h
 *
 *  Created on: 23 de out de 2019
 *      Author: jeffe
 */

#ifndef LIB_ADC_BATTERY_H_
#define LIB_ADC_BATTERY_H_

typedef volatile enum adc_channels{
	ADC0, ADC1
} adc_channels_t;

static adc_channels_t ADC_CHANNEL = ADC0;

void adc_select_channel(adc_channels_t __ch);

void adc_init();

#endif /* LIB_ADC_BATTERY_H_ */
