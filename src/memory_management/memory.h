#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>


#define KERNEL_USEABLE_RAM_END      0x20003fff    // The end of the RAM area which the kernel can use freely

#define CCR     *(volatile uint32_t*) 0xE000ED14
void disableUnalignedAddressFault();

/*
    ---Process Pages---
    Every process page has at its beginning one byte that indicates its
    availability. We call it proc_state_byte. If it is 0, this page is not used
    by anyone
*/
#define PROCESS_PAGE_SIZE                 400
#define FIRST_PROCESS_PAGE_ADDR           KERNEL_USEABLE_RAM_END + 1
#define PROCESS_PAGE_MAX_STARTING_ADDR    0x20005000 - PROCESS_PAGE_SIZE

// Init proc_state_byte to 0 for all process pages
void initProcessPages();

// Check where there is space for a process to live. Return the start of
// this space. If not return zero
uint32_t findAvailableProcessPage();




/*
    ---Dynamic allocation of memory---
    Here the dynamic memory allocator is implemented
    Each dynamically allocated area has a 16-bit(2 byte) prefix, which indicates
    the length of the allocated area. Then the bytes (which in total are equal to
    the aforementioned length) follow
*/

#define DALLOC_STARTING_ADDR        0x20002000 // The starting address of the space where dynamically allocated memory will be stored
#define DALLOC_ENDING_ADDR          KERNEL_USEABLE_RAM_END

void initDallocSpace();
void* malloc(uint16_t size);


#endif
