# Makefile for STM32F103C6 LED blinking project

# Toolchain definitions
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Compiler, assembler, and linker flags
CFLAGS = -mcpu=cortex-m3 -mthumb -g -O0 -Wall -I.
ASFLAGS = -mcpu=cortex-m3 -mthumb -g
LDFLAGS = -T linkerscript.ld -nostdlib

# Source files
SOURCES = main.c DIO_program.c RCC_program.c STK_program.c
ASM_SOURCES = startup.s
OBJECTS = $(SOURCES:.c=.o) $(ASM_SOURCES:.s=.o)
TARGET = Application

# Default target
all: $(TARGET).elf $(TARGET).bin $(TARGET).hex

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup code
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# Link object files
$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@
	$(SIZE) $@

# Generate binary
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Generate hex
$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# Clean generated files
clean:
	rm -f *.o *.elf *.bin *.hex

# Flash to STM32F103C6 via ST-Link
flash: $(TARGET).bin
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).bin 0x08000000 verify reset exit"

# Phony targets
.PHONY: all clean flash
