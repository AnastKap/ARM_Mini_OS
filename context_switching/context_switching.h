#ifndef CONTEXT_SWITCHING_H
#define CONTEXT_SWITCHING_H

#include <stdint.h>

/* Context switching is achieved using the SysTick and the interrupts that it produces in preset intervals */

// General definitions
#define SCHEDULER_INTERVAL		0x00ffffff


// Starts the scheduler who is responsible for the context switching
void startScheduler();

// Schedule next process
extern uint8_t current_process;
void scheduleNextProcess();


// The ISR for the SysTick which is used by the scheduler
__attribute__ ((interrupt("FIQ"))) void SysTick_ISR();


/*
 * Definitions regarding current process
 */
extern struct PCB * current_PCB_ptr;




#endif