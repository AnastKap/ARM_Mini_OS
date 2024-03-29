#include <stdint.h>

#ifndef TIMER_H
#define TIMER_H


//TIM2-11 base addresses
#define TIM2    0x40000000
#define TIM3    0x40000400
#define TIM4    0x40000800
#define TIM5    0x40000C00
#define TIM6    0x40001000
#define TIM7    0x40001400
#define TIM12   0x40001800
#define TIM13   0x40001C00
#define TIM14   0x40002000
#define TIM9    0x40014C00
#define TIM10   0x40015000
#define TIM11   0x40015400

/*
        TIM2-5: General purpose timers
*/

//TIM2 registers
#define TIM2_CR1    *(volatile uint32_t*) (TIM2+0x00) //control register1
#define TIM2_CR2    *(volatile uint32_t*) (TIM2+0x04) //control register2

#define TIM2_SMCR   *(volatile uint32_t*) (TIM2+0x08) //slave mode control register
#define TIM2_DIER   *(volatile uint32_t*) (TIM2+0x0C) //DMA/interrupt enable register
#define TIM2_SR     *(volatile uint32_t*) (TIM2+0x10) //status register
#define TIM2_EGR    *(volatile uint32_t*) (TIM2+0x14) //event generation register

#define TIM2_CCMR1  *(volatile uint32_t*) (TIM2+0x18) //capture/compare mode register1
#define TIM2_CCMR2  *(volatile uint32_t*) (TIM2+0x1C) //capture/compare mode register2
#define TIM2_CCER   *(volatile uint32_t*) (TIM2+0x20) //capture/compare enable register

#define TIM2_CNT    *(volatile uint32_t*) (TIM2+0x24) //counter
#define TIM2_PSC    *(volatile uint32_t*) (TIM2+0x28) //prescaler
#define TIM2_ARR    *(volatile uint32_t*) (TIM2+0x2C) //auto-reload register

#define TIM2_CCR1   *(volatile uint32_t*) (TIM2+0x34) //capture/compare register1
#define TIM2_CCR2   *(volatile uint32_t*) (TIM2+0x38) //capture/compare register2
#define TIM2_CCR3   *(volatile uint32_t*) (TIM2+0x3C) //capture/compare register3
#define TIM2_CCR4   *(volatile uint32_t*) (TIM2+0x40) //capture/compare register4

#define TIM2_DCR    *(volatile uint32_t*) (TIM2+0x48) //DMA control register
#define TIM2_DMAR   *(volatile uint32_t*) (TIM2+0x4C) //DMA address for full transfer

//TIM3 registers ---------------------------------------------------------------------------------------//
#define TIM3_CR1    *(volatile uint32_t*) (TIM3+0x00) //control register1
#define TIM3_CR2    *(volatile uint32_t*) (TIM3+0x04) //control register2

#define TIM3_SMCR   *(volatile uint32_t*) (TIM3+0x08) //slave mode control register
#define TIM3_DIER   *(volatile uint32_t*) (TIM3+0x0C) //DMA/interrupt enable register
#define TIM3_SR     *(volatile uint32_t*) (TIM3+0x10) //status register
#define TIM3_EGR    *(volatile uint32_t*) (TIM3+0x14) //event generation register

#define TIM3_CCMR1  *(volatile uint32_t*) (TIM3+0x18) //capture/compare mode register1
#define TIM3_CCMR2  *(volatile uint32_t*) (TIM3+0x1C) //capture/compare mode register2
#define TIM3_CCER   *(volatile uint32_t*) (TIM3+0x20) //capture/compare enable register

#define TIM3_CNT    *(volatile uint32_t*) (TIM3+0x24) //counter
#define TIM3_PSC    *(volatile uint32_t*) (TIM3+0x28) //prescaler
#define TIM3_ARR    *(volatile uint32_t*) (TIM3+0x2C) //auto-reload register

#define TIM3_CCR1   *(volatile uint32_t*) (TIM3+0x34) //capture/compare register1
#define TIM3_CCR2   *(volatile uint32_t*) (TIM3+0x38) //capture/compare register2
#define TIM3_CCR3   *(volatile uint32_t*) (TIM3+0x3C) //capture/compare register3
#define TIM3_CCR4   *(volatile uint32_t*) (TIM3+0x40) //capture/compare register4

#define TIM3_DCR    *(volatile uint32_t*) (TIM3+0x48) //DMA control register
#define TIM3_DMAR   *(volatile uint32_t*) (TIM3+0x4C) //DMA address for full transfer

//TIM4 registers----------------------------------------------------------------------------------------//
#define TIM4_CR1    *(volatile uint32_t*) (TIM4+0x00) //control register1
#define TIM4_CR2    *(volatile uint32_t*) (TIM4+0x04) //control register2

#define TIM4_SMCR   *(volatile uint32_t*) (TIM4+0x08) //slave mode control register
#define TIM4_DIER   *(volatile uint32_t*) (TIM4+0x0C) //DMA/interrupt enable register
#define TIM4_SR     *(volatile uint32_t*) (TIM4+0x10) //status register
#define TIM4_EGR    *(volatile uint32_t*) (TIM4+0x14) //event generation register

#define TIM4_CCMR1  *(volatile uint32_t*) (TIM4+0x18) //capture/compare mode register1
#define TIM4_CCMR2  *(volatile uint32_t*) (TIM4+0x1C) //capture/compare mode register2
#define TIM4_CCER   *(volatile uint32_t*) (TIM4+0x20) //capture/compare enable register

#define TIM4_CNT    *(volatile uint32_t*) (TIM4+0x24) //counter
#define TIM4_PSC    *(volatile uint32_t*) (TIM4+0x28) //prescaler
#define TIM4_ARR    *(volatile uint32_t*) (TIM4+0x2C) //auto-reload register

#define TIM4_CCR1   *(volatile uint32_t*) (TIM4+0x34) //capture/compare register1
#define TIM4_CCR2   *(volatile uint32_t*) (TIM4+0x38) //capture/compare register2
#define TIM4_CCR3   *(volatile uint32_t*) (TIM4+0x3C) //capture/compare register3
#define TIM4_CCR4   *(volatile uint32_t*) (TIM4+0x40) //capture/compare register4

#define TIM4_DCR    *(volatile uint32_t*) (TIM4+0x48) //DMA control register
#define TIM4_DMAR   *(volatile uint32_t*) (TIM4+0x4C) //DMA address for full transfer

//TIM5 registers----------------------------------------------------------------------------------------//
#define TIM5_CR1    *(volatile uint32_t*) (TIM5+0x00) //control register1
#define TIM5_CR2    *(volatile uint32_t*) (TIM5+0x04) //control register2

#define TIM5_SMCR   *(volatile uint32_t*) (TIM5+0x08) //slave mode control register
#define TIM5_DIER   *(volatile uint32_t*) (TIM5+0x0C) //DMA/interrupt enable register
#define TIM5_SR     *(volatile uint32_t*) (TIM5+0x10) //status register
#define TIM5_EGR    *(volatile uint32_t*) (TIM5+0x14) //event generation register

#define TIM5_CCMR1  *(volatile uint32_t*) (TIM5+0x18) //capture/compare mode register1
#define TIM5_CCMR2  *(volatile uint32_t*) (TIM5+0x1C) //capture/compare mode register2
#define TIM5_CCER   *(volatile uint32_t*) (TIM5+0x20) //capture/compare enable register

#define TIM5_CNT    *(volatile uint32_t*) (TIM5+0x24) //counter
#define TIM5_PSC    *(volatile uint32_t*) (TIM5+0x28) //prescaler
#define TIM5_ARR    *(volatile uint32_t*) (TIM5+0x2C) //auto-reload register

#define TIM5_CCR1   *(volatile uint32_t*) (TIM5+0x34) //capture/compare register1
#define TIM5_CCR2   *(volatile uint32_t*) (TIM5+0x38) //capture/compare register2
#define TIM5_CCR3   *(volatile uint32_t*) (TIM5+0x3C) //capture/compare register3
#define TIM5_CCR4   *(volatile uint32_t*) (TIM5+0x40) //capture/compare register4

#define TIM5_DCR    *(volatile uint32_t*) (TIM5+0x48) //DMA control register
#define TIM5_DMAR   *(volatile uint32_t*) (TIM5+0x4C) //DMA address for full transfer

//TIMx_CR1 bits
#define CKD1  9
#define CKD0  8
#define ARPE  7
#define CMS1  6
#define CMS0  5
#define DIR   4
#define OPM   3
#define URS   3
#define UDIS  1
#define CEN   0

//TIMx_CR2 bits
#define TI1S  7
#define MMS2  6
#define MMS1  5
#define MMS0  4
#define CCDS  3

//TIMx_SMCR bits
//TODO

//TIMx_DIER bits
#define TDE  14
#define CC4DE 12
#define CC3DE 11
#define CC2DE 10
#define CC1DE 9
#define UDE  8
#define TIE  6
#define CC4IE 4
#define CC3IE 3
#define CC2IE 2
#define CC1IE 1
#define UIE  0

//TIMx_SR bits
#define CC4OF 12
#define CC3OF 11
#define CC2OF 10
#define CC1OF 9
#define TIF 8
#define CC4IF 4
#define CC3IF 3
#define CC2IF 2
#define CC1IF 1
#define UIF 0

//TIMx_CCMR1 output compare mode bits
#define OC2CE   15
#define OC2M    12
#define OC2PE   11
#define OC2FE   10
#define CC2S    8
#define OC1CE   7
#define OC1M    4
#define OC1PE   3
#define OC1FE   2
#define CC1S    0

//TIMx_CCMR1 input capture mode bits
//TODO

//TIMx_CCMR2 output compare mode bits
#define OC4CE 15
#define OC4M2 14
#define OC4M1 13
#define OC4M0 12
#define OC4PE 11
#define OC4FE 10
#define CC4S1 9
#define CC4S0 8
#define OC3CE 7
#define OC3M2 6
#define OC3M1 5
#define OC3M0 4
#define OC3PE 3
#define OC3FE 2
#define CC3S1 1
#define CC3S0 0

//TIMx_CCER bits
#define CC4P  13
#define CC4E  12
#define CC3P  9
#define CC3E  8
#define CC2P  5
#define CC2E  4
#define CC1P  1
#define CC1E  0

//TIMx_EGR bits
#define TG  6
#define CC4G  4
#define CC3G  3
#define CC2G  2
#define CC1G  1
#define UG  0

//timer directions
#define UP 0
#define DOWN 1

// Frequency given in Hz
void setPWM(uint32_t frequency);

// Set Timers 2-3-4-5 to user's params
void setTimer(uint32_t timer,uint32_t frequency,uint32_t prescaler,uint32_t direction,uint32_t intr_en);


#endif
