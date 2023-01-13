#ifndef CONTEXT_SWITCHING_H
#define CONTEXT_SWITCHING_H



/*
    How the context switching works?
    The main function of the context switching lies on the fact that every ARM Cortex-M3
    microprocessor has an internal timer, which is called SysTick. This timer
    is a down-counter and can be configured to fire an interrupt every time its
    value reaches zero. After that, it reloads a value, which we set to be the
    trigger-period of the scheduler.

    What steps are followed every time the scheduler is triggered(that means that
    the SysTick counter reaches zero)?
    1) The important information (all core registers) of the currently working
    process are stored in its corresponding PCB
    2) The scheduler finds the next process to be routed
    3) The important information (previous state) of the new process are loaded
    4) Control continuous from the appropriate code segment

    What happens when we want to attach a new process to the system?
    1) Memory is allocated for stack frame
    2) We immitate that an interrupt has just happened on SysTick, thus loading
    the 8-byte length data, which are initialized in valid values. The PC of these
    data takes the starting address of the function that is called from process
    creation and adds 1, to enter Thumb instruction mode
    3) 1) The important information (all core registers) of this process to be
    attached are stored in its corresponding PCB
    4) Return to the main process which created this new process
*/




#include <stdint.h>

/* Context switching is achieved using the SysTick and the interrupts that it produces in preset intervals */

// General definitions
#define SCHEDULER_INTERVAL		0x00000fff
#define TOTAL_NUM_OF_PCB      2


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
