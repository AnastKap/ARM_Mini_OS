#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

/* 
 * SysTick - specific definitions
 */

#define SYST_CSR		*(volatile uint32_t *) 0xe000e010
#define SYST_RVR		*(volatile uint32_t *) 0xe000e014
#define SYST_CVR		*(volatile uint32_t *) 0xe000e018
#define SYST_CALIB		*(volatile uint32_t *) 0xe000e01c


// Set the reload value; value is between 0 and 0x00ffffff
void set_systick_reload(uint32_t value);
// Enable SysTick along with its interrupt; First the reload value must have been loaded
void enable_systick();

void SysTick_ISR();

#endif