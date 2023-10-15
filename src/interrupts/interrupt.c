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

/*
 * Enable selected interrupt 
 */

void setInterrupt(uint32_t position){
	if(position<32)
		NVIC_ISER0 |= (1<<position);
	else if(position<64)
		position -= 32;
 		NVIC_ISER1 |= (1<<position);
}

/*
 * Disable selected interrupt 
 */

void clearInterrupt(uint32_t position){
	if(position<32)
		NVIC_ICER0 |= (1<<position);
	else if(position<64)
		position -= 32;
	 	NVIC_ICER1 |= (1<<position);
}

/*
 * Some interrupt implementations for testing and debbuging. 
 */

__attribute__((interrupt("FIQ"))) void HardFault_ISR(){
	setPin(GPIOB, GPIO_PIN_12, 0);
}

int led1 = 0;
__attribute__((interrupt("IRQ"))) void TIM2_ISR(){
	led1 = ~led1;
	setPin(GPIOB, 5, led1);
	TIM2_SR &=0x0; //clear status register
}

int led2 = 0;
__attribute__((interrupt("IRQ"))) void TIM3_ISR(){

}

int led3 = 0;
__attribute__((interrupt("IRQ"))) void TIM4_ISR(){
	led3 = ~led3;
	setPin(GPIOB, 13, led3);
	TIM4_SR &=0x0; //clear status register
}


__attribute__((interrupt("IRQ"))) void TIM5_ISR(){
	led3 = ~led3;
	setPin(GPIOB, 15, led3);
	TIM4_SR &=0x0; //clear status register
}
