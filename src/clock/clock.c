#include "clock.h"

volatile uint32_t USEC_WORKING = 0;

void enable_external_clock(){
    RCC_CR |= ((uint32_t)1 << 16);
    RCC_CR |= ((uint32_t)1 << HSEON);
}


void enableGpioClocks(){
    RCC_APB2ENR |= (1 << RCC_IOPAEN) | (1 << RCC_IOPBEN) | (1 << RCC_IOPCEN) | (1 << RCC_IOPDEN) | (1 << RCC_IOPEEN);
}

void enable_timer_clocks(){
    RCC_APB1ENR |= (1 << TIM2EN) | (1 << TIM3EN) | (1 << TIM4EN) | (1 << TIM5EN) | (1 << TIM6EN) | (1 << TIM7EN);
}

void enableADCClocks(){
    RCC_APB2ENR |= (1 << ADC1EN) | (1 << ADC2EN) | (1 << ADC3EN);
}

void enable_uart_clocks(){
    RCC_APB1ENR |= (1 << USART2EN);
    RCC_APB2ENR |= (1 << AFIOEN);
}

// See reference manual on which multiplier to select
void enable_external_clock_pll(uint8_t multiplier){
    RCC_CFGR |= ((uint32_t)1 << PLLSRC);
    RCC_CFGR &= ~((uint32_t)0b1111 << PLLMUL);

    uint32_t multiplier_select = multiplier - 2;
    RCC_CFGR |= (multiplier_select << PLLMUL);


    RCC_CR |= ((uint32_t)1 << PLLON);
    RCC_CFGR &= ~((uint32_t)1 << SW);
    RCC_CFGR |= (0b10 << SW);
}

#define EXTERNAL_CRYSTAL_kHz        8000
uint32_t getClockFreq(){
    uint32_t freq = 8000;
    // Check if PLL is enabled
    uint32_t pll_enabled = (RCC_CR >> PLLON) & 1;
    uint32_t pll_mul = ((RCC_CFGR >> PLLMUL) & 0b1111) + 2;
    if(pll_enabled) freq = EXTERNAL_CRYSTAL_kHz * pll_mul;
    return freq;
}


// Takes as argument a value that is used to make the count-down
__attribute((naked)) void delay_1_msec(uint32_t cmp_value){
    __asm volatile(
        "push {r0}\n"
        "delay_loop:\n"
        "sub r0, r0, #1\n"
        "cmp r0, #0\n"
        "bne delay_loop\n"
        "pop {r0}\n"
        "bx lr \n"
    );
}

void delay_msec(uint32_t msec){
    // The value of msec is stored in r0
    uint32_t freq = getClockFreq();
    freq /= 14; // This value is to account for the delay of the loop in delay_1_msec
    for(uint32_t i = 0; i < msec; i++){
        delay_1_msec(freq);
    }
}

uint32_t getUsecWorking(){
    return USEC_WORKING;
}
