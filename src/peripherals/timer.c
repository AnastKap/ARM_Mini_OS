#include "timer.h"
#include <stdint.h>
#include "../clock/clock.h"

/* Returns the clock frequency given as input to the timer peripheral in kHz*/
uint32_t getTimerClockFreq(){
    uint32_t clock_freq = getClockFreq(); // in kHz
    uint32_t ahb_pre_reg = ((RCC_CFGR & (111 << HPRE)) >> HPRE);
    uint32_t ahb_pre = 1;
    for(uint8_t i = 0; i < ahb_pre_reg; i++){
        if(i == 5) ahb_pre *= 2;
        ahb_pre *= 2;
    }
    uint32_t after_ahb_pre = (clock_freq)/ahb_pre;
    uint16_t apb1_pre_reg = (RCC_CFGR & (1111 << PPRE1)) >> PPRE1;
    uint16_t apb1_pre = 1;
    for(uint8_t i = 0; i < apb1_pre_reg; i++){
        apb1_pre *= 2;
    }
    uint32_t after_apb1_pre = after_ahb_pre/apb1_pre;
    if(apb1_pre == 1) return after_apb1_pre;
    else return after_apb1_pre*2;
}

// Frequency given in Hz
// We are going to use channel 2(PA1)
void setPWM(uint32_t frequency){
  //set up PWM parameters
  //TIM2_ARR = 0xFFFF; //frequency
  //TIM2_PSC = 0xFFFF; //prescaler
  TIM2_CR1 = (1<<ARPE); //buffered ARR
  TIM2_CCMR1 = (0<<OC2CE)|(111<<OC2M)|(00<<CC2S)|(1<<OC2PE); //PWM mode1, output, preload enable
  TIM2_CCER = (1<<CC2P)|(1<<CC2E); //OC2 active: HIGH, OC2 as output
  //TIM2_CCR2 = 0x8000; //50% DC

  // Set timer clock and prescaler
  uint16_t prescaler = 0xfff;
  TIM2_PSC = prescaler - 1; // No prescaling to the timer frequency

  // Set the frequency and the duty cycle
  uint32_t ARR;
  uint32_t timer_clock = getTimerClockFreq();
  ARR = (timer_clock*1000/(prescaler))/frequency;
  TIM2_ARR = ARR;//ARR;
  TIM2_CCR2 = ARR/2;

  //load settings into timer by forcing an update
  TIM2_EGR = (1<<UG);
  TIM2_SR &= 0x0;

  //start timer
  TIM2_CR1 |= (1<<CEN);


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
