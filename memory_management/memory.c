#include "memory.h"


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
