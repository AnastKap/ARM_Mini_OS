#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>


/*
 * General interrupt-specific definitions
 */

// Function to attach an interrupt handler to a specific address (hence to a specific interrupt)   DOES NOT WORK; PRODUCES HARD FAULT
void attachHandler(void *mem_address, void *handler_address);




/*
 * SysTick - specific definitions
 */

#define SYSTICK_VT_ADDR		0x3c

#define SYST_CSR			*(volatile uint32_t *) 0xe000e010
#define SYST_RVR			*(volatile uint32_t *) 0xe000e014
#define SYST_CVR			*(volatile uint32_t *) 0xe000e018
#define SYST_CALIB			*(volatile uint32_t *) 0xe000e01c


/*
  NVIC registers:
  Each register (ISERn/ICERn/ISPRn/ICPRn) controls 32 interrupts.
  n = 0: interrupts in positions 0-31
  n = 1: interrupts in positions 32-61
  .
  .
  .
*/

//Interrupt Set Enable Register
#define NVIC_ISER0    *(volatile uint32_t*) 0xE000E100
#define NVIC_ISER1    *(volatile uint32_t*) 0xE000E104
#define NVIC_ISER2    *(volatile uint32_t*) 0xE000E108
#define NVIC_ISER3    *(volatile uint32_t*) 0xE000E10C
#define NVIC_ISER4    *(volatile uint32_t*) 0xE000E110
#define NVIC_ISER5    *(volatile uint32_t*) 0xE000E114
#define NVIC_ISER6    *(volatile uint32_t*) 0xE000E118
#define NVIC_ISER7    *(volatile uint32_t*) 0xE000E11C

//Interrupt Clear Enable Register (disable interrupts)
#define NVIC_ICER0    *(volatile uint32_t*) 0xE000E180
#define NVIC_ICER1    *(volatile uint32_t*) 0xE000E184
#define NVIC_ICER2    *(volatile uint32_t*) 0xE000E188
#define NVIC_ICER3    *(volatile uint32_t*) 0xE000E18C
#define NVIC_ICER4    *(volatile uint32_t*) 0xE000E190
#define NVIC_ICER5    *(volatile uint32_t*) 0xE000E194
#define NVIC_ICER6    *(volatile uint32_t*) 0xE000E198
#define NVIC_ICER7    *(volatile uint32_t*) 0xE000E19C


//Interrupts
#define TIM2_IRQ    28
#define TIM3_IRQ    29
#define TIM4_IRQ    30
#define TIM5_IRQ    50

// Set the reload value; value is between 0 and 0x00ffffff
void setSystickReload(uint32_t value);
// Enable SysTick along with its interrupt; First the reload value must have been loaded
void enableSystick();

//Enable interrupt function
void setInterrupt(uint32_t position);

//Disable interrupt function
void clearInterrupt(uint32_t position);

// Interrupt Handlers
__attribute__((interrupt("FIQ"))) void HardFault_ISR();

__attribute__((interrupt("IRQ"))) void TIM2_ISR();

__attribute__((interrupt("IRQ"))) void TIM3_ISR();

__attribute__((interrupt("IRQ"))) void TIM4_ISR();

__attribute__((interrupt("IRQ"))) void TIM5_ISR();
#endif
