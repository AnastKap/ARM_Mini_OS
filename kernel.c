#include "peripherals/gpio.h"
#include "peripherals/adc.h"
#include "peripherals/usart.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include "memory_management/memory.h"
#include "clock/clock.h"
#include <stdint.h>



void process1(){
	uint32_t i;
	uint32_t* addr = malloc(4);
    configPin(GPIOC, GPIO_PIN_13, OUTPUT_PUSH_PULL);
	while(1){
		*addr = 0;
		setPin(GPIOC, GPIO_PIN_13, 0);
    for (i = 0; i < 25000; i++);
		*addr = 1;
    setPin(GPIOC, GPIO_PIN_13, 1);
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
    configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
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
    for(int i = 0; i < 8; i++){
		configPin(GPIOA, i, OUTPUT_PUSH_PULL);
	}
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


void testUSART(){
  startUSART(9600);
  startUSARTTransmission();
  while(1){
    startUSART(9600);
    startUSARTTransmission();
    sendByteViaUSART('a');
  }
}

void testDelay(){
    configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
    int val = 1;
    while(1){
        delay_msec(1000);
        setPin(GPIOB, GPIO_PIN_12, val);
        val = ~val;
    }
}

void kernel(){
	disableUnalignedAddressFault();
	initDallocSpace();
	initProcessPages();
	enable_external_clock();
	enableGpioClocks();
	enable_timer_clocks();
	enableADCClocks();
	enable_external_clock_pll(4);
    //enable_uart_clocks();


	startScheduler();
	createNewProcess(process1);
	//createNewProcess(testUSART);
	createNewProcess(testDelay);
	createNewProcess(testADC);

    process1();
}
