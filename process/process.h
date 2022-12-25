#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define PCB_REGISTERS_STORED		40
/* state takes the following values
 *	0: not started yet
 */
struct PCB{
	//uint32_t stored_registers[PCB_REGISTERS_STORED];
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
	uint32_t lr;
	uint32_t psr;
	uint32_t msp;
	uint32_t psp;

	uint32_t pid;
	uint32_t state;
};


void createNewProcess(void *address);


#endif
