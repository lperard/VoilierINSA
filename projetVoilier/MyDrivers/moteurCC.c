#include "moteurCC.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void initMoteurCC (void){
	
	//start the clock of TIM2
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	
	/*****Init TIM2*****/
	//struct use to config TIM2
	LL_TIM_InitTypeDef TIM2InitStruct;
	
	/*set at 10kH = 100 micorS*/
	TIM2InitStruct.Autoreload = 49; 
	TIM2InitStruct.Prescaler= 143;
	/*************/
	//init the other files
	TIM2InitStruct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM2InitStruct.CounterMode=LL_TIM_COUNTERMODE_UP;
	TIM2InitStruct.RepetitionCounter=0;
	/********************/
	
	/*****Init PWM*****/
	//Init the struct
	LL_TIM_Init(TIM1,&TIM2InitStruct);
	
	
	//struct use to config the output mode of the PWM on TIM1
	LL_TIM_OC_InitTypeDef PWMInitStruct;
	
	//init the PWM struct
	LL_TIM_OC_StructInit(&PWMInitStruct);
	
	//set the values of the fields of the PWM structure
	// ((__VALUE__) == LL_TIM_OCMODE_PWM1) 
	PWMInitStruct.OCMode = LL_TIM_OCMODE_PWM1;
	//speed min : 0 and speed max : 49
	//set at 0 by default (no speed)
	PWMInitStruct.CompareValue = 0;
	//enable the compare mode
	PWMInitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
	PWMInitStruct.OCNState = LL_TIM_OCSTATE_ENABLE;

	//bind the PWM struct with the timer and the channel
	LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH2, &PWMInitStruct);
	/********************/
	
	
}

void enableMoteurCC(void){
	LL_TIM_EnableCounter(TIM2);
}

void disableMoteurCC(void) {
	LL_TIM_DisableCounter(TIM2);
}

//speed between 0 and 100 %
void setBoardSpeed (int relativeSpeed) {
	int compareValue = (relativeSpeed / 2) - 1;
	LL_TIM_OC_SetCompareCH2(TIM2, compareValue);
}

/* -1 = left and 1 = right */
void setBoardOrientation (int orientation) {
	if (orientation == -1) {
		LL_GPIO_ResetOutputPin(GPIOA,LL_GPIO_PIN_2);
	}
	if (orientation == 1) {
		LL_GPIO_SetOutputPin(GPIOA,LL_GPIO_PIN_2);
	}
}

//speed between 0 and 100 %
// -1 = left and 1 = right
void navigate (int speed, int orientation) {
	setBoardSpeed (speed);
	setBoardOrientation(orientation);
}	














