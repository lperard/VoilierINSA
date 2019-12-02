#include "readRF.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_rcc.h"
 // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"

void initReadRF (void){
	/* activation de TIM4 */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);	
	
	/* Configuration du timer pour une frequence de 20ms */
	LL_TIM_InitTypeDef TIM4InitStruct;
	TIM4InitStruct.Autoreload = 0xFFFF; 
	TIM4InitStruct.Prescaler = 719;
	TIM4InitStruct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM4InitStruct.CounterMode=LL_TIM_COUNTERMODE_UP;
	TIM4InitStruct.RepetitionCounter=0;
	LL_TIM_Init(TIM4,&TIM4InitStruct);

	/* Initialisation de IC1 et IC2*/
	LL_TIM_IC_InitTypeDef typeDefIC1;
	typeDefIC1.ICPolarity = LL_TIM_IC_POLARITY_RISING;
	typeDefIC1.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	typeDefIC1.ICPrescaler = LL_TIM_ICPSC_DIV1;
	typeDefIC1.ICFilter = LL_TIM_IC_FILTER_FDIV1;

	LL_TIM_IC_InitTypeDef typeDefIC2;
	typeDefIC2.ICPolarity = LL_TIM_IC_POLARITY_FALLING;
	typeDefIC2.ICActiveInput = LL_TIM_ACTIVEINPUT_INDIRECTTI;
	typeDefIC2.ICPrescaler = LL_TIM_ICPSC_DIV1;
	typeDefIC2.ICFilter = LL_TIM_IC_FILTER_FDIV1;
	
	LL_TIM_IC_Init(TIM4, LL_TIM_CHANNEL_CH1, &typeDefIC1);
	LL_TIM_IC_Init(TIM4, LL_TIM_CHANNEL_CH2, &typeDefIC2);
	
	/* Trigger Selection */
	LL_TIM_SetTriggerInput(TIM4,LL_TIM_TS_TI1FP1);
	
	/* Slave mode */
	LL_TIM_SetSlaveMode(TIM4, LL_TIM_SLAVEMODE_RESET);
	
	/* Active les interruptions */
	TIM4-> DIER |= TIM_DIER_CC1IE;
	TIM4-> DIER |= TIM_DIER_CC2IE;
	LL_TIM_EnableIT_UPDATE(TIM4);
	
	/* Active le timer */
	LL_TIM_EnableCounter(TIM4);
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;	
	TIM4->CR1 |= TIM_CR1_CEN;
}

float readRemote() {
	int remoteMin = 0x60;
	int remoteMax = 0xB0;
	return (TIM4->CCR2 - remoteMin) / ((remoteMax - remoteMin) * 1.0);
}
