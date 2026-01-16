/*
 * TCS230.c
 *
 *  Created on: Oct 21, 2025
 *      Author: ACER
 */

#include "TCS230.h"

void TCS230_Init(TCS_HandleTypeDef *TCS, uint16_t *Output)
{
	TCS->MyOutput = Output;

	setScaling(PERCENT_2);
	setTypeColor(CLEAR);

	TCS->pre_icValue = 0;
	TCS->colorIndex = 0;
}

void TCS230_Init2(TCS_HandleTypeDef *TCS, uint16_t *freqRed, uint16_t *freqGreen, uint16_t *freqBlue, uint16_t *Output){
	TCS->MyRed = freqRed;
	TCS->MyGreen = freqGreen;
	TCS->MyBlue = freqBlue;
	TCS->MyOutput = Output;

	setScaling(PERCENT_2);
	setTypeColor(CLEAR);

	TCS->pre_icValue = 0;
	TCS->colorIndex = 0;
}

void setTypeColor(enum COLOR state)
{
	// RED: LL, GREEN: HH, BLUE: LH, CLEAR: HL
	switch (state) {
		case RED:
			HAL_GPIO_WritePin(GPIOE, S2_Pin, RESET);
			HAL_GPIO_WritePin(GPIOE, S3_Pin, RESET);
			break;
		case GREEN:
			HAL_GPIO_WritePin(GPIOE, S2_Pin, SET);
			HAL_GPIO_WritePin(GPIOE, S3_Pin, SET);
			break;
		case BLUE:
			HAL_GPIO_WritePin(GPIOE, S2_Pin, RESET);
			HAL_GPIO_WritePin(GPIOE, S3_Pin, SET);
			break;
		case CLEAR:
			HAL_GPIO_WritePin(GPIOE, S2_Pin, SET);
			HAL_GPIO_WritePin(GPIOE, S3_Pin, RESET);
			break;
	}
}

void setScaling(enum PERCENT state)
{
	// OFF: LL, 2%: LH, 20%: HL, 100%: HH
	switch (state)
	{
		case OFF:
			HAL_GPIO_WritePin(GPIOE, S0_Pin, RESET);
			HAL_GPIO_WritePin(GPIOE, S1_Pin, RESET);
			break;
		case PERCENT_2:
			HAL_GPIO_WritePin(GPIOE, S0_Pin, RESET);
			HAL_GPIO_WritePin(GPIOE, S1_Pin, SET);
			break;
		case PERCENT_20:
			HAL_GPIO_WritePin(GPIOE, S0_Pin, SET);
			HAL_GPIO_WritePin(GPIOE, S1_Pin, RESET);
			break;
		case PERCENT_100:
			HAL_GPIO_WritePin(GPIOE, S0_Pin, SET);
			HAL_GPIO_WritePin(GPIOE, S1_Pin, SET);
			break;
	}
}

void calculateFrequency(TCS_HandleTypeDef *TCS)
{
	uint16_t icValue = __HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1);

	uint16_t T;
	if (icValue >= TCS->pre_icValue)
	{
		T = icValue - TCS->pre_icValue;
	}
	else
	{
		T = (htim1.Instance->ARR - TCS->pre_icValue) + icValue + 1;
	}

	uint16_t freqValue = 1000000 / T;
	TCS->pre_icValue = icValue;

	if (TCS->colorIndex -1 == RED)
	{
		*TCS->MyRed = freqValue;
		TCS->Red = freqValue;
	}
	if (TCS->colorIndex -1 == GREEN)
	{
		*TCS->MyGreen = freqValue;
		TCS->Green = freqValue;
	}
	if (TCS->colorIndex +2 == BLUE)
	{
		*TCS->MyBlue = freqValue;
		TCS->Blue = freqValue;
	}
}

void switchColor(TCS_HandleTypeDef *TCS)
{
//	TCS->colorIndex = (TCS->colorIndex + 1) % 3;
	switch (TCS->colorIndex)
	{
		case 0:
			setTypeColor(RED);
			resetPreValue(TCS);
			break;
		case 1:
			setTypeColor(GREEN);
			resetPreValue(TCS);
			break;
		case 2:
			setTypeColor(BLUE);
			resetPreValue(TCS);
			break;
	}
	TCS->colorIndex = (TCS->colorIndex + 1) % 3;
}

void resetPreValue(TCS_HandleTypeDef *TCS)
{
	TCS->pre_icValue = 0;
}

void determineColor(TCS_HandleTypeDef *TCS)
{

	if(TCS->Red < 120 && TCS->Green < 120 && TCS->Blue < 120) *TCS->MyOutput = CLEAR;
	else if (TCS->Red > TCS->Green && TCS->Red > TCS->Blue) *TCS->MyOutput = RED;
//	else if (TCS->Green > TCS->Red && TCS->Green > TCS->Blue && TCS->Red > 70) *TCS->MyOutput = GREEN;
	else if (TCS->Green > TCS->Red*1.9) *TCS->MyOutput = BLUE;
	else *TCS->MyOutput = GREEN;

}

