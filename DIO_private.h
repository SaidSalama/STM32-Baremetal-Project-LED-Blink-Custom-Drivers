/*
 * DIO_private.h
 *
 *  Created on: 05/25
 *      Author: SAID SALAMA
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


            /* REGISTER ADDRESSES FOR PORTA */
#define  GPIOA_CRL             *((u32*)0x40010800 )
#define  GPIOA_CRH             *((u32*)0x40010804 )
#define  GPIOA_IDR             *((u32*)0x40010808 )
#define  GPIOA_ODR             *((u32*)0x4001080C )
#define  GPIOA_BSR             *((u32*)0x40010810 )
#define  GPIOA_BRR             *((u32*)0x40010814 )
#define  GPIOA_LCK             *((u32*)0x40010818 )




               /* REGISTER ADDRESSES FOR PORTB */
							 
#define  GPIOB_CRL             *((u32*)0x40010C00 )
#define  GPIOB_CRH             *((u32*)0x40010C04 )
#define  GPIOB_IDR             *((u32*)0x40010C08 )
#define  GPIOB_ODR             *((u32*)0x40010C0C )
#define  GPIOB_BSR             *((u32*)0x40010C10 )
#define  GPIOB_BRR             *((u32*)0x40010C14 )
#define  GPIOB_LCK             *((u32*)0x40010C18 )




               /* REGISTER ADDRESSES FOR PORTC */
#define  GPIOC_CRL             *((u32*)0x40011000 )
#define  GPIOC_CRH             *((u32*)0x40011004 )
#define  GPIOC_IDR             *((u32*)0x40011008 )
#define  GPIOC_ODR             *((u32*)0x4001100C )
#define  GPIOC_BSR             *((u32*)0x40011010 )
#define  GPIOC_BRR             *((u32*)0x40011014 )
#define  GPIOC_LCK             *((u32*)0x40011018 )

/* modified by ME*/
#define AFIO_BASE_ADD    	    *((u32*)0x40010000)
#define AFIO_EXTICR1  			*((u32*)0x40010008)
#define AFIO_EXTICR4  			*((u32*)0x40010014)
#define AFIO_MAPR  				*((u32*)0x40010004)


#endif /* DIO_PRIVATE_H_ */
