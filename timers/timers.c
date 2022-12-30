#include "timers.h"

void counter(uint32_t timer,uint8_t direction,uint16_t value){
  uint32_t *curr; //pointer to registers addresses

  curr = timer+TIMX_DIER;
  *curr = 0x0001; //enable update interrupt

  curr = timer+TIMX_ARR;
  *curr = value; //set reload value

  curr = timer+TIMX_CR1;
  *curr |= (direction<<4)|(0b1);
}
