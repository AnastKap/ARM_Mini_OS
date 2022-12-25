#include "context_switching.h"
#include "../interrupts/interrupt.h"
#include "../peripherals/gpio.h"
#include "../process/process.h"
#include "../memory_management/memory.h"

uint8_t current_process = 0;
struct PCB *PCB_list[TOTAL_NUM_OF_PCB];
struct PCB *current_PCB_ptr;
struct PCB* last_user_process = 0;

void add_to_PCB_list(struct PCB *address,uint32_t next) {
	*(uint32_t *)(PCB_list+next) = (uint32_t) address;

}

void startScheduler(){
	setSystickReload(SCHEDULER_INTERVAL);
	enableSystick();
	last_user_process = 0;

	//we need a pointer to the first process -> manual setting
	//current_PCB_ptr = 0x20003000;
	//passing values to next using uint32_t causes problems
	//add_to_PCB_list(current_PCB_ptr,0);


}

void scheduleNextProcess(){
	//current_PCB_ptr = 0x20004004;
	// If in running in kernel right now
	if(last_user_process == 0){
		current_PCB_ptr = FIRST_PROCESS_PAGE_ADDR + 4;
		last_user_process = current_PCB_ptr;
		return;
	}
	for(uint32_t i = ((uint32_t)last_user_process - 4 +PROCESS_PAGE_SIZE); i < PROCESS_PAGE_MAX_STARTING_ADDR; i += PROCESS_PAGE_SIZE){
		if(*(uint32_t *)i && (((uint32_t)current_PCB_ptr - 4) != i)){
			current_PCB_ptr = i + 4;
			last_user_process = current_PCB_ptr;
			return;
		}
	}
	current_PCB_ptr = FIRST_PROCESS_PAGE_ADDR + 4;
	last_user_process = current_PCB_ptr;
	/*if(current_process<TOTAL_NUM_OF_PCB-1) current_process += 1;
	else current_process = 0;

	current_PCB_ptr = PCB_list[current_process]; //current_PCB_ptr stores the PCB address*/



}

__attribute__ ((naked)) void SysTick_ISR(){
	//current_PCB_ptr = 0x20003000;
	__asm volatile(
		"push {r0} \n"
		"mrs r0, psr \n"
		"push {r0} \n"
		"ldr r0, current_PCB \n"
		"ldr r0, [r0] \n"
		"push {r0} \n"
		"add r0, r0, #4 \n"
		"stmia r0, {r1 - r12, lr} \n"
		"pop {r0} \n"
		"mov r1, r0 \n"
		"pop {r0} \n"
		"str r0, [r1, #56] \n"		// Store psr
		"pop {r0} \n"
		"str r0, [r1] \n"					// Store inital r0
		"mrs r0, msp\n"
		"str r0, [r1, #60] \n"
		"mrs r0, psp\n"
		"str r0, [r1, #64] \n"


		"dsb \n isb \n"
		"current_PCB: .word current_PCB_ptr"
	);

	scheduleNextProcess();
	//if(current_PCB_ptr->state)
	__asm volatile(
		"ldr r0, current_PCB \n"
		"ldr r0, [r0] \n"
		"push {r0} \n"
		"add r0, r0, #4 \n"
		"ldmia r0, {r1 - r12, lr} \n"
		"pop {r0} \n"
		"mov r1, r0 \n"
		"ldr r0, [r1, #56] \n"
		"msr psr, r0 \n"
		"ldr r0, [r1, #60] \n"
		"msr msp, r0 \n"
		"ldr r0, [r1, #64] \n"
		"msr psp, r0 \n"

		"ldr r0, current_PCB \n"
		"ldr r0, [r0] \n"
		"ldr r1, [r0, #4]\n"
		"ldr r0, [r0] \n"


		"dsb \n isb \n"
		"bx lr"
		);
}
