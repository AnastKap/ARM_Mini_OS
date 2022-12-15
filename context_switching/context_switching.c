#include "context_switching.h"
#include "../interrupts/interrupt.h"
#include "../peripherals/gpio.h"

void startScheduler(){
	setSystickReload(SCHEDULER_INTERVAL);
	enableSystick();
	//attachHandler((uint32_t *) 0x3c, SysTick_ISR);
}

__attribute__ ((interrupt ("FIQ"))) void SysTick_ISR(){
	set_pin(GPIOC, GPIO_PIN_13, 0);
    for (int i = 0; i < 200000; i++);
	//GPIOC_ODR &= ~GPIOC13;
    set_pin(GPIOC, GPIO_PIN_13, 1);
    for (int i = 0; i < 200000; i++);
}