#include "peripherals/gpio.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include <stdint.h>

#define ICSR		*(volatile uint32_t *) 0xE000ED04

#define RCC_BASE      0x40021000
#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18)
#define RCC_IOPCEN   (1<<4)

#define GPIOC13 (1 << 13UL)

void process1(){
	while(1){
		//GPIOC_ODR |=  GPIOC13;
		set_pin(GPIOC, GPIO_PIN_13, 0);
        for (int i = 0; i < 50000; i++);
		//GPIOC_ODR &= ~GPIOC13;
        set_pin(GPIOC, GPIO_PIN_13, 1);
        for (int i = 0; i < 50000; i++);
	}
}

void process2(){
	while(1){
		//GPIOC_ODR |=  GPIOC13;
		set_pin(GPIOC, GPIO_PIN_13, 0);
        for (int i = 0; i < 25000; i++);
		//GPIOC_ODR &= ~GPIOC13;
        set_pin(GPIOC, GPIO_PIN_13, 1);
        for (int i = 0; i < 25000; i++);
	}
}


void kernel(){
	
	config_pin(GPIOC, GPIO_PIN_13, OUTPUT_PUSH_PULL);
	/*set_systick_reload(0x00ffffff);
	enable_systick();*/
	
	RCC_APB2ENR |= RCC_IOPCEN;
	GPIOC_CRH   &= 0xFF0FFFFF;
    GPIOC_CRH   |= 0x00200000;
	
	startScheduler();
	createNewProcess(process1);
	
    /*while(1){
		//GPIOC_ODR |=  GPIOC13;
		set_pin(GPIOC, GPIO_PIN_13, 0);
        for (int i = 0; i < 50000; i++);
		//GPIOC_ODR &= ~GPIOC13;
        set_pin(GPIOC, GPIO_PIN_13, 1);
        for (int i = 0; i < 50000; i++);
	}*/
	process2();
}