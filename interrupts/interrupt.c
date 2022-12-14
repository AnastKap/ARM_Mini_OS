#include "interrupt.h"
#include "..//peripherals/gpio.h"

/* 
 * SysTick - specific definitions
 */

void set_systick_reload(uint32_t value){
	SYST_RVR = SYST_RVR & 0xff000000;
	SYST_RVR |= value & 0x00ffffff;
}

void enable_systick(){
	uint32_t current = SYST_CSR & ~(0b111);
	SYST_CSR = current | 0b111;
	SYST_CVR = 0;
}

#define GPIOC13 (1 << 13UL)
void SysTick_ISR(){
	//__asm volatile("bkpt");
	while(1)
    {
        GPIOC_ODR |=  GPIOC13;
        for (int i = 0; i < 500000; i++); // arbitrary delay
        GPIOC_ODR &= ~GPIOC13;
        for (int i = 0; i < 500000; i++); // arbitrary delay
    }
}