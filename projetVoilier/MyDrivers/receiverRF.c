#include "receiverRF.h"
#include "stm32f1xx_ll_bus.h"

/*
@brief : config TIMER1
@param : none
@return : none
*/
void init (void) {
	
	//start the clock of TIM1
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	
}