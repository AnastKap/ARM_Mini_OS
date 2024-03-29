#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

#define RCC_BASE      0x40021000
#define RCC_CR        *(volatile uint32_t*)(RCC_BASE + 0x00)
#define RCC_CFGR      *(volatile uint32_t*)(RCC_BASE + 0x04)
#define RCC_CIR       *(volatile uint32_t*)(RCC_BASE + 0x08)
#define RCC_APB2RSTR  *(volatile uint32_t*)(RCC_BASE + 0x0c)
#define RCC_APB1RSTR  *(volatile uint32_t*)(RCC_BASE + 0x10)
#define RCC_AHBENR    *(volatile uint32_t*)(RCC_BASE + 0x14)
#define RCC_APB2ENR   *(volatile uint32_t*)(RCC_BASE + 0x18)
#define RCC_APB1ENR   *(volatile uint32_t*)(RCC_BASE + 0x1c)
#define RCC_BDCR      *(volatile uint32_t*)(RCC_BASE + 0x20)
#define RCC_CSR       *(volatile uint32_t*)(RCC_BASE + 0x24)
#define RCC_AHBRSTR   *(volatile uint32_t*)(RCC_BASE + 0x28)
#define RCC_CFGR2     *(volatile uint32_t*)(RCC_BASE + 0x2c)


// Bit shifts for GPIOs enable
#define RCC_IOPAEN   	2
#define RCC_IOPBEN		3
#define RCC_IOPCEN   	4
#define RCC_IOPDEN   	5
#define RCC_IOPEEN   	6


// Bit shifts for ADC enable
#define ADC1EN        9
#define ADC2EN        10
#define ADC3EN        15

// General bit shift Definitions
#define PREDIV1SRC    16
#define PREDIV1       0
#define PLLSRC        16
#define PLLXTPRE      17
#define PLLON         24
#define HSEON         16
#define SW            0



// RCC_CFGR bit shifts
#define MCO         24
#define OTGFSPRE    22
#define PLLMUL      18
#define PLLXTPRE    17
#define PLLSRC      16
#define ADCPRE      14
#define PPRE2       11
#define PPRE1       8
#define HPRE        4
#define SWS         2
#define SW          0



// RCC_APB1ENR bit shifts
#define USART2EN      17
#define TIM2EN        0
#define TIM3EN        1
#define TIM4EN        2
#define TIM5EN        3
#define TIM6EN        4
#define TIM7EN        5


// RCC_APB2ENR bit shifts
#define AFIOEN        0

extern volatile uint32_t USEC_WORKING;  // Current time in usec passed from the beginning of the stm32 life

// Enables the external clock
void enable_external_clock();

// Enable all the GPIO clocks
void enableGpioClocks();

// Enable timer enable_gpio_clocks
void enable_timer_clocks();

// Enable all the ADC clocks
void enableADCClocks();

// Enable the uart2 clocks
void enable_uart_clocks();

// Set and enable external clock PLL
void enable_external_clock_pll(uint8_t multiplier);


// Get the clock freq in kHz
uint32_t getClockFreq();


// Delay msec
void delay_msec(uint32_t msec);

// Get usec working
uint32_t getUsecWorking();

#endif
