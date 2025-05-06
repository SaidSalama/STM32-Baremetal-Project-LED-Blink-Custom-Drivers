#include "DIO_interface.h"
#include "RCC_interface.h"
#include "STK_interface.h"

int main(void)
{
	RCC_Init();
	MSTK_voidInit();
	RCC_PerClock_State(APB2, IOPC_PERIPHERAL, PClock_enable);
	DIO_PinMode(GPIOC, PIN13, OUTPUT_SPEED_10MHZ_PP);
    /* Loop forever */
	while(1)
	{
		  DIO_PinWrite (GPIOC , PIN13  , GPIO_HIGH);
		  MSTK_voidSetBusyWait(4000000);

		  DIO_PinWrite (GPIOC , PIN13  , GPIO_LOW);
		  MSTK_voidSetBusyWait(4000000);
	}
}
