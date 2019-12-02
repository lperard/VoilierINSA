#include "codeurIncr.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void initTimerCodeur (void) {
	//start clock TIM3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	
	//Initialisation du timer
	LL_TIM_InitTypeDef TIM3Struct;
	TIM3Struct.Autoreload = 0x02D0; //correspond un tour complet (teste de maniere tres precise experimentalement)
	//0 degre du bateau = 0x01B5
	TIM3Struct.Prescaler = 1;
	TIM3Struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM3Struct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM3Struct.RepetitionCounter = 0;	
	LL_TIM_Init(TIM3,&TIM3Struct);
	
	//Initialisation du mode encoder pour les channels A et B
	LL_TIM_ENCODER_InitTypeDef encInit;
	encInit.EncoderMode = LL_TIM_ENCODERMODE_X4_TI12;
	encInit.IC1ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	encInit.IC1Filter = LL_TIM_IC_FILTER_FDIV1;
	encInit.IC1Prescaler = LL_TIM_ICPSC_DIV1;
	encInit.IC1Polarity = LL_TIM_IC_POLARITY_RISING;
	
	encInit.IC2ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	encInit.IC2Filter = LL_TIM_IC_FILTER_FDIV1;
	encInit.IC2Prescaler = LL_TIM_ICPSC_DIV1;
	encInit.IC2Polarity = LL_TIM_IC_POLARITY_RISING;
	
	TIM3-> DIER |= TIM_DIER_CC1IE;
	TIM3-> DIER |= TIM_DIER_CC2IE;
	
	LL_TIM_ENCODER_Init(TIM3, &encInit);
}

int getAngleGirouette(void) {
	return LL_TIM_GetCounter(TIM3) / 2; //0,5 degre par position, conversion CNT -> deg;
}

void waitForGirouette(void) {
	// bloquant, necessite un tour de girouette
	while(!LL_GPIO_IsInputPinSet (GPIOA, LL_GPIO_PIN_5)) {
		LL_TIM_SetCounter(TIM3, RESETVALUE);
	}
}
