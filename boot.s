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
.rept 112
	.byte 0
.endr
.word TIM2_ISR
.word TIM3_ISR
.word TIM4_ISR
.rept 19
	.word 0
.endr
.word TIM5_ISR

.thumb_func
kernel_start:
	cpsie i
	cpsie f
	bl kernel
	b kernel_start
