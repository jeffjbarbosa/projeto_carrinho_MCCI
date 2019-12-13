/*
 * controle.c
 *
 *  Created on: 10 de dez de 2019
 *      Autores: jefferson e Marcelo
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib/avr_gpio.h"
#include "lib/avr_timer.h"
#include "lib/avr_usart.h"
#include "lib/bits.h"
#include "controle.h"
#include "motor.h"


#define SENSOR_E PC2
#define SENSOR_D PC3


unsigned int Inicio_Sinal, Distancia;


ISR(TIMER1_CAPT_vect)  { 				//interrupção por captura do valor do TCNT1

	CPL_BIT(TCCR1B,ICES1);				//troca a borda de captura do sinal
	if(!TST_BIT(TCCR1B,ICES1))			//lê o valor de contagem do TC1 na borda de subida do sinal
		Inicio_Sinal = ICR1;			//salva a primeira contagem para determinar a largura do pulso
	else 								//lê o valor de contagem do TC1 na borda de descida do sinal
		Distancia = ((ICR1 - Inicio_Sinal)/58);	//agora ICR1 tem o valor do TC1 na borda de descida do sinal, então calcula a distância

}


void rc(){

	uint8_t l_spd=120, r_spd=140;

	uint8_t serial_char;

	while(1){

		serial_char = USART_rx();

		if(serial_char == 'X') {
			while(serial_char != 'F') {			//sai da parte autonoma quando o botar de ir pra frente ficar pressionado
				autonomo();
				serial_char = USART_rx();
			}
		}

		// controle de velocidade //

		if (serial_char == '0'){
			r_spd = 0;
			l_spd = 0;

		}
		else if (serial_char == '1'){
			r_spd = 120;
			l_spd = 100;
		}
		else if(serial_char == '2'){
			r_spd = 140;
			l_spd = 120;
		}
		else if(serial_char == '3'){
			r_spd = 160;
			l_spd = 140;
		}
		else if(serial_char == '4'){
			r_spd = 180;
			l_spd = 160;
		}
		else if(serial_char == '5'){
			r_spd = 200;
			l_spd = 180;
		}
		else if(serial_char == '6'){
			r_spd = 220;
			l_spd = 200;
		}
		else if(serial_char == '7'){
			r_spd = 230;
			l_spd = 210;
		}
		else if(serial_char == '8'){
			r_spd = 240;
			l_spd = 220;
		}
		else if(serial_char == '9'){
			r_spd = 250;
			l_spd = 230;
		}
		else if(serial_char == 'q'){
			r_spd = 255;
			l_spd = 235;
		}
		else if (serial_char == 'D')
			para();


		// controle de direcao //

			if (serial_char == 'F' )
				frente(l_spd, r_spd);

			else if(serial_char == 'B')
				reh(r_spd, r_spd);

			else if(serial_char == 'L')
				direita(l_spd, r_spd);

			else if(serial_char == 'R')
				esquerda(l_spd, r_spd);

			else if(serial_char == 'G')
				frente(l_spd*70/100, r_spd);

			else if(serial_char == 'I')
				frente(l_spd, r_spd*70/100);

			else if(serial_char == 'H')
				reh(r_spd*70/100, l_spd);

			else if(serial_char == 'J')
				reh(r_spd, l_spd*70/100);

			else if(serial_char == 'S')
				para();
			else if(serial_char == 'D')
				break;
	}

}


void autonomo(){


	uint8_t sensor_esq = TST_BIT(PINC,SENSOR_E);
	uint8_t sensor_dir = TST_BIT(PINC,SENSOR_D);

	//pulso de disparo
	SET_BIT(PORTB,PB1);
	_delay_us(10);
	CLR_BIT(PORTB,PB1);

	if(Distancia>=60) {

		if(!sensor_esq && !sensor_dir)
			frente(115, 115);

		else if(!sensor_esq && sensor_dir)
			esquerda(145,145);

		else if(sensor_esq && !sensor_dir)
			direita(145,145);

		else if(sensor_esq && sensor_dir)
			para();
	}

	else if (Distancia>=4){
		para();
	}

	_delay_ms(50);	//mínimo tempo para uma nova medida de distância

}
