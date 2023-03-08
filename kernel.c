#include "peripherals/gpio.h"
#include "peripherals/adc.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include "memory_management/memory.h"
#include "clock/clock.h"
#include "peripherals/timer.h"
#include "peripherals/timer.c"
#include <stdint.h>

int pipe,p1,p2,p3,p4,p5;
int write_res;
int val1,val2,val3,val4;
uint32_t cnt;
uint32_t dier;

void process1(){
	uint32_t i;
	uint32_t* addr = malloc(4);
	while(1){
		*addr = 0;
		setPin(GPIOC, GPIO_PIN_13, *addr);
    for (i = 0; i < 25000; i++);
		*addr = 1;
    setPin(GPIOC, GPIO_PIN_13, *addr);
    for (i = 0; i < 25000; i++);
	}
}

void process2(){
	uint32_t i;
	while(1){
		setPin(GPIOA, GPIO_PIN_0, 0);
		for (i = 0; i < 75000; i++);
		setPin(GPIOA, GPIO_PIN_0, 1);
		for (i = 0; i < 75000; i++);
	}
}

void testADC(){
	uint8_t seq[] = {8};
	startContinuousConversion(seq, 1);
	while(1){
		uint16_t data = readDataConverted() >> 4;
		for(int i = 0; i < 8; i++){
			setPin(GPIOA, i, data%2);
			data /= 2;
		}
	}
}

void testTIM2(){
	setPin(GPIOB, GPIO_PIN_5, 0);
	setTimer(TIM2,0xff,0x0fff,UP,1);
	setInterrupt(TIM2_IRQ);
	//clearInterrupt(TIM2_IRQ);
	while(1){

	}
}

void testTIM4(){
	cnt = (TIM4+0x24);
	dier = (TIM4+0x0C);
	setPin(GPIOB, GPIO_PIN_13, 0);
	setTimer(TIM4,0xff,0xffff,UP,1);
	setInterrupt(TIM4_IRQ);
	//clearInterrupt(TIM2_IRQ);
	while(1){

	}
}

void testPipeWrite(){
	write_res = writePipeByte(p2,0);
	/*
	write_res = writePipeByte(pipe,5);
	write_res = writePipeByte(pipe,4);
	write_res = writePipeByte(pipe,3);
	*/
	while(1){
	}
}

void testPipeRead(){
	val1 = readPipeByte(pipe);
	val2 = readPipeByte(pipe);
	val3 = readPipeByte(pipe);
	val4 = readPipeByte(p2);
	setPin(GPIOB,13,val4);
	while(1){
	}
}


//test
void kernel(){
	disableUnalignedAddressFault();
	initDallocSpace();
	initProcessPages();
	initPipeSpace();
	enable_external_clock();
	enable_gpio_clocks();
	enable_timer_clocks();
	enable_adc_clocks();
	enable_external_clock_pll(1);

	configPin(GPIOB, GPIO_PIN_13, OUTPUT_PUSH_PULL);
	configPin(GPIOB, GPIO_PIN_5, OUTPUT_PUSH_PULL);

	pipe = createPipe();
	p1 = createPipe();
	p2 = createPipe();
	p3 = createPipe();
	p4 = createPipe();
	p5 = createPipe(); //should be p5=-1

	startScheduler();
	createNewProcess(process1);
	createNewProcess(testTIM2);
	//createNewProcess(testTIM4);
	//createNewProcess(testTIM4);
	createNewProcess(testPipeWrite);
	createNewProcess(testPipeRead);


	//process1();


	//process1();
	//testTIM2();
	//setPWM();
}
