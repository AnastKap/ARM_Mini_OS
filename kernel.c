#include "peripherals/gpio.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include "memory_management/memory.h"
#include <stdint.h>

#define ICSR		*(volatile uint32_t *) 0xE000ED04

#define RCC_BASE      0x40021000
#define RCC_APB2ENR   *(volatile uint32_t *)(RCC_BASE   + 0x18)
#define RCC_IOPCEN   	(1<<4)
#define RCC_IOPBEN		(1 << 3)


void process1(){
	uint32_t i;
	while(1){
		setPin(GPIOC, GPIO_PIN_13, 0);
    for (i = 0; i < 25000; i++);
    setPin(GPIOC, GPIO_PIN_13, 1);
    for (i = 0; i < 25000; i++);
	}
}

void process2(){
	uint32_t i;
	while(1){
		setPin(GPIOB, GPIO_PIN_13, 0);
		for (i = 0; i < 75000; i++);
		setPin(GPIOB, GPIO_PIN_13, 1);
		for (i = 0; i < 75000; i++);
	}
}

void process3(){
	uint32_t i;
	while(1){
		setPin(GPIOB, GPIO_PIN_12, 0);
		for (i = 0; i < 200000; i++);
		setPin(GPIOB, GPIO_PIN_12, 1);
		for (i = 0; i < 200000; i++);
	}
}

void process4(){
	uint32_t i;
	while(1){
		setPin(GPIOB, GPIO_PIN_12, 0);
		for (i = 0; i < 200000; i++);
		setPin(GPIOB, GPIO_PIN_12, 1);
		for (i = 0; i < 200000; i++);
	}
}


void kernel(){
	initProcessPages();
	RCC_APB2ENR |= RCC_IOPCEN | RCC_IOPBEN;

	configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
	configPin(GPIOB, GPIO_PIN_13, OUTPUT_PUSH_PULL);
	configPin(GPIOC, GPIO_PIN_13, OUTPUT_PUSH_PULL);

	startScheduler();
	createNewProcess(process1);
	createNewProcess(process2);
	createNewProcess(process3);

	process1();
}
