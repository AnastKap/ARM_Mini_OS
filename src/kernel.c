#include "peripherals/gpio.h"
#include "peripherals/adc.h"
#include "peripherals/usart.h"
#include "peripherals/timer.h"
#include "interrupts/interrupt.h"
#include "context_switching/context_switching.h"
#include "process/process.h"
#include "memory_management/memory.h"
#include "clock/clock.h"
#include "misc/music.h"
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
    for(int i = 0; i <= 8; i++){
        if(i == 1) continue;
        configPin(GPIOA, i, OUTPUT_PUSH_PULL);
    }
    uint8_t seq[] = {8};
    startContinuousConversion(seq, 1);
    while(1){
        uint16_t data = readDataConverted() >> 4;
        for(int i = 0; i < 8; i++){
            if(i == 1) setPin(GPIOA, 8, data%2);
            else setPin(GPIOA, i, data%2);
            data /= 2;
        }
    }
}


void testUSART(){
    startUSART(115200);
    startUSARTTransmission();
    while(1){
        //startUSART(9600);
        startUSARTTransmission();
        sendByteViaUSART('a');
    }
}

void testDelay(){
    configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
    configPin(GPIOB, GPIO_PIN_12, OUTPUT_PUSH_PULL);
    int val = 1;
    while(1){
        uint32_t current = getUsecWorking();
        //delay_msec(1000);
        while(getUsecWorking() - current < 1000000);
        setPin(GPIOB, GPIO_PIN_12, val);
        val = ~val;
    }
}

void test_pwm(){
    configPin(GPIOA, GPIO_PIN_1, ALT_FUNC_PUSH_PULL);
    setPWM(440);
    while(1){}
}

void testTIM2(){
	setTimer(TIM2,0xff,0xffff,UP,0);
	while(1){
		if((TIM2_SR && (1<<UIF)) == 0x01){
			TIM2_SR &= 0x00; //manually clear SR
			setPin(GPIOB, GPIO_PIN_12, 1);
		}
	}
}

void testTIM4(){
    configPin(GPIOB, GPIO_PIN_13, OUTPUT_PUSH_PULL);
	setPin(GPIOB, GPIO_PIN_13, 0);
	setTimer(TIM4,0xff,0xffff,UP,1);
	setInterrupt(TIM4_IRQ);
	//clearInterrupt(TIM2_IRQ);
	while(1){

	}
}

void play_music(){
    configPin(GPIOA, GPIO_PIN_1, ALT_FUNC_PUSH_PULL);
    setBPM(200);

    while(1){
        // Play two times
        for(int i = 0; i < 2; i++){
            play_note("E2", 8);
            play_note("G2", 8);
            play_note("A2", 4);
            play_note("A2", 4);

            play_note("A2", 8);
            play_note("B2", 8);
            play_note("C3", 4);
            play_note("C3", 4);

            play_note("C3", 8);
            play_note("D3", 8);
            play_note("B2", 4);
            play_note("B2", 4);

            play_note("A2", 8);
            play_note("G2", 8);
            play_note("A2", 4);
            play_note("A2", 4);
        }
        play_note("E2", 8);
        play_note("G2", 8);
        play_note("A2", 4);
        play_note("A2", 4);

        play_note("A2", 8);
        play_note("B2", 8);
        play_note("C3", 4);
        play_note("C3", 4);

        play_note("C3", 8);
        play_note("D3", 8);
        play_note("E3", 4);
        play_note("E3", 4);

        play_note("D3", 8);
        play_note("C3", 8);
        play_note("D3", 4);
        play_note("A2", 4);
        play_pause(8);

        play_note("B2", 8);
        play_note("C3", 4);
        play_note("C3", 4);

        play_note("D3", 4);
        play_note("E3", 8);
        play_note("A2", 4);
        play_pause(8);

        play_note("A2", 8);
        play_note("C3", 8);
        play_note("B2", 4);
        play_note("B2", 4);

        play_note("B2", 8);
        play_note("A2", 8);
        play_note("B2", 2);
        play_pause(4);

        play_note("E3", 2);
        play_note("F3", 2);
        play_note("E3", 8);
        play_pause(16);
        play_note("E3", 8);
        play_pause(16);
        play_note("E3", 8);
        play_note("E3", 16);
        play_note("D3", 2);

        play_note("D3", 2);
        play_note("C3", 2);
        play_note("B2", 8);
        play_pause(16);
        play_note("C3", 8);
        play_pause(16);
        play_note("B2", 8);
        play_note("A2", 2);
        play_pause(4);

        dukes_of_hazard_music();
    }
    //play_note("A2", 4);
    //play_note("A2", 4);
    //play_note("A2", 4);
    //play_note("A2", 4);
    //play_note("A2", 4);

    while(1){}
}

void dukes_of_hazard_music(){
    configPin(GPIOA, GPIO_PIN_1, ALT_FUNC_PUSH_PULL);
    setBPM(200);

    while(1){
        play_note("E5", 8);
        play_note("C5", 8);
        play_note("A4", 4);
        play_note("A4", 4);
        play_note("A4", 8);
        play_note("B4", 8);
        play_note("C5", 8);
        play_note("D5", 8);
        play_note("E5", 4);
        play_note("E5", 8);
        play_note("E5", 4);
        play_note("C5", 4);
        play_pause(1);
        play_pause(1);

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
    enable_uart_clocks();


    startScheduler();
    createNewProcess(process1);
    //createNewProcess(testUSART);
    createNewProcess(testDelay);
    //createNewProcess(test_pwm);
    createNewProcess(testADC);
    //createNewProcess(testTIM2);
    createNewProcess(testTIM4);
    //createNewProcess(play_music);
    //createNewProcess(dukes_of_hazard_music);

    process1();
}
