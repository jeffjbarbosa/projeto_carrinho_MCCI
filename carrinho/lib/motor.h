/*
 * motor.h
 *
 *  Created on: 7 de out de 2019
 *      Author: Marcelo
 */

#ifndef MOTOR_H_
#define MOTOR_H_

void timer_pwm_init();

void frente(uint8_t dutty_esq, uint8_t dutty_dir);

void reh(uint8_t dutty_esq, uint8_t dutty_dir);

void direita(uint8_t dutty_esq, uint8_t dutty_dir);

void esquerda(uint8_t dutty_esq, uint8_t dutty_dir);

void stop();

#endif /* MOTOR_H_ */
