#include "timer.h"
#include <stdint.h>

/*
void setTimer(uint32_t timer,uint8_t direction,uint16_t value){
  uint32_t *curr; //pointer to registers addresses

  curr = timer+TIMX_DIER;
  *curr = 0x0001; //enable update interrupt

  curr = timer+TIMX_ARR;
  *curr = value; //set reload value

  curr = timer+TIMX_CR1;
  *curr |= (direction<<4)|(0b1); //set direction bit and CEN=1
}

void setPWM(uint32_t timer, uint32_t duty_cycle, uint32_t freq){
	setTimer(timer,UP,freq);
	uint32_t *curr;

	curr = timer+TIMx_CCR1; //using just the 1st channel
	*curr = duty_cycle;

}*/
