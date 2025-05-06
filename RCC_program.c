#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_configuration.h"

#define HSI 0
#define HSE 1
#define PLL 2

void RCC_Init(void)
{
#if CLK_SOURCE == HSI
	// Turn on HSI
	RCC_ClkEnable(HSI);
	// Check HSI Ready
	while (RCC_CheckClockReady(HSI) == NOT_READY);
	// Set Buses Prescaler
	RCC_SetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSI Clock
	RCC_SetClkSource(HSI);
	// Turn off HSE and PLL
	RCC_ClkDisable(HSE);
	RCC_ClkDisable(PLL);
#elif CLK_SOURCE == HSE
	// Turn on HSE
	RCC_ClkEnable(HSE);
	// Check HSE Ready
	while (RCC_CheckClockReady(HSE) == NOT_READY)
		;
	// Set Buses Prescaler
	RCC_SetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSE Clock
	RCC_SetClkSource(HSE);
	// Turn off HSE and PLL
	RCC_ClkDisable(HSI);
	RCC_ClkDisable(PLL);

#elif CLK_SOURCE == PLL
	#if PLL_SOURCE == HSE
		RCC_SetPLLSource(PLL_SOURCE, PLL_HSE_FACTOR);
		// Turn on HSE
		RCC_ClkEnable(HSE);
		// Check HSE Ready
		while (RCC_CheckClockReady(HSE) == NOT_READY);
		RCC_ClkDisable(HSI);
	#elif PLL_SOURCE == HSI
		RCC_SetPLLSource(PLL_SOURCE, HSE_NOT_DIVIDED);
		// Turn on HSE
		RCC_ClkEnable(HSI);
		// Check HSE Ready
		while (RCC_CheckClockReady(HSI) == NOT_READY);
		RCC_ClkDisable(HSE);
	#else
		#error Wrong PLL Configurations
	#endif
		// Set Pll Multiplication Factor
		RCC_SetPLLMulFactor(PLL_MULTIPLICATION_FACTOR);
		// Set Buses Prescaler
		RCC_SetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
		// Turn on PLL
		RCC_ClkEnable(PLL);
		// Check PLL Ready
		while (RCC_CheckClockReady(PLL) == NOT_READY);
		// Switch to PLL Clock
		RCC_SetClkSource(PLL);


#else
#error CLOCK Source isn not configured in the right way
#endif

}

void RCC_PerClock_State(Buses_t bus ,u8  peripheral ,PClock_State_t state )
{
	  switch (bus) {
	        case AHB  :
	        	if(state == PClock_enable)
	        	{
	        		SET_BIT (RCC->AHBENR  , peripheral );
	        	}
	        	else if(state == PClock_disable)
	        	{
		        	CLR_BIT (RCC->AHBENR  , peripheral );

	        	}
	        	break;
	        case APB1 :
	        	if(state == PClock_enable)
	        	{
	        		SET_BIT (RCC->APB1ENR  , peripheral );
	        	}
	        	else if(state == PClock_disable)
	        	{
	        		CLR_BIT (RCC->APB1ENR  , peripheral );
	        	}
	        	break;
	        case APB2 :
	        	if(state == PClock_enable)
	        	{
	        		SET_BIT (RCC->APB2ENR  , peripheral );
	        	}
	        	else if(state == PClock_disable)
	        	{
	        		CLR_BIT (RCC->APB2ENR  , peripheral );
	        	}
	        	break;

	        default       : break;
	      }
}

void RCC_SetPLLMulFactor(u8 MulFactor)
{
	RCC->CFGR &= ~(MULTIPLICATION_FACTOR_RESET_MASK);
	RCC->CFGR |= (MulFactor << PLL_MUL_FBIT);
}

/* A_u8ClkSource : HSI  -  HSE */
/* A_u8Prescaler : HSE_NOT_DIVIDED  -  HSE_DIVIDED*/

void RCC_SetPLLSource(u8 ClkSource, u8 Prescaler)
{
	switch (ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, PLLSRC_BIT);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, PLLSRC_BIT);
		switch (Prescaler)
		{
		case HSE_NOT_DIVIDED:
			CLR_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		case HSE_DIVIDED:
			SET_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		default:
			break;
		}
		break;
	}
}

void RCC_ClkEnable(u8 ClkSource)
{
	switch (ClkSource)
	{
	case HSI:
		SET_BIT(RCC->CR, HSI_ON_BIT);
		break;
	case HSE:
		SET_BIT(RCC->CR, HSE_ON_BIT);
		break;
	case PLL:
		SET_BIT(RCC->CR, PLL_ON_BIT);
		break;
	}
}

void RCC_ClkDisable(u8 ClkSource)
{
	switch (ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CR, HSI_ON_BIT);
		break;
	case HSE:
		CLR_BIT(RCC->CR, HSE_ON_BIT);
		break;
	case PLL:
		CLR_BIT(RCC->CR, PLL_ON_BIT);
		break;
	}
}

u8 RCC_CheckClockReady(u8 ClkSource)
{
	u8 local_u8ReadyFlag = 0;
	switch (ClkSource)
	{
	case HSI:
		local_u8ReadyFlag = GET_BIT(RCC->CR, HSI_RDY_BIT);
		break;
	case HSE:
		local_u8ReadyFlag = GET_BIT(RCC->CR, HSE_RDY_BIT);
		break;
	case PLL:
		local_u8ReadyFlag = GET_BIT(RCC->CR, PLL_RDY_BIT);
		break;
	}
	return local_u8ReadyFlag;
}

void RCC_SetClkSource(u8 ClkSource)
{
	switch (ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case PLL:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	}
}

void RCC_SetBusesPrescaler(u8 AHBPrescaler, u8 APB1Prescaler, u8 APB2Prescaler)
{
	RCC->CFGR &= ~(BUSES_PRESCALER_RESET_MASK << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (AHBPrescaler << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (APB1Prescaler << APB1_PRESCALER_FBIT);
	RCC->CFGR |= (APB2Prescaler << APB2_PRESCALER_FBIT);
}
