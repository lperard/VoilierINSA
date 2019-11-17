#include "GPIOConf.h"
#include "../LLDrivers/inc/stm32f1xx_ll_gpio.h"

void GPIOConfig(void) {

	//enable gpio clock
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
}
