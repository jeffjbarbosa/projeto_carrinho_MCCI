/*
 * motor.h
 *
 *  Created on: 22 de out de 2019
 *      Author: jefferson
 */

#ifndef LIB_MOTOR_H_
#define LIB_MOTOR_H_

void set_dutty(uint8_t dutty);

void timer0_pwm_hardware_init();

void timer2_pwm_hardware_init();

#endif /* LIB_MOTOR_H_ */
