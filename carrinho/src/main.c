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
#define RIGHT_SPEED 200
#define LEFT_SPEED 200

//volatile uint16_t bat1=0;
//volatile uint16_t bat_med=0;

uint8_t serial_char;
uint8_t switch_controller = 0;


int main(){
	uint8_t r_spd = RIGHT_SPEED;
	uint8_t l_spd = LEFT_SPEED;

	/* Obtem o stream de depuracao */
		FILE *debug = get_usart_stream();

		/* Inicializa hardware da USART */
			USART_Init(B9600);

	/* inicia adc */
	//adc_init();

	/* Configura timer em modo PWM */
	timer_pwm_init();
	sei();
	while (1){

		serial_char = USART_rx();


		if(serial_char == 'X') {
			switch_controller = 1;
		}
		else if(serial_char == 'x'){
			switch_controller = 0;
		}

		if (switch_controller == 1) {

			// controle de direcao //
			if (serial_char == 'F' ){
				frente(l_spd, r_spd);
				fprintf(debug, "%c\n\r",serial_char);
			}
			else if(serial_char == 'B'){
				reh(l_spd, r_spd);
				fprintf(debug, "%c\n\r",serial_char);
			}
			else if(serial_char == 'L'){
				esquerda(l_spd, r_spd);
				fprintf(debug, "%c\n\r",serial_char);
			}
			else if(serial_char == 'R'){
				direita(l_spd, r_spd);
				fprintf(debug, "%c\n\r",serial_char);
			}
			else if(serial_char == 'G'){
						// funcao frente e esquerda (curva <--)
				fprintf(debug, "curva para esquerda\n\r");
					}
			else if(serial_char == 'I'){
						// funcao frente e direita (curva -->)
				fprintf(debug, "curva para direita\n\r");
					}
			else if(serial_char == 'H'){
						// funcao reh e esquerda
				fprintf(debug, "reh para esquerda\n\r");
					}
			else if(serial_char == 'J'){
						// funcao reh e direita
				fprintf(debug, "reh para esquerda\n\r");
					}
			else if(serial_char == 'S'){
				fprintf(debug, "%c\n\r",serial_char);
				stop();
			}

			// controle de velocidade //

			if (serial_char == '0'){
						r_spd = 0;
						l_spd = 0;
			}
			else if (serial_char == '1'){
				r_spd = 25;
				l_spd = 25;
			}
			else if(serial_char == '2'){
				r_spd = 50;
				l_spd = 50;
			}
			else if(serial_char == '3'){
				r_spd = 75;
				l_spd = 75;
			}
			else if(serial_char == '4'){
				r_spd = 100;
				l_spd = 100;
			}
			else if(serial_char == '5'){
				r_spd = 125;
				l_spd = 125;
			}
			else if(serial_char == '6'){
				r_spd = 150;
				l_spd = 150;
			}
			else if(serial_char == '7'){
				r_spd = 175;
				l_spd = 175;
			}
			else if(serial_char == '8'){
				r_spd = 200;
				l_spd = 200;
			}
			else if(serial_char == '9'){
				r_spd = 225;
				l_spd = 225;
			}
			else if(serial_char == 'q'){
				r_spd = 255;
				l_spd = 255;
			}
			else if (serial_char == 'D'){
				stop();
			}
		}
		else {
			// executa funcao andar sozinho
			fprintf(debug,"andando sozinho\n");
		}

		//fprintf(debug, "%d\n\r", bat1);
		//fprintf(debug, "%d\n\r", bat_med);

		//if (protect_bat(bat1, bat_med) == 1){
		//	fprintf(debug, "tensao da bateria caiu!\n\r");
		//}
	}

	return 0;
}

/*ISR(ADC_vect){
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
}*/
