#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#define PCB_REGISTERS_STORED		40
struct PCB{
	uint32_t stored_registers[PCB_REGISTERS_STORED];
	uint32_t pid;
};


void createNewProcess(void *address);


#endif