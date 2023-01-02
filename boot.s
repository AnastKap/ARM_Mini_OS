.cpu cortex-m3
.thumb
.syntax unified

.word 0x20002000	// Set stack pointer
.word kernel_start
.word 0
.word HardFault_ISR
.rept 44
	.byte 0
.endr
.word SysTick_ISR
.word 0   //sorry taso, einai asxhmo to kserw
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word TIM2_ISR //TIM2_ISR must be located at 0x0000_00B0

.thumb_func
kernel_start:
	cpsie f
	b kernel


.thumb_func
/*SysTick_ISR:
	push {r0}
	ldr r0, current_PCB
	ldr r0, [r0]
	mov r1, r0
	add r0, r0, #4
	stmia r0, {r1 - r12, lr}
	pop {r0}
	str r0, [r1]
	add r1, r1, #56 //14*4
	mrs r0, msp
	str r0, [r1]
	mrs r0, psp
	add r1, r1, #4
	str r0, [r1]

	bl scheduleNextProcess

	add sp, sp, #0x18
	str process2, [sp]
	sub sp, sp, #0x18

	ldr r0, current_PCB
	ldr r0, [r0]
	mov r1, r0
	add r0, r0, #4
	ldmia r0, {r1 - r12, lr}
	ldr r0, [r1]
	add r1, r1, #56
	ldr r0, [r1]
	msr msp, r0
	add r1, r1, #4
	ldr r0, [r1]
	msr psp, r0

	bx lr

current_PCB: .word current_PCB_ptr */
