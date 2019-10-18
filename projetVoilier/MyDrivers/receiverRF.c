#include "receiverRF.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"

/*
@brief : config TIMER1
@param : none
@return : none
*/
void init (void) {
	
	//start the clock of TIM1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	
	//struct use to config TIM1
	LL_TIM_InitTypeDef TIM1InitStruct;
	
	/*set at 20ms*/
	TIM1InitStruct.Autoreload = 999; 
	TIM1InitStruct.Prescaler= 359;
	/*************/
	TIM1InitStruct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM1InitStruct.CounterMode=LL_TIM_COUNTERMODE_UP;
	TIM1InitStruct.RepetitionCounter=0;
	
	//Init the struct
	LL_TIM_Init(TIM1,&TIM1InitStruct);
	
	//struct use to config the output mode of the PWM on TIM1
	LL_TIM_OC_InitTypeDef * PWMInitStruct;
	
	//init the PWM struct
	LL_TIM_OC_StructInit(PWMInitStruct);
	
	//change the values of the fields of the PWM structure
	PWMInitStruct -> OCMode = LL_TIM_OCMODE_PWM1;

	//bind the PWM struct with the timer and the channel
	LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, PWMInitStruct);
	
	
	//launch the timer
}