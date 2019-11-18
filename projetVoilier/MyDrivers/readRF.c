#include "readRF.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_rcc.h"
 // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"

static int a;

void initReadRF (void){
	//start the clock of TIM4
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	//active le timer
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;	
	
	//struct use to config TIM4
	LL_TIM_InitTypeDef TIM4InitStruct;
	
	/*set at 20ms*/
	TIM4InitStruct.Autoreload = 999; 
	TIM4InitStruct.Prescaler= 1439;
	TIM4InitStruct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM4InitStruct.CounterMode=LL_TIM_COUNTERMODE_UP;
	TIM4InitStruct.RepetitionCounter=0;
	
	//Init the struct
	LL_TIM_Init(TIM4,&TIM4InitStruct);
	
	LL_TIM_IC_InitTypeDef typeDefIC1;
	typeDefIC1.ICPolarity = LL_TIM_IC_POLARITY_RISING;
	typeDefIC1.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	typeDefIC1.ICPrescaler = LL_TIM_ICPSC_DIV1;
	typeDefIC1.ICFilter = LL_TIM_IC_FILTER_FDIV1;
	
	LL_TIM_IC_InitTypeDef typeDefIC2;
	typeDefIC2.ICPolarity = LL_TIM_IC_POLARITY_FALLING;
	typeDefIC2.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	typeDefIC2.ICPrescaler = LL_TIM_ICPSC_DIV1;
	typeDefIC2.ICFilter = LL_TIM_IC_FILTER_FDIV1;
	
	LL_TIM_IC_Init(TIM4, LL_TIM_CHANNEL_CH1, &typeDefIC1);
	LL_TIM_IC_Init(TIM4, LL_TIM_CHANNEL_CH1, &typeDefIC2);
	
	// TODO TS : TI1FP1
	// TODO SMS : Reset Mode
	// TODO CC2S : input ?
	
	while(1)
		a = LL_TIM_IC_GetCaptureCH1(TIM4);
}
