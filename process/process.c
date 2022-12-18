#include "process.h"
#include "../context_switching/context_switching.h"
#include "../memory_management/memory.h"



/*
	This function creates a new process
	The steps followed to create the new process are:
	1) Allocate memory space for the stack of the process
	2) Immitate that a SysTick interrupt has already happened. This means that
*/
__attribute__((naked)) void createNewProcess(void *address){
	// Push everything to the stack
	__asm volatile("push {r0 - r12}");

	// Find an available stack frame where the process gonna live
	__asm volatile(
		"push {r0} \n"
		"push {lr} \n"		// Witout it won't work beacause we have "naked" attribute
	);
	findAvailableProcessPage();	// The result is gonna be stored in r0 (EABI convention)

	// Set to one the proc_state_byte
	__asm volatile(
		""
		//	"mov r1, "
		);

	__asm volatile(
		"pop {lr} \n"			// Witout it won't work beacause we have "naked" attribute
		"pop {r0}"
	);

	// Set stack pointer. The stack must NEVER overlap with a stack of another process
	__asm volatile(
		"mov r1, r0 \n"	// Store address which is stored in r0
		//"add r1, r1, #1 \n"
		//"add r1, r1 , #4 \n"
		"mov r12, lr \n" // Store lr
		"mov r0, #0x4000 \n"
		"movt r0, #0x2000 \n"
		"mrs r3, msp \n"
		"msr msp, r0 \n"
		);

	// Immitate that an interrupt has happened
	__asm volatile(
		"mrs r0, psr \n"
		"mov r2, #0 \n"
		"movt r2, #0x100 \n"
		"orr r0, r0, r2 \n"
		"push {r0} \n"
		"push {r1} \n"
		"mov r0, #0xfff9 \n"
		"movt r0, #0xffff \n"
		"mov lr, r1 \n"
		"push {lr} \n"
		"mov lr, r0 \n"
		"push {r0 - r4} \n"
		//"add sp, sp, #4 \n"
		);

	// Fill the stored register entries of the PCB
	__asm volatile(
		"push {r0} \n"
		"ldr r0, _current_PCB \n"
		"mov r1, r0 \n"
		"add r0, r0, #4 \n"
		"stmia r0, {r1 - r12, lr} \n"
		"pop {r0} \n"
		"str r0, [r1] \n"
		"add r1, r1, #56\n"
		"mrs r0, msp\n"
		//"add r0, r0, #4 \n"
		"str r0, [r1] \n"
		"mrs r0, psp\n"
		"add r1, r1, #4\n"
		"str r0, [r1] \n"
		"_current_PCB: .word 0x20002000"
		);

	__asm volatile(
		"mov lr, r12 \n"
		"msr msp, r3 \n"
		"pop {r0 - r12} \n"
		/*"pop {r0, r5} \n"
		"pop {r1} \n"
		"pop {r0} \n"*/
		"bx lr \n"
		);
}
