#include "memory.h"


void disableUnalignedAddressFault(){
  CCR &= ~(1 << 3);
}


void initProcessPages(){
  uint32_t current_page_starting_addr = FIRST_PROCESS_PAGE_ADDR;
  while(current_page_starting_addr < PROCESS_PAGE_MAX_STARTING_ADDR){
    *(uint32_t *)current_page_starting_addr = 0;
    current_page_starting_addr += PROCESS_PAGE_SIZE;
  }
}

//cause HARD FAULT
uint32_t findAvailableProcessPage(){
  uint32_t current_page_starting_addr = FIRST_PROCESS_PAGE_ADDR;
  uint32_t proc_state_byte;
  while(current_page_starting_addr < PROCESS_PAGE_MAX_STARTING_ADDR){
    proc_state_byte = *(uint32_t *)current_page_starting_addr;
    if(!proc_state_byte) return current_page_starting_addr;
    current_page_starting_addr += PROCESS_PAGE_SIZE;
  }
  return 0;
}



void initDallocSpace(){
  for(uint32_t i = DALLOC_STARTING_ADDR; i <= KERNEL_USEABLE_RAM_END; i++){
    *(uint32_t*)i = 0;
  }
}

/* Take care of the probability that when zero found, the data don't fit in */
void* malloc(uint16_t size){
  uint32_t cur_addr = DALLOC_STARTING_ADDR;
  uint16_t length;
  length = *(uint16_t*)cur_addr;
  while((length != 0) && (cur_addr < DALLOC_ENDING_ADDR)){
    cur_addr += length + 2;
    length = *(uint16_t*)cur_addr;
  }
  if(cur_addr + 1 + size > DALLOC_ENDING_ADDR) return 0;
  else{
    *(uint16_t*)cur_addr = size;
    return (void*)(cur_addr + 2);
  }
}
