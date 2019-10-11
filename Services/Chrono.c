// A COMPLETER

/*
Service permettant de chornométrer jusqu'à 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 à TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "../LLDrivers/inc/stm32f1xx_ll_gpio.h"
#include "../LLDrivers/inc/stm32f1xx_ll_usart.h"
#include "../LLDrivers/inc/stm32f1xx_ll_bus.h"



// variable privée de type Time qui mémorise la durée mesurée
static Time Chrono_Time; // rem : static rend la visibilité de la variable Chrono_Time limitée à ce fichier 

// variable privée qui mémorise pour le module le timer utilisé par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.

// déclaration callback appelé toute les 10ms
void Chrono_Task_10ms(void);

/**
	* @brief  Configure le chronomètre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Chrono_Conf(TIM_TypeDef * Timer)
{
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);
}

void Chrono_Conf_io() {
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//init LL GPIOC 8
	LL_GPIO_InitTypeDef initGPIO8;
	LL_GPIO_StructInit(&initGPIO8);
	initGPIO8.Pin = LL_GPIO_PIN_8;
	initGPIO8.Mode = LL_GPIO_MODE_FLOATING;
	
	LL_GPIO_Init(GPIOC, &initGPIO8);

	//init LL GPIOC 10
	LL_GPIO_InitTypeDef initGPIO10;
	LL_GPIO_StructInit(&initGPIO10);
	initGPIO10.Pin = LL_GPIO_PIN_10;
	initGPIO10.Mode = LL_GPIO_MODE_OUTPUT;
	initGPIO10.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOC, &initGPIO10);
	
	/* USART */
	
	//LL_USART_ClockInitTypeDef clockStruct;
	//LL_USART_ClockStructInit(&clockStruct);
	//LL_USART_ClockInit(USART2, &clockStruct);
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	LL_USART_InitTypeDef usartTypeDef;
	usartTypeDef.BaudRate = 19200;
	usartTypeDef.DataWidth = LL_USART_DATAWIDTH_8B ;
	usartTypeDef.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	usartTypeDef.Parity = LL_USART_PARITY_NONE;
	usartTypeDef.TransferDirection = LL_USART_DIRECTION_TX;	
	usartTypeDef.StopBits = LL_USART_STOPBITS_1;
	usartTypeDef.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &usartTypeDef);
	
	//config de PA2 et PA3 en alternate function pour l'usart
	
	//Tx
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	LL_GPIO_InitTypeDef initPA2;
	LL_GPIO_StructInit(&initPA2);
	initPA2.Pin = LL_GPIO_PIN_2;
	initPA2.Mode = LL_GPIO_MODE_ALTERNATE;
	initPA2.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &initPA2);
	
	/*
	//Rx
	LL_GPIO_InitTypeDef initPA3;
	LL_GPIO_StructInit(&initPA3);
	initPA3.Pin = LL_GPIO_PIN_3;
	initPA3.Mode = LL_GPIO_MODE_ALTERNATE;
	initPA3.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	LL_GPIO_Init(GPIOA, &initPA3);
	*/
	LL_USART_Enable(USART2);
	// USART2->CR1 |= USART_CR1_TE;
}

void Chrono_Background() {
	int isStartPressed = LL_GPIO_IsInputPinSet (GPIOC, LL_GPIO_PIN_8); 

	if(isStartPressed) {
		LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10);
	} else {
		if(LL_GPIO_IsOutputPinSet(GPIOC, LL_GPIO_PIN_10)) {
			 LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_10);
		}
	}	
	
	/* TODO utiliser BSRR */
}

/**
	* @brief  Démarre le chronomètre. 
  * @note   si la durée dépasse 59mn 59sec 99 Hund, elle est remise à zéro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arrête le chronomètre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronomètre à 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arrêt Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time privée gérée dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}

void send_char(char c){
	while(LL_USART_IsActiveFlag_TXE(USART2) != 1);	
	LL_USART_TransmitData8(USART2, c);
}

/**
	* @brief  incrémente la variable privée Chron_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Task_10ms(void)
{ 
	Chrono_Time.Hund++;
	if (Chrono_Time.Hund==100)
	{
		Chrono_Time.Sec++;
		Chrono_Time.Hund=0;
	}
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Hund=0;
	}
	
	
	send_char('0' + Chrono_Time.Min / 10);
	send_char('0' + Chrono_Time.Min % 10);
	send_char(':');
	send_char('0' + Chrono_Time.Sec / 10);
	send_char('0' + Chrono_Time.Sec % 10);
	send_char(':');
	send_char('0' + Chrono_Time.Hund / 10);
	send_char('0' + Chrono_Time.Hund % 10);
	send_char(13);
	send_char('\0')
	
/*	
	/* USART */
//	while(LL_USART_IsActiveFlag_TXE(USART2) != 1);	
//	LL_USART_TransmitData8(USART2, );
	//while(LL_USART_IsActiveFlag_TC(USART2) != 1); //wait for tc flag 
	
}








