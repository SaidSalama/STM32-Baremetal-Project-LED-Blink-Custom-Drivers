/*
 * STK_interface.h
 *
 *  Created on: Aug 21, 2022
 *      Author: Said Salama
 */

#ifndef MCAL_STK_STK_INTERFACE_H_
#define MCAL_STK_STK_INTERFACE_H_

#include "STD_TYPES.h"

void MSTK_voidInit 				  (void);
void MSTK_voidSetBusyWait 		  (u32 Copy_u32Ticks);
void MSTK_voidSetIntervalSingle   (u32 Copy_u32Ticks, void (* Copy_PF)(void));
void MSTK_voidSetIntervalPeriodic (u32 Copy_u32Ticks, void (* Copy_PF)(void));
void MSTK_voidStopInterval        (void);
u32  MSTK_u32GetElapsedTime		  (void);
u32  MSTK_u32GetReamianTime		  (void);

#endif /* MCAL_STK_STK_INTERFACE_H_ */
