#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define PCB_REGISTERS_STORED		40
/* state takes the following values
 *	0: not started yet
 */
struct PCB{
	uint32_t stored_registers[PCB_REGISTERS_STORED];
	uint32_t pid;
	uint32_t state;
	void (*func_addr)();
};


void createNewProcess(void *address);


#endif