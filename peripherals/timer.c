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

void setPWM(){
  //set up PWM parameters
  TIM2_ARR = 0xFFFF; //frequency
  TIM2_PSC = 0xFFFF; //prescaler
  TIM2_CR1 = (1<<ARPE); //buffered ARR
  TIM2_CCMR1 = (1<<OC2M2)|(1<<OC2M1)|(0<<OC2M0)|(0<<CC2S1)|(0<<CC2S0)|(1<<OC2PE); //PWM mode1, outpuy, preload enable
  TIM2_CCER = (0<<CC2P)|(1<<CC2E); //OC1 active: HIGH, OC1 as output
  TIM2_CCR2 = 0x8000; //50% DC

  //load settings into timer by forcing an update
  TIM2_EGR = (1<<UG);
  TIM2_SR &= 0x0;

  //start timer
  TIM2_CNT = (1<<CEN);

}

void setTimer(uint32_t timer,uint32_t frequency,uint32_t prescaler,uint32_t direction){
  switch(timer){
    case TIM2:
      TIM2_ARR = frequency;
      TIM2_PSC = prescaler;
      TIM2_CNT = (direction<<DIR)|(1<<ARPE);

      //force update in order to load settings to above registers
      TIM2_EGR = (1<<UG);
      TIM2_SR &= 0x0;

      //start timer
      TIM2_CR1 = (1<<CEN);
      break;
    default:
      break;
  }
}
