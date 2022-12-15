#include "interrupt.h"
#include "..//peripherals/gpio.h"


/*
 * General interrupt-specific definitions
 */

void attachHandler(void *mem_address, void *handler_address){
	*(uint32_t *)mem_address = (uint32_t) handler_address;
}



/* 
 * SysTick - specific definitions
 */

void setSystickReload(uint32_t value){
	SYST_RVR = SYST_RVR & 0xff000000;
	SYST_RVR |= value & 0x00ffffff;
}

void enableSystick(){
	uint32_t current = SYST_CSR & ~(0b111);
	SYST_CSR = current | 0b111;
	SYST_CVR = 100000;
}