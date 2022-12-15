#ifndef CONTEXT_SWITCHING_H
#define CONTEXT_SWITCHING_H

/* Context switching is achieved using the SysTick and the interrupts that it produces in preset intervals */

// General definitions
#define SCHEDULER_INTERVAL		0x00ffffff


// Starts the scheduler who is responsible for the context switching
void startScheduler();

// The ISR for the SysTick which is used by the scheduler
__attribute__ ((interrupt("FIQ"))) void SysTick_ISR();


/*
 * Definitions regarding current process
 */
extern void * current_PCB_ptr;




#endif