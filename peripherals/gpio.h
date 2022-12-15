#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

// Define the base addresses for ports A,B,C
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000


// Define port A registers
#define GPIOA_CRL			*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH			*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR			*(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR			*(volatile uint32_t *)(GPIOA_BASE + 0x0c)
#define GPIOA_BSRR			*(volatile uint32_t *)(GPIOA_BASE + 0x10)
#define GPIOA_BRR			*(volatile uint32_t *)(GPIOA_BASE + 0x14)
#define GPIOA_LCKR			*(volatile uint32_t *)(GPIOA_BASE + 0x18)

// Define port B registers
#define GPIOB_CRL			*(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH			*(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR			*(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR			*(volatile uint32_t *)(GPIOB_BASE + 0x0c)
#define GPIOB_BSRR			*(volatile uint32_t *)(GPIOB_BASE + 0x10)
#define GPIOB_BRR			*(volatile uint32_t *)(GPIOB_BASE + 0x14)
#define GPIOB_LCKR			*(volatile uint32_t *)(GPIOB_BASE + 0x18)

// Define port C registers
#define GPIOC_CRL			*(volatile uint32_t *)(GPIOC_BASE + 0x00)
#define GPIOC_CRH			*(volatile uint32_t *)(GPIOC_BASE + 0x04)
#define GPIOC_IDR			*(volatile uint32_t *)(GPIOC_BASE + 0x08)
#define GPIOC_ODR			*(volatile uint32_t *)(GPIOC_BASE + 0x0c)
#define GPIOC_BSRR			*(volatile uint32_t *)(GPIOC_BASE + 0x10)
#define GPIOC_BRR			*(volatile uint32_t *)(GPIOC_BASE + 0x14)
#define GPIOC_LCKR			*(volatile uint32_t *)(GPIOC_BASE + 0x18)



// General definitions
#define GPIOA 1
#define GPIOB 2
#define GPIOC 3

#define GPIO_PIN_13 13


// GPIO modes
#define OUTPUT_PUSH_PULL		0
#define OUTPUT_OPEN_DRAIN		1
#define ALT_FUNC_PUSH_PULL		2
#define ALT_FUNC_OPEN_DRAIN		3

void config_pin(uint8_t port, uint8_t pin, uint8_t gpio_mode);
void set_pin(uint8_t port, uint8_t pin, uint8_t value);

#endif
