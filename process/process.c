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
		"push {lr} \n"		// Witout it won't work because we have "naked" attribute
	);
	uint32_t proc_addr = findAvailableProcessPage();	// The result is gonna be stored in r0 (EABI convention)
	//uint32_t proc_addr = 0x20002000;

	// Do arithmetic to set stack pointer
	__asm volatile(
		"mov r2, r0 \n"
		"mov r10, r0 \n"
		"add r2, r2, %0 \n"
		"push {r2}"
	: :"i" (PROCESS_PAGE_SIZE));
	//*(uint32_t *) proc_addr = 1; //set first bit -> page is used
	__asm volatile(
		"mov r2, 1 \n"
		"movt r2, 0 \n"
		"stm r0, {r2} \n"
	);

	//current_PCB_ptr = proc_addr + 4;
	__asm volatile(
		"add r0, r0, #4 \n"
		"ldr r2, _current_PCB \n"
		"stm r2, {r0}"
	);


	//add_to_PCB_list((proc_addr+1),1); //next word of page is used for storing PCB
	// Set to one the proc_state_byte
	__asm volatile(
		""
		//	"mov r1, "
		);

	__asm volatile(
		"pop {r2} \n"
		"pop {lr} \n"			// Witout it won't work beacause we have "naked" attribute
		"pop {r0}"
	);

	// Set stack pointer. The stack must NEVER overlap with a stack of another process
	__asm volatile(
		"mov r1, r0 \n"	// Store address which is stored in r0
		//"add r1, r1, #1 \n"
		//"add r1, r1 , #4 \n"
		"mov r12, lr \n" // Store lr
		//"mov r0, #0x4000 \n"
		//"movt r0, #0x2000 \n"
		"mrs r3, msp \n"
		"msr msp, r2 \n"
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
		"mrs r0, psr \n"
		"push {r0} \n"
		"ldr r0, _current_PCB \n"
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
		"_current_PCB: .word current_PCB_ptr"
	);


		//current_PCB_ptr = 0x20003000;
	__asm volatile(
			"mov r0, #0x3000\n"
			"movt r0, #0x2000 \n"
			"ldr r2, _current_PCB \n"
			"stm r2, {r0}"
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


void initPipeSpace(){
	uint32_t ptr = PIPE_STARTING_ADDRESS;
	uint8_t id = 0;
	while(id<PIPE_NUM && ptr<PIPE_SPACE+PIPE_STARTING_ADDRESS){
		used_pipes[id] = 0;
		*(uint8_t *) ptr = id;
		*(uint8_t *) (ptr+1) = 0; //initialize pipe counter to 0
		id++;
		ptr += PIPE_SIZE;
	}
}

//finds the first free pipe space if there is any
int createPipe(){ 
	int free_id = -1;
	for(int i = 0; i<PIPE_NUM; i++){
		if(used_pipes[i] == 0){
			free_id	= i;
			used_pipes[i] = 1;
			return free_id;
		}
	}
	return free_id;
}

int readPipeByte(int pipe_id){ //reads from the end to the start of the pipe
	//chack if pipe id is valid
	if(pipe_id<PIPE_NUM){
		uint32_t pipe = PIPE_STARTING_ADDRESS + pipe_id*PIPE_SIZE;
		uint8_t counter = *(uint8_t *) (pipe+1);
		//check if there is anything to read
		if(counter>0){
			uint8_t value = *(uint8_t *) (pipe+1+counter);
			*(uint8_t *) (pipe+1+counter) = 0;
			(*(uint8_t *) (pipe+1))--;
			return value;
		}
		else return 0; //nothing to read
	}
	else return -1; //invalid pipe id
}


//succesful write -> 1
//no space to write -> 0
//non-existing pipe id -> -1
int writePipeByte(int pipe_id, uint8_t msg){ //works alright
	//write if the pipe id exists
	if(pipe_id<PIPE_NUM){
		uint32_t pipe = PIPE_STARTING_ADDRESS + pipe_id*PIPE_SIZE; //pipe starting location
		uint8_t counter = *(uint8_t *) (pipe+1);
		//write while there is space in the pipe
		if(counter<PIPE_SIZE-2){
			*(uint8_t *) (pipe+2+counter) = msg; //pipe+2+counter: free space start location
			counter++;
			*(uint8_t *) (pipe+1) = (uint8_t) counter; //update counter
			return 1; //succesfull write
		}
		else 
			return 0;	//no space to write
	}
	else 
		return -1; //non-existing pipe id
}


