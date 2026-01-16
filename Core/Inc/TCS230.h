/*
 * TCS230.h
 *
 *  Created on: Oct 21, 2025
 *      Author: ACER
 */

#ifndef INC_TCS230_H_
#define INC_TCS230_H_

#include "main.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"

#define DARKRED 30
#define DARKGREEN 30
#define DARKBLUE 30
#define BRIGHTRED 14000
#define BRIGHTGREEN 14000
#define BRIGHTBLUE 14000

#define DEFAULTRED 0
#define DEFAULTGREEN 0
#define DEFAULTBLUE 0



enum COLOR { RED, GREEN, BLUE, CLEAR };
enum PERCENT { OFF ,PERCENT_2, PERCENT_20, PERCENT_100 };

extern TIM_HandleTypeDef htim1;

typedef struct {
	volatile uint16_t pre_icValue;
	volatile uint8_t colorIndex;

	uint16_t Red;
	uint16_t Green;
	uint16_t Blue;

	uint16_t *MyOutput;
	uint16_t *MyRed;
	uint16_t *MyGreen;
	uint16_t *MyBlue;

}TCS_HandleTypeDef;

void TCS230_Init(TCS_HandleTypeDef *TCS, uint16_t *Output);
void TCS230_Init2(TCS_HandleTypeDef *TCS, uint16_t *freqRed, uint16_t *freqGreen, uint16_t *freqBlue, uint16_t *Output);

void setTypeColor(enum COLOR);
void setScaling(enum PERCENT);

void calculateFrequency(TCS_HandleTypeDef *TCS);

void switchColor(TCS_HandleTypeDef *TCS);
void resetPreValue(TCS_HandleTypeDef *TCS);

void determineColor(TCS_HandleTypeDef *TCS);

#endif /* INC_TCS230_H_ */
