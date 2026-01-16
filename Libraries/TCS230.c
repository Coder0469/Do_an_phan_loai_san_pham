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
	TCS->index = 0;
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
			HAL_GPIO_WritePin(GPIOE, S2_Pin, RESET);
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
	uint16_t T = icValue - TCS->pre_icValue;
	uint16_t freqValue = 1000000 / T;
	TCS->pre_icValue = icValue;

	if (TCS->colorIndex - 1 == RED)
	{
		TCS->freqRed = freqValue;
//		*TCS->MyRed = freqValue;
		TCS->buffer[RED] += freqValue;
	}
	if (TCS->colorIndex - 1 == GREEN)
	{
		TCS->freqGreen = freqValue;
//		*TCS->MyGreen = freqValue;
		TCS->buffer[GREEN] += freqValue;
	}
	if (TCS->colorIndex + 2 == BLUE)
	{
		TCS->freqBlue = freqValue;
//		*TCS->MyBlue = freqValue;
		TCS->buffer[BLUE] += freqValue;
	}
	if(TCS->index == BUFFERSIZE - 1){
		TCS->buffer_avg[RED] = TCS->buffer[RED] / BUFFERSIZE;
		TCS->buffer_avg[BLUE] = TCS->buffer[BLUE] / BUFFERSIZE;
		TCS->buffer_avg[GREEN] = TCS->buffer[GREEN] / BUFFERSIZE;
		*TCS->MyRed = TCS->buffer_avg[RED];
		*TCS->MyGreen = TCS->buffer_avg[GREEN];
		*TCS->MyBlue = TCS->buffer_avg[BLUE];

		TCS->index = 0;
		TCS->buffer[RED] = 0;
		TCS->buffer[GREEN] = 0;
		TCS->buffer[BLUE] = 0;
	}
	TCS->index++;
	//*TCS->MyOutput = freqValue;
}

void switchColor(TCS_HandleTypeDef *TCS)
{
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

void mapFreqToColor(TCS_HandleTypeDef *TCS)
{
	TCS->rgbRed = (uint16_t)((TCS->freqRed - DARKRED) / (BRIGHTRED - DARKRED)) * 255;
	TCS->rgbGreen = (uint16_t)((TCS->freqGreen - DARKGREEN) / (BRIGHTGREEN - DARKGREEN)) * 255;
	TCS->rgbBlue = (uint16_t)((TCS->freqBlue - DARKBLUE) / (BRIGHTBLUE - DARKBLUE)) * 255;
}

void determineColor(TCS_HandleTypeDef *TCS)
{
//	if (TCS->freqRed < DEFAULTRED && TCS->freqGreen < DEFAULTGREEN && TCS->freqBlue < DEFAULTBLUE)
//	{
//		*TCS->MyOutput = CLEAR;
//		return;
//	}
//	if (TCS->freqRed > TCS->freqGreen && TCS->freqRed > TCS->freqBlue) *TCS->MyOutput = RED;
//	else if (TCS->freqGreen > TCS->freqRed && TCS->freqGreen > TCS->freqBlue) *TCS->MyOutput = GREEN;
//	else if (TCS->freqBlue > TCS->freqGreen && TCS->freqBlue > TCS->freqRed) *TCS->MyOutput = BLUE;
//	else *TCS->MyOutput = CLEAR;

	if (TCS->buffer_avg[RED] > TCS->buffer_avg[GREEN] && TCS->buffer_avg[RED] > TCS->buffer_avg[BLUE]) *TCS->MyOutput = RED;
	else if (TCS->buffer_avg[GREEN] > TCS->buffer_avg[RED] && TCS->buffer_avg[GREEN] > TCS->buffer_avg[BLUE]) *TCS->MyOutput = GREEN;
	else if (TCS->buffer_avg[BLUE] > TCS->buffer_avg[RED] && TCS->buffer_avg[BLUE] > TCS->buffer_avg[GREEN]) *TCS->MyOutput = BLUE;
//	else *TCS->MyOutput = CLEAR;
}

