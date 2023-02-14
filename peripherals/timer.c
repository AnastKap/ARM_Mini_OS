#include "timer.h"
#include <stdint.h>

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

void setTimer(uint32_t timer,uint32_t frequency,uint32_t prescaler,uint32_t direction,uint32_t intr_en){
  /*
  Set-up TIMx registers to user's values/settings.
  Force update event (using TIMx_EGR(UG = 1)) to load settings to said registers.
  Enable counter and enable/disable interrupt.
  */
  switch(timer){
    case TIM2:
      TIM2_ARR = frequency;
      TIM2_PSC = prescaler;
      TIM2_CR1 = (direction<<DIR)|(1<<ARPE);
      TIM2_EGR = (1<<UG);
      TIM2_SR &= 0x0;
      TIM2_CR1 |= (1<<CEN);
      TIM2_DIER = (intr_en<<UIE);
      break;
    case TIM3:
      TIM3_ARR = frequency;
      TIM3_PSC = prescaler;
      TIM3_CR1 = (direction<<DIR)|(1<<ARPE);
      TIM3_EGR = (1<<UG);
      TIM3_SR &= 0x0;
      TIM3_CR1 |= (1<<CEN);
      TIM3_DIER = (intr_en<<UIE);
      break;
    case TIM4:
      TIM4_ARR = frequency;
      TIM4_PSC = prescaler;
      TIM4_CR1 = (direction<<DIR)|(1<<ARPE);
      TIM4_EGR = (1<<UG);
      TIM4_SR &= 0x0;
      TIM4_CR1 |= (1<<CEN);
      TIM4_DIER = (intr_en<<UIE);
      break;
    case TIM5:
      TIM5_ARR = frequency;
      TIM5_PSC = prescaler;
      TIM5_CR1 = (direction<<DIR)|(1<<ARPE);
      TIM5_EGR = (1<<UG);
      TIM5_SR &= 0x0;
      TIM5_CR1 |= (1<<CEN);
      TIM5_DIER = (intr_en<<UIE);
      break;
    default:
      break;
  }
}
