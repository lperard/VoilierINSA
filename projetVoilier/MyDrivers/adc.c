#include "../LLDrivers/inc/stm32f1xx_ll_gpio.h"
#include "../LLDrivers/inc/stm32f1xx_ll_adc.h"

void ADCConf() {
	
	LL_ADC_InitTypeDef adcTypeDef;
	adcTypeDef.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	adcTypeDef.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
	LL_ADC_Init(ADC1, &adcTypeDef);
	
	

	
	
	
	
	//Configuration des pins
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	//PIN PC2 pour la batterie
	LL_GPIO_InitTypeDef initPC2;
	LL_GPIO_StructInit(&initPC2);
	initPC2.Pin = LL_GPIO_PIN_2;
	initPC2.Mode = LL_GPIO_MODE_ALTERNATE;
	initPC2.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOC, &initPC2);
	
	LL_ADC_Enable(ADC1);
}