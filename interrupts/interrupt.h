#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>


/*
 * General interrupt-specific definitions
 */

// Function to attach an interrupt handler to a specific address (hence to a specific interrupt)   DOES NOT WORK; PRODUCES HARD FAULT
void attachHandler(void *mem_address, void *handler_address);




/* 
 * SysTick - specific definitions
 */

#define SYSTICK_VT_ADDR		0x3c

#define SYST_CSR			*(volatile uint32_t *) 0xe000e010
#define SYST_RVR			*(volatile uint32_t *) 0xe000e014
#define SYST_CVR			*(volatile uint32_t *) 0xe000e018
#define SYST_CALIB			*(volatile uint32_t *) 0xe000e01c


// Set the reload value; value is between 0 and 0x00ffffff
void setSystickReload(uint32_t value);
// Enable SysTick along with its interrupt; First the reload value must have been loaded
void enableSystick();



// Interrupts
__attribute__((interrupt("FIQ"))) void HardFault_ISR();

#endif