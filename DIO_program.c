/*
 * DIO_program.c
 *
 *  Created on: Aug 12, 2020
 *      Author: Said SALAMA
 */


#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"



void DIO_PinMode(u8 port , u8 pin  , u8 mode)		/*For configuration each pin has 4 bits so multiplying by 4 */
{

	switch(port)
	{
	case GPIOA :
		        if(pin <=7)
		        {
		        	GPIOA_CRL &= ~((0X0F) << pin*4)  ; // REST PINS
		        	GPIOA_CRL |= (mode << pin*4 ) ;  // CHOOSE mode

		        }
		        else if(pin <= 15)
		        {
		        	pin = pin - 8;
		        	GPIOA_CRH &= ~((0X0F)  << (pin*4 ) );
		        	GPIOA_CRH |= (mode << (pin*4 ));
		        }

		        break ;
	case GPIOB :
					if(pin <=7)
				        {
				        	GPIOB_CRL &= ~((0X0F)  << pin*4  ); // REST PINS
				        	GPIOB_CRL |= mode << pin*4  ;  // CHOOSE mode

				        }
				        else if(pin <= 15)
				        {
				        	pin = pin - 8;
				        	GPIOB_CRH &= ~((0X0F)  << (pin*4 ) );
				        	GPIOB_CRH |= (mode << (pin*4 ));
				        }

				        break ;


	case GPIOC :
						if(pin <=7)
				        {
				        	GPIOA_CRL &= ~((0X0F)  << pin*4  ); // REST PINS
				        	GPIOA_CRL |= mode << pin*4  ;  // CHOOSE mode

				        }
				        else if(pin <= 15)
				        {
				        	pin = pin - 8;
				        	GPIOC_CRH &= ~((0X0F)  << (pin*4 ) );
				        	GPIOC_CRH |= (mode << (pin*4 ));
				        }

				        break ;




	}

	}

void DIO_PinWrite   (u8 port , u8 pin  , u8 value)
{
	switch(port)
		{
		case GPIOA :

			        if(value == GPIO_LOW)
			        {
			        	CLR_BIT(  GPIOA_ODR  , pin );
			        }
			        else
			        {
						SET_BIT(   GPIOA_ODR   ,  pin );

					}

			        break ;
		case GPIOB :

	        if(value == GPIO_LOW)
	        {
	        	CLR_BIT(  GPIOB_ODR  , pin );
	        }
	        else
	        {
				SET_BIT(   GPIOB_ODR   ,  pin );

			}

	        break ;


		case GPIOC :

	        if(value == GPIO_LOW)
	        {
	        	CLR_BIT(  GPIOC_ODR  , pin );
	        }
	        else
	        {
				SET_BIT(   GPIOC_ODR   ,  pin );

			}

	        break ;




		}
	}
u8   DIO_PinRead      (u8 port , u8 pin )
{
	u8 LOC_u8Result =0;

	switch(port)
	{
	   case GPIOA :  LOC_u8Result = GET_BIT(GPIOA_IDR ,pin );
		             break ;

	   case GPIOB :  LOC_u8Result = GET_BIT(GPIOB_IDR ,pin );
	                 break ;

	   case GPIOC :  LOC_u8Result = GET_BIT(GPIOC_IDR ,pin );
	                 break ;
	}

	return LOC_u8Result ;

}

void DIO_Atomic_Set(u8 port , u8 pin)
{
	switch(port)
	{
		case GPIOA :
			SET_BIT(GPIOA_BSR,pin);
			break;
		case GPIOB:
			SET_BIT(GPIOB_BSR,pin);
			break;
		case GPIOC :
			SET_BIT(GPIOC_BSR,pin);
			break;


	}
}
void DIO_Atomic_Reset(u8 port , u8 pin)
{
	switch(port)
	{
		case GPIOA :
			SET_BIT(GPIOA_BSR,(pin+16));
			break;
		case GPIOB:
			SET_BIT(GPIOB_BSR,(pin+16));
			break;
		case GPIOC :
			SET_BIT(GPIOC_BSR,(pin+16));
			break;


	}
}
