#include "GPIOConf.h"
#include "../LLDrivers/inc/stm32f1xx_ll_gpio.h"

void GPIOConfig(void) {

	//enable gpio clock
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//gpio conf for pwm servo moteur
	LL_GPIO_InitTypeDef initGPIOA8;
	LL_GPIO_StructInit(&initGPIOA8);
	initGPIOA8.Pin = LL_GPIO_PIN_8;
	initGPIOA8.Mode = LL_GPIO_MODE_ALTERNATE;
	initGPIOA8.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOA, &initGPIOA8);
	
}
