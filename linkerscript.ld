/* Linker script for STM32F103C6 */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 32K
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 10K
}

ENTRY(Reset_Handler)

SECTIONS
{
  /* Vector table and code */
  .text :
  {
    KEEP(*(.isr_vector))      /* Interrupt vectors */
    *(.text*)                 /* Application code */
    *(.rodata*)               /* Read-only data */
    *(.glue_7) *(.glue_7t)    /* ARM glue code */
    *(.eh_frame)
  } > FLASH

  /* Initialized data (copied from FLASH to RAM) */
  .data : 
  {
    _sdata = .;               /* Start of .data in RAM */
    *(.data*)
    _edata = .;               /* End of .data */
  } > RAM AT > FLASH

  /* Uninitialized data (zeroed in RAM) */
  .bss :
  {
    _sbss = .;                /* Start of .bss */
    *(.bss*)
    *(COMMON)
    _ebss = .;                /* End of .bss */
  } > RAM

  /* Stack section (1 KB from end of RAM) */
  .stack (COPY):
  {
    . = ALIGN(8);
    _stack_start = .;
    . = . + 0x400;            /* 1 KB stack */
    _stack_end = .;
  } > RAM

  /* Heap section (remaining RAM, optional) */
  .heap (COPY):
  {
    _heap_start = .;
    . = . + 0x400;            /* 1 KB heap */
    _heap_end = .;
  } > RAM

  /* Symbols used in startup code */
  PROVIDE(_estack = ORIGIN(RAM) + LENGTH(RAM));
}
