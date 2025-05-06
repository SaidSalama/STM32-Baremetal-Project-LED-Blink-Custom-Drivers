# STM32-Baremetal-Project-LED-Blink-Custom-Drivers
This is a bare-metal embedded project for the STM32F103C8T6 (Blue Pill) board. The goal isn't just to blink an LED — it's to learn how embedded systems work at the lowest level by writing everything from scratch: startup code, linker script, Makefile, and hardware drivers (RCC, SysTick, GPIO).
STM32 Baremetal Project – LED Blink + Custom Drivers
====================================================
## Project Goals
-------------
- No HAL or STM32Cube libraries
- Manual control over hardware registers
- Write reusable drivers (RCC, SysTick, DIO)
- Understand Cortex-M startup flow
- Build system using Makefile
- Explore linker scripts and memory mapping

### Development Environment
------------------------
- MCU: STM32F103C8T6 (ARM Cortex-M3)
- Toolchain: arm-none-eabi-gcc
- Host OS: Linux (Ubuntu)
- Flashing tool: st-flash (from stlink)

### Project Structure
-----------------
main.c                     -> Application entry point  
startup.s                  -> Assembly startup code and vector table  
linkerscript.ld            -> Custom linker script  
makefile                   -> Makefile for building the project  
makefile_explanation.txt   -> Comments & notes on how the Makefile works  
BIT_MATH.h / STD_TYPES.h   -> Utility headers  

DIO_interface.h  
DIO_private.h  
DIO_program.c  

RCC_interface.h  
RCC_private.h  
RCC_configuration.h  
RCC_program.c  

STK_interface.h  
STK_private.h  
STK_configuration.h  
STK_program.c  

### Build & Flash Instructions
--------------------------
1. Clone the repo:
   git clone 
   cd 

2. Build the binary:
   make

3. Flash to the board:
   st-flash write main.bin 0x8000000

### Implemented Drivers
-------------------
- RCC:
  Enables peripheral clocks, configures system clock

- SysTick:
  Provides delay functionality using ARM SysTick timer

- DIO:
  Controls GPIO pins, blinks LED on PC13

### Driver Structure
----------------
Each driver is modular and follows this pattern:
- *_interface.h: Public API
- *_private.h: Internal macros and base addresses
- *_configuration.h: User-defined settings
- *_program.c: Implementation

### Key Concepts Demonstrated
--------------------------
- Cortex-M startup flow: vector table → reset → main
- Writing reusable hardware abstraction drivers
- Makefile-based build system
- Custom linker scripts and memory mapping
- Register-level peripheral control

### Note:
-----
This project is intended for learning and educational purposes for anyone interested in true bare-metal embedded development on ARM Cortex-M microcontrollers.
