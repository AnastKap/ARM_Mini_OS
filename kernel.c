#include "peripherals/gpio.h"
#include "peripherals/adc.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include "memory_management/memory.h"
#include "clock/clock.h"
#include "peripherals/timer.h"
#include <stdint.h>



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

void process3(){
	uint32_t i;
	uint32_t* addr = malloc(4);
	while(1){
		*addr = 0;
		setPin(GPIOB, GPIO_PIN_12, *addr);
		for (i = 0; i < 200000; i++);
		*addr = 1;
		setPin(GPIOB, GPIO_PIN_12, *addr);
		for (i = 0; i < 200000; i++);
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
	//it works fine on debug: counter and status change value
	//on flash it seems like there is no delay
	uint32_t *cr1 = &TIM2_CR1;
	uint32_t *status = &TIM2_SR;
	uint32_t *counter = &TIM2_CNT;

	TIM2_ARR = 0xFFFF;
	TIM2_PSC = 0xFFFF;
	TIM2_CR1 = (0<<CMS1)|(0<<CMS1)|(0<<DIR)|(0<<URS)|(0<<UDIS)|(1<<CEN);

	/*
	TIMx_PSC is loaded its proper value after the first update event.
	This requires a "false" first update event.

	TIMx_SR bits are cleared by software and set by hardware.
	*/

	if((TIM2_SR && (1<<UIF)==0x01)) TIM2_SR &=0x00; //clear SR after first, "false" event

	while(1){
		if((TIM2_SR && (1<<UIF)) == 0x01){
			TIM2_SR &= 0x00; //manually clear SR
			demo();
		}
	}
}

void demo(){
	while(1){
		uint32_t i;
		setPin(GPIOC, GPIO_PIN_13, 1);
		for (i = 0; i < 75000; i++);
		setPin(GPIOC, GPIO_PIN_13, 0);
		for (i = 0; i < 75000; i++);
	}
}

void kernel(){
	//disableUnalignedAddressFault();
	//initDallocSpace();
	//initProcessPages();
	enable_external_clock();
	enable_gpio_clocks();
	enable_timer_clocks();
	enable_adc_clocks();
	//enable_external_clock_pll(4);

	configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
	for(int i = 0; i < 8; i++){
		configPin(GPIOA, i, OUTPUT_PUSH_PULL);
	}
	configPin(GPIOC, GPIO_PIN_13, OUTPUT_PUSH_PULL);

	/*
	startScheduler();
	createNewProcess(process1);
	//createNewProcess(process2);
	createNewProcess(process3);
	createNewProcess(testADC);

	process1();
	*/
	testTIM2();
}
