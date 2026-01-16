/*
 * Servo_sg.c
 *
 *  Created on: Nov 5, 2025
 *      Author: ACER
 */

#include "Servo_sg.h"
extern TIM_HandleTypeDef htim2;


typedef struct{
	uint32_t channel;
}Servoconfig;

// Servo 1–3 use 3 channel cung 1 timer

static Servoconfig servos[3]={
		{TIM_CHANNEL_1}, //PA8
		{TIM_CHANNEL_2}, //PE11
		{TIM_CHANNEL_3} //PE13
};

// =====HAM TAO XUNG CHO SERVO ============

static void Servo_SetAngle(uint32_t Channel , float angle )
{
	if(angle < 0 ) angle =0;
	if(angle >180 ) angle = 180;
	float pulse = pulsemin + (angle / 180.0f)* (pulsemax - pulsemin);
	__HAL_TIM_SET_COMPARE(&htim2, Channel, (uint32_t)pulse);

}

// ===========Khoi tao servo=========
void Servo_Init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

}

//======Ham control servo co HAL_Delay ==========

void Servo_Run_HALDelay(uint8_t servo_number , float angle , float delay_s)
{
	if (servo_number < 1 || servo_number > 3) return;

	Servo_SetAngle(servos[servo_number - 1].channel, angle);
	HAL_Delay((uint32_t)(delay_s * 1000));
}
//======Ham control servo use gettick() ==========
void Servo_Run(uint8_t servo_number , float angle)
{
	if (servo_number < 1 || servo_number > 3) return;

	Servo_SetAngle(servos[servo_number - 1].channel, angle);
}
