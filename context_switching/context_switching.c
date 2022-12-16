#include "context_switching.h"
#include "../interrupts/interrupt.h"
#include "../peripherals/gpio.h"
#include "../process/process.h"

struct PCB *current_PCB_ptr;
uint8_t current_process = 0;


void startScheduler(){
	setSystickReload(SCHEDULER_INTERVAL);
	enableSystick();
	current_PCB_ptr = 0x20002000;
	current_PCB_ptr = 0x20003000;
	current_process = 0;
	//attachHandler((uint32_t *) 0x3c, SysTick_ISR);
}

void scheduleNextProcess(){
	if(current_process == 0){
		current_process = 1;
		current_PCB_ptr = 0x20002000;
	}
	else{
		current_process = 1;
		current_PCB_ptr = 0x20003000;
	}
}


#define CURRENT_PCB_HIGH		(uint32_t)&current_PCB_ptr >> 16
#define CURRENT_PCB_LOW			(uint32_t)&current_PCB_ptr & 0X0000ffff


__attribute__ ((naked)) void SysTick_ISR(){
	//current_PCB_ptr = 0x20004980;
	__asm volatile(	"push {r0} \n"
					"ldr r0, current_PCB \n"
					"ldr r0, [r0] \n"
				   	"mov r1, r0 \n"
				   	"add r0, r0, #4 \n"
				   	"stmia r0, {r1 - r12, lr} \n"
					"pop {r0} \n"
				   	"str r0, [r1] \n"
				   	"add r1, r1, #56\n"
				   	"mrs r0, msp\n"
				   	"str r0, [r1] \n"
				   	"mrs r0, psp\n"
				   	"add r1, r1, #4\n"
				   	"str r0, [r1] \n"
					""
				   	""
				   	"current_PCB: .word current_PCB_ptr");
	
	scheduleNextProcess();
	//if(current_PCB_ptr->state)
		__asm volatile(	"ldr r0, current_PCB \n"
						"ldr r0, [r0] \n"
						"push {r0} \n"
						"add r0, r0, #4 \n"
						"ldmia r0, {r1 - r12, lr} \n"
						"pop {r0} \n"
					   	"mov r1, r0 \n"
						"add r1, r1, #56 \n"
						"ldr r0, [r1] \n"
						"msr msp, r0 \n"
						"add r1, r1, #4 \n"
						"ldr r0, [r1] \n"
						"msr psp, r0 \n"
						""
						""
						"bx lr");
	//else{
		//current_PCB_ptr->func_addr();
		/*__asm volatile(	"add sp, sp, #0x18 \n"
					   	"str %0, [sp]"
					   	"current_PCB_func_addr_ptr: .word %[func_addr]"
						: :[func_addr] "i" (&current_PCB_ptr->func_addr));*/
	//}
}