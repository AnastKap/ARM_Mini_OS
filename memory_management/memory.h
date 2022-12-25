#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>


#define PROCESS_PAGE_SIZE                 200
#define FIRST_PROCESS_PAGE_ADDR           0x20004000
#define PROCESS_PAGE_MAX_STARTING_ADDR    0x20005000 - PROCESS_PAGE_SIZE


/*
  ---Process Pages---
  Every process page has at its beginning one byte that indicates its
  availability. We call it proc_state_byte. If it is 0, this page is note used
  by anyone
*/


// Init proc_state_byte to 0 for all process pages
void initProcessPages();

// Check where there is space for a process to live. Return the start of
// this space. If not return zero
uint32_t findAvailableProcessPage();


#endif
