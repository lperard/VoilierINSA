#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config

#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

void  SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	

int main(void)
{	
	
	//TODO
	//activer CEN de TIM3 DONE
	//config les pins en input DONE
	//mettre arr a 1080 DONE
	//mettre en place l'index (GPIO classique)
	//SET UP du voilier : faire un tour de girouette au tout debut pour trouver le trou du capteur de l'index
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; //active le gpio
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //active la clock du timer
	
	//Initialisation du timer
	LL_TIM_InitTypeDef TIM3Struct;
	TIM3Struct.Autoreload = 1080; //correponda un tour complet
	TIM3Struct.Prescaler = 1;
	TIM3Struct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM3Struct.CounterMode = LL_TIM_COUNTERMODE_UP;
	TIM3Struct.RepetitionCounter = 0;	
	LL_TIM_Init(TIM3,&TIM3Struct);
	
	LL_TIM_EnableCounter(TIM3); //active le timer
	
	//Initialisation du mode encoder pour les channels A et B
	LL_TIM_ENCODER_InitTypeDef encInit;
	encInit.EncoderMode = LL_TIM_ENCODERMODE_X4_TI12;
	encInit.IC1ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	encInit.IC1Filter = LL_TIM_IC_FILTER_FDIV1;
	encInit.IC1Prescaler = LL_TIM_ICPSC_DIV1;
	encInit.IC1Polarity = LL_TIM_IC_POLARITY_RISING;
	
	encInit.IC2ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	encInit.IC2Filter = LL_TIM_IC_FILTER_FDIV1;
	encInit.IC2Prescaler = LL_TIM_ICPSC_DIV1;
	encInit.IC2Polarity = LL_TIM_IC_POLARITY_RISING;
	
	LL_TIM_ENCODER_Init(TIM3, &encInit);
	
  /* Infinite loop */
  while (1) {
		int indexPass = LL_GPIO_IsInputPinSet (GPIOC, LL_GPIO_PIN_8);
		if(!indexPass) {
			LL_TIM_SetCounter(TIM3, 0);
		}
	}
}
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Enable HSE oscillator */
	// ********* Commenter la ligne ci-dessous pour MCBSTM32 *****************
	// ********* Conserver la ligne si Nucléo*********************************
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 72MHz */
  LL_Init1msTick(72000000); // utile lorsqu'on utilise la fonction LL_mDelay

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(72000000);
}



/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
