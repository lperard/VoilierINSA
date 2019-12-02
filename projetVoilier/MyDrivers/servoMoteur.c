#include "servoMoteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"

/*
@brief : config TIMER1
@param : none
@return : none
*/
void initServoMoteur (void) {
	
	//start the clock of TIM1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	
	//struct use to config TIM1
	LL_TIM_InitTypeDef TIM1InitStruct;
	
	/*set at 20ms*/
	TIM1InitStruct.Autoreload = 999; 
	TIM1InitStruct.Prescaler= 1439;
	/*************/
	//init the other files
	TIM1InitStruct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM1InitStruct.CounterMode=LL_TIM_COUNTERMODE_UP;
	TIM1InitStruct.RepetitionCounter=0;
	
	//Init the struct
	LL_TIM_Init(TIM1,&TIM1InitStruct);
	
	
	//struct use to config the output mode of the PWM on TIM1
	LL_TIM_OC_InitTypeDef PWMInitStruct;
	
	//init the PWM struct
	LL_TIM_OC_StructInit(&PWMInitStruct);
	
	//set the values of the fields of the PWM structure
	// ((__VALUE__) == LL_TIM_OCMODE_PWM1) 
	PWMInitStruct.OCMode = LL_TIM_OCMODE_PWM1;
	//1ms (value : 50) for the minimum angle and 2ms (value : 100) for the max angle
	//set at 2 ms by default (sail in straight position)
	PWMInitStruct.CompareValue = 100;
	//enable the compare mode
	PWMInitStruct.OCState = LL_TIM_OCSTATE_ENABLE;
	PWMInitStruct.OCNState = LL_TIM_OCSTATE_ENABLE;
	//start TIM1 output mode
	TIM1 -> BDTR |= 0x1 << 15;

	//bind the PWM struct with the timer and the channel
	LL_TIM_OC_Init(TIM1, LL_TIM_CHANNEL_CH1, &PWMInitStruct);
	
	
}


/**
	* @brief : Start servoMoteur service
	* @param : None
	* @retval : None
  */
void enableServoMoteur(void)
{
		LL_TIM_EnableCounter(TIM1);
}

/**
	* @brief : Stop servoMoteur service
	* @param : None
	* @retval : None
  */
void disableServoMoteur(void)
{
		LL_TIM_DisableCounter(TIM1);
}

/*
@brief : set the angle of the sail (0 to 60 degrees)
@param : angle wanted
@return : none
*/

void setSailAngle (int angle) { 
	float coefDirect = (-5./6.);
	float	origin = 100.;
	float compareValue = coefDirect * (float) angle + origin;
	LL_TIM_OC_SetCompareCH1(TIM1,(int) compareValue);
}

void setAngleFromGirouette (int angle) {
	if (angle < 45){
		setSailAngle (0);
	}
	else if (angle < 55){
		setSailAngle (50);
	}
	else if (angle < 75){
		setSailAngle (65);
	}
	else if (angle < 105){
		setSailAngle (90);
	}
	else if (angle < 150){
		setSailAngle (127);
	}
	else if (angle < 45){
		setSailAngle (0);
	}
	else if (angle < 45){
		setSailAngle (0);
	}
	
}






















