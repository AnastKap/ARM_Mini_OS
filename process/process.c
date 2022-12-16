#include "process.h"
#include "../context_switching/context_switching.h"



__attribute__((naked)) void createNewProcess(void *address){
	//((struct PCB *)(0x20000000))->func_addr = address;
	// Set stack pointer. The stack must NEVER overlap with a stack of another process
	__asm volatile( "mov r1, r0 \n"	// Store address which is stored in r0
				   	"mov r12, lr \n" // Store lr
				   	"mov r0, #0x4000 \n"
				   	"movt r0, #0x2000 \n"
				   	"msr msp, r0 \n");
	
	// Immitate that an interrupt has happened
	__asm volatile( "mrs r0, psr \n"
					"push {r0} \n"
				   	"push {r1} \n"
				   	"mov r0, #0xfff9 \n"
				   	"movt r0, #0xffff \n"
				   	"mov lr, r0 \n"
				   	"push {lr} \n"
				  	"push {r0 - r5} \n");
	
	// Fill the stored register entries of the PCB
	__asm volatile(	"push {r0} \n"
					"ldr r0, _current_PCB \n"
				   	"mov r1, r0 \n"
				   	"add r0, r0, #4 \n"
				   	"stmia r0, {r1 - r12, lr} \n"
					"pop {r0} \n"
				   	"str r0, [r1] \n"
				   	"add r1, r1, #56\n"
				   	"mrs r0, msp\n"
				   	"add r0, r0, #4 \n"
				   	"str r0, [r1] \n"
				   	"mrs r0, psp\n"
				   	"add r1, r1, #4\n"
				   	"str r0, [r1] \n"
					""
				   	""
				   	"_current_PCB: .word 0x20002000");
	
	__asm volatile( "mov lr, r12 \n"
				   	/*"pop {r0, r5} \n"
				   	"pop {r1} \n"
				   	"pop {r0} \n"*/
				   	"bx lr \n");
}