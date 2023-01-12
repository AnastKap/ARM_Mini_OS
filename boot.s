.cpu cortex-m3
.thumb
.syntax unified

.word 0x20001fff	// Set stack pointer
.word kernel_start
.word 0
.word HardFault_ISR
.rept 44
	.byte 0
.endr
.word SysTick_ISR

.thumb_func
kernel_start:
	cpsie f
	bl kernel
	b kernel_start
