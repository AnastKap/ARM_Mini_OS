#include "context_switching.h"
#include "../interrupts/interrupt.h"
#include "../peripherals/gpio.h"

void *current_PCB_ptr;


void startScheduler(){
	setSystickReload(SCHEDULER_INTERVAL);
	enableSystick();
	//attachHandler((uint32_t *) 0x3c, SysTick_ISR);
}


#define CURRENT_PCB_HIGH		(uint32_t)&current_PCB_ptr >> 16
#define CURRENT_PCB_LOW			(uint32_t)&current_PCB_ptr & 0X0000ffff


__attribute__ ((interrupt ("FIQ"))) void SysTick_ISR(){
	current_PCB_ptr = 0x20004980;
	__asm volatile(	"push {r0} \n"
					"ldr r0, current_PCB \n"
					"ldr r0, [r0] \n"
				   	"stmia r0, {r1 - r12, lr} \n"
				   	"mov r1, r0 \n"
					"pop {r0} \n"
				   	"str r0, [r1] \n"
				   	"add r1, r1, #12\n"
				   	"mrs r0, apsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, ipsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, epsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, iepsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, iapsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, eapsr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, psr\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, msp\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   	"mrs r0, psp\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   "mrs r0, primask\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   "mrs r0, basepri\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   "mrs r0, basepri_max\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   "mrs r0, faultmask\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
				   "mrs r0, control\n"
				   	"add r1, r1, #1\n"
				   "str r0, [r1] \n"
					""
				   	""
				   	"current_PCB: .word current_PCB_ptr");
	/*__asm volatile("push {r0} \n \
					mov r0, %0 \n \
					lsr r0, r0, #16 \n \
					orr r0, r0, %1 \n \
				    str r0, [r0]" \
				  : : "i" (x), "i" (current_PCB_ptr));*/
	/*set_pin(GPIOC, GPIO_PIN_13, 0);
    for (int i = 0; i < 200000; i++);
    set_pin(GPIOC, GPIO_PIN_13, 1);
    for (int i = 0; i < 200000; i++);*/
}