/*
 * main.c
 *
 *  Created on: 22 de out de 2019
 *      Autores: jefferson e Marcelo
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motor.h"
#include "controle.h"


int main(){

	robo_init();

	rc();

}
