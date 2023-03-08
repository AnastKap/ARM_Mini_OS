#include "clock.h"

void enable_external_clock(){
  RCC_CR |= ((uint32_t)1 << 16);
  RCC_CR |= ((uint32_t)1 << HSEON);
}


void enable_gpio_clocks(){
  RCC_APB2ENR |= (1 << RCC_IOPAEN) | (1 << RCC_IOPBEN) | (1 << RCC_IOPCEN) | (1 << RCC_IOPDEN) | (1 << RCC_IOPEEN);
}

void enable_timer_clocks(){
  RCC_APB1ENR |= (1 << TIM2EN) | (1 << TIM3EN) | (1 << TIM4EN) | (1 << TIM5EN) | (1 << TIM6EN) | (1 << TIM7EN);
}

void enable_adc_clocks(){
  RCC_APB2ENR |= (1 << ADC1EN) | (1 << ADC2EN) | (1 << ADC3EN);
}

// See reference manual on which multiplier to select
void enable_external_clock_pll(uint8_t multiplier){
  RCC_CFGR |= ((uint32_t)1 << PLLSRC);
  RCC_CFGR &= ~((uint32_t)0b1111 << PLLMUL);

  uint32_t multiplier_select = multiplier - 1;
  RCC_CFGR |= (multiplier_select << PLLMUL);


  RCC_CR |= ((uint32_t)1 << PLLON);
  RCC_CFGR &= ~((uint32_t)1 << SW);
  RCC_CFGR |= (0b10 << SW);
}
