#include "interrupt.h"
#include "..//peripherals/gpio.h"
#include "..//peripherals/timer.h"


/*
 * General interrupt-specific definitions
 */

void attachHandler(void *mem_address, void *handler_address){
	*(uint32_t *)mem_address = (uint32_t) handler_address;
}



/*
 * SysTick - specific definitions
 */

void setSystickReload(uint32_t value){
	SYST_RVR = SYST_RVR & 0xff000000;
	SYST_RVR |= value & 0x00ffffff;
}

void enableSystick(){
	uint32_t current = SYST_CSR & ~(0b111);
	SYST_CSR = current | 0b111;
	SYST_CVR = 100000;
}

void setInterrupt(uint32_t position){
	if(position<32)
		NVIC_ISER0 |= (1<<position);
}

void clearInterrupt(uint32_t position){
	if(position<32)
		NVIC_ICER0 |= (1<<position);
}


__attribute__((interrupt("FIQ"))) void HardFault_ISR(){
	setPin(GPIOB, GPIO_PIN_12, 0);
}

int led = 0;
__attribute__((interrupt("IRQ"))) void TIM2_ISR(){
	//static i;
	led = ~led;
	setPin(GPIOB, GPIO_PIN_12, led);
	setPin(GPIOB, GPIO_PIN_5, led);
	TIM2_SR &=0x0; //clear status register
}
