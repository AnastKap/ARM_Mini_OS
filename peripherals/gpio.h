#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

/*-------------------------------------------------------------------------------------------------------------------*/
/*    GPIOs    */
/*-------------------------------------------------------------------------------------------------------------------*/

// Define the base addresses
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000

// Define port A registers
#define GPIOA_CRL			*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH			*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR			*(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR			*(volatile uint32_t *)(GPIOA_BASE + 0x0c)
#define GPIOA_BSRR		*(volatile uint32_t *)(GPIOA_BASE + 0x10)
#define GPIOA_BRR			*(volatile uint32_t *)(GPIOA_BASE + 0x14)
#define GPIOA_LCKR		*(volatile uint32_t *)(GPIOA_BASE + 0x18)

// Define port B registers
#define GPIOB_CRL			*(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH			*(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR			*(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR			*(volatile uint32_t *)(GPIOB_BASE + 0x0c)
#define GPIOB_BSRR		*(volatile uint32_t *)(GPIOB_BASE + 0x10)
#define GPIOB_BRR			*(volatile uint32_t *)(GPIOB_BASE + 0x14)
#define GPIOB_LCKR		*(volatile uint32_t *)(GPIOB_BASE + 0x18

// Define port C registers
#define GPIOC_CRL			*(volatile uint32_t *)(GPIOC_BASE + 0x00)
#define GPIOC_CRH			*(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_IDR			*(volatile uint32_t *)(GPIOC_BASE + 0x08)
#define GPIOC_ODR			*(volatile uint32_t *)(GPIOC_BASE + 0x0c)
#define GPIOC_BSRR		*(volatile uint32_t *)(GPIOC_BASE + 0x10)
#define GPIOC_BRR			*(volatile uint32_t *)(GPIOC_BASE + 0x14)
#define GPIOC_LCKR		*(volatile uint32_t *)(GPIOC_BASE + 0x18)

// General definitions
#define GPIOA 1
#define GPIOB 2
#define GPIOC 3

#define GPIO_PIN_12 12
#define GPIO_PIN_13 13


// GPIO modes
#define OUTPUT_PUSH_PULL		  0
#define OUTPUT_OPEN_DRAIN     1
#define ALT_FUNC_PUSH_PULL		2
#define ALT_FUNC_OPEN_DRAIN		3


void configPin(uint8_t port, uint8_t pin, uint8_t gpio_mode);
void setPin(uint8_t port, uint8_t pin, uint8_t value);



/*-------------------------------------------------------------------------------------------------------------------*/
/*    TIMERS    */
/*-------------------------------------------------------------------------------------------------------------------*/

//timers TIM2-14 base addresses
#define TIM2 0x40000000
#define TIM3 0x40000400
#define TIM4 0x40000800
#define TIM5 0x40000C00
#define TIM6 0x40001000
#define TIM7 0x40001400
#define TIM12 0x40001800
#define TIM13 0x40001C00
#define TIM14 0x40002000
#define TIM9 0x40014C00
#define TIM10 0x40015000
#define TIM11 0x40015400


//timers registers offsets
#define TIMX_CR1 0x00 //control register1
#define TIMX_CR2 0x04 //control register2

#define TIMX_SMCR 0x08 //slave mode control register
#define TIMX_DIER 0x0C //DMA/interrupt enable register
#define TIMX_SR 0x10 //status register
#define TIMX_EGR 0x14 //event generation register

#define TIMX_CCMR1 0x18 //capture/compare mode register1
#define TIMX_CCMR2 0x1C //capture/compare mode register2
#define TIMX_CCER 0x20 //capture/compare enable register

#define TIMX_CNT 0x24 //counter
#define TIMX_PSC 0x28 //prescaler
#define TIMX_ARR 0x2C //auto-reload register

#define TIMX_CCR1 0x34 //capture/compare register1
#define TIMX_CCR2 0x38 //capture/compare register2
#define TIMX_CCR3 0x3C //capture/compare register3
#define TIMX_CCR4 0x40 //capture/compare register4

#define TIMX_DCR 0x48 //DMA control register
#define TIMX_DMAR 0x4C //DMA address for full transfer


//counting direction
#define UP 0
#define DOWN 1

//simple counters
void setTimer(uint32_t timer,uint8_t direction,uint16_t value);

//PWM mode
void setPWM(uint32_t timer, uint32_t duty_cycle, uint32_t freq)

#endif
