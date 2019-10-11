// TOUT A FAIRE !! //

/*
 indispensable pour pouvoir adresser les registres des périphériques.
 Rem : OBLIGATION d'utiliser les définitions utiles contenues dans ce fichier (ex : TIM_CR1_CEN, RCC_APB1ENR_TIM2EN ...)
 pour une meilleure lisibilité du code.

 Pour les masques, utiliser également les définitions proposée
 Rappel : pour mettre à 1  , reg = reg | Mask (ou Mask est le représente le ou les bits à positionner à 1)
				  pour mettre à 0  , reg = reg&~ Mask (ou Mask est le représente le ou les bits à positionner à 0)
 
*/ 
#include "stm32f103xb.h" 

static void (*IT_Callback) (void);


void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc)
{
	if(Timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	if(Timer == TIM2){
		RCC->APB1ENR = RCC_APB1ENR_TIM2EN;
	}
	if(Timer == TIM3){
		RCC->APB1ENR = RCC_APB1ENR_TIM3EN;
	}
	if(Timer == TIM4){
		RCC->APB1ENR = RCC_APB1ENR_TIM4EN;
	}		
	Timer->ARR = Arr;	
	Timer ->PSC = Psc;
}

void MyTimer_Start(TIM_TypeDef * Timer)
{
	Timer->CR1 |= TIM_CR1_CEN;
}

void MyTimer_Stop(TIM_TypeDef * Timer)
{
	Timer->CR1 &= ~TIM_CR1_CEN;
}

void MyTimer_IT_Enable(TIM_TypeDef * Timer)
{
	Timer->DIER |= TIM_DIER_UIE;
}

void MyTimer_IT_Disable(TIM_TypeDef * Timer)
{
	Timer->DIER &= ~TIM_DIER_UIE;
}

void MyTimer_IT_Conf(TIM_TypeDef * Timer, void (*IT_function) (void),int Prio)
{
	if (Timer == TIM1){
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, Prio);
	}
	if (Timer == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
	}
	if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
	}
	if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
	}
	MyTimer_IT_Enable(Timer);
	IT_Callback = IT_function;
}

void TIM1_UP_IRQHandler(void)
{
		IT_Callback();
}

void TIM2_IRQHandler(void)
{
		IT_Callback();
}

void TIM3_IRQHandler(void)
{
		IT_Callback();
}

void TIM4_IRQHandler(void)
{
		IT_Callback();
}