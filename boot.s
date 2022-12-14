.cpu cortex-m3
.thumb

.word 0x20005000	// Set stack pointer
.word kernel_start
.rept 52
	.byte 0
.endr
.word SysTick_ISR

.thumb_func
kernel_start:
	cpsie f
	b kernel
