/*
 * DIO_interface.h
 *
 *  Created on:  05/ 25
 *      Author: SAID SALAMA
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define GPIO_HIGH   1
#define GPIO_LOW   0



          /* GPIO ports*/
#define GPIOA  0
#define GPIOB  1
#define GPIOC  2

       /* GPIO PINS*/

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7
#define PIN8   8
#define PIN9   9
#define PIN10  10
#define PIN11  11
#define PIN12  12
#define PIN13  13
#define PIN14  14


// pin modes



#define INPUT_ANALOG                  0b0000
#define INPUT_FLOATING                0b0100
#define INPUT_PULL_UP_DOWN            0b1000


#define OUTPUT_SPEED_10MHZ_PP         0X01
#define OUTPUT_SPEED_10MHZ_OD         0b0101
#define OUTPUT_SPEED_10MHZ_AFPP       0b1001
#define OUTPUT_SPEED_10MHZ_AFOD       0b1101


#define OUTPUT_SPEED_2MHZ_PP         0b0010
#define OUTPUT_SPEED_2MHZ_OD         0b0110
#define OUTPUT_SPEED_2MHZ_AFPP       0b1010
#define OUTPUT_SPEED_2MHZ_AFOD       0b1110


#define OUTPUT_SPEED_50MHZ_PP         0b0011
#define OUTPUT_SPEED_50MHZ_OD         0b0111
#define OUTPUT_SPEED_50MHZ_AFPP       0b1011
#define OUTPUT_SPEED_50MHZ_AFOD       0X0F



void DIO_PinMode(u8 port , u8 pin  , u8 mode);
void DIO_PinWrite   (u8 port , u8 pin  , u8 value);
u8   DIO_PinRead      (u8 port , u8 pin );





#endif /* DIO_INTERFACE_H_ */
