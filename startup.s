.syntax unified              // Use unified assembly syntax (compatible with ARM and Thumb)
.cpu cortex-m3              // Target CPU core (STM32F103 uses Cortex-M3)
.fpu softvfp                // Use software floating-point (no hardware FPU)
.thumb                      // Generate Thumb instructions (required for Cortex-M)

.extern _estack             // Stack top symbol from linker script
.extern _sdata              // Start of initialized data in RAM
.extern _edata              // End of initialized data in RAM
.extern _sbss               // Start of uninitialized (BSS) section
.extern _ebss               // End of BSS section

.global Reset_Handler       // Make Reset_Handler globally visible
.global Default_Handler     // Make Default_Handler globally visible

.section .isr_vector, "a", %progbits  // Place vector table in this section, marked as allocatable

.word _estack               // Initial stack pointer (loaded into MSP at reset)
.word Reset_Handler         // Reset vector: address of Reset_Handler
.word NMI_Handler           // Non-maskable interrupt
.word HardFault_Handler     // Hard fault
.word MemManage_Handler     // Memory management fault
.word BusFault_Handler      // Bus fault
.word UsageFault_Handler    // Usage fault
.word 0, 0, 0, 0            // Reserved (4 entries)
.word SVC_Handler           // Supervisor call (SVC)
.word DebugMon_Handler      // Debug monitor
.word 0                     // Reserved
.word PendSV_Handler        // PendSV
.word SysTick_Handler       // SysTick

// Add more IRQ handlers here if needed (e.g., for USART, TIM, etc.)

.section .text              // Begin code section
.type Reset_Handler, %function  // Mark Reset_Handler as a function

Reset_Handler:
  ldr r0, =_sdata           // r0 ← address of start of .data in RAM
  ldr r1, =_edata           // r1 ← address of end of .data in RAM
 // ldr r2, =_etext           // r2 ← address of initialized .data in Flash (source) — optional
  movs r3, #0               // r3 ← 0 (used as a temp register)

copy_data:                  // Copy loop: Flash → RAM
  cmp r0, r1                // Compare current RAM address with end
  ittt lt                   // If r0 < r1 (Less Than), execute next 3 instructions
  ldrlt r3, [r2], #4        // Load word from Flash and increment r2
  strlt r3, [r0], #4        // Store word to RAM and increment r0
  blt copy_data             // Repeat until all .data is copied

  ldr r0, =_sbss            // r0 ← start of .bss
  ldr r1, =_ebss            // r1 ← end of .bss
  movs r2, #0               // r2 ← 0 (zero value)

zero_bss:                   // Loop to zero out .bss
  cmp r0, r1                // Compare current with end
  it lt
  strlt r2, [r0], #4        // If less, store 0 and increment
  blt zero_bss              // Repeat until all of .bss is cleared

  bl main                   // Branch to main() in C

infinite_loop:
  b infinite_loop           // If main returns, stay in infinite loop

/* Default_Handler is a catch-all for any undefined IRQs */
Default_Handler:
  b .                       // Infinite loop (do nothing)

// Weakly define interrupt handlers so user code can override them
.weak NMI_Handler
.weak HardFault_Handler
.weak MemManage_Handler
.weak BusFault_Handler
.weak UsageFault_Handler
.weak SVC_Handler
.weak DebugMon_Handler
.weak PendSV_Handler
.weak SysTick_Handler

// Point all weak handlers to Default_Handler unless overridden
NMI_Handler:         b Default_Handler
HardFault_Handler:   b Default_Handler
MemManage_Handler:   b Default_Handler
BusFault_Handler:    b Default_Handler
UsageFault_Handler:  b Default_Handler
SVC_Handler:         b Default_Handler
DebugMon_Handler:    b Default_Handler
PendSV_Handler:      b Default_Handler
SysTick_Handler:     b Default_Handler
