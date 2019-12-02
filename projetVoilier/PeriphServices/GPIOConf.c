#include "GPIOConf.h"
#include "../LLDrivers/inc/stm32f1xx_ll_gpio.h"

void GPIOConfig(void) {

	//enable gpio clock
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//gpio conf for pwm servo moteur
	LL_GPIO_InitTypeDef initGPIOA8;
	LL_GPIO_StructInit(&initGPIOA8);
	initGPIOA8.Pin = LL_GPIO_PIN_8;
	initGPIOA8.Mode = LL_GPIO_MODE_ALTERNATE;
	initGPIOA8.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &initGPIOA8);
	
	//gpio conf for pwm moteur cc
	LL_GPIO_InitTypeDef initGPIOA1;
	LL_GPIO_StructInit(&initGPIOA1);
	initGPIOA8.Pin = LL_GPIO_PIN_1;
	initGPIOA8.Mode = LL_GPIO_MODE_ALTERNATE;
	initGPIOA8.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &initGPIOA1);
	
	//gpio conf for sens moteur cc
	LL_GPIO_InitTypeDef initGPIOA2;
	LL_GPIO_StructInit(&initGPIOA2);
	initGPIOA8.Pin = LL_GPIO_PIN_2;
	initGPIOA8.Mode = LL_GPIO_MODE_OUTPUT;
	initGPIOA8.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &initGPIOA2);
}
