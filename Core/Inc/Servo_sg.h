/*
 * Servo_sg.h
 *
 *  Created on: Nov 5, 2025
 *      Author: ACER
 */

#ifndef INC_SERVO_SG_H_
#define INC_SERVO_SG_H_

#include "main.h"

#define pulsemin 500
#define pulsemax 2500

typedef enum {Servo1, Servo2, Servo3} Servo;

void Servo_Init(void);
void Servo_Run_HALDelay(uint8_t servo_number , float angle , float delay_s );
void Servo_Run(uint8_t servo_number , float angle);

#endif /* INC_SERVO_SG_H_ */
