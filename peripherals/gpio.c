#include "gpio.h"
#include <stdint.h>


#define CONFIG(GPIOx_CRL, GPIOx_CRH) 								\
	switch(gpio_mode){												\
		case OUTPUT_PUSH_PULL:										\
			modey = 0b11;											\
			cnfy = 0b00;												\
			break;													\
		default:													\
			break;													\
	}																\
	uint32_t current;												\
	if(pin < 8){													\
		current = GPIOx_CRL; 										\
		GPIOx_CRL = (cnfy << ((pin*4) + 2)) | (modey << (pin*4));	\
		GPIOx_CRL = (current & ~(0b1111 << (pin*4))) | GPIOx_CRL;	\
	}																\
	else{															\
		current = GPIOx_CRH;										\
		GPIOx_CRH = ((cnfy << (((pin - 8)*4) + 2))) | 				\
					(modey << ((pin - 8)*4));						\
		GPIOx_CRH = (current & ~(0b1111 << ((pin - 8)*4))) 			\
			| GPIOx_CRH;											\
	}

void config_pin(uint8_t port, uint8_t pin, uint8_t gpio_mode){
	uint32_t cnfy, modey;
	switch(port){
		case GPIOA:
			break;
		case GPIOB:
			break;
		case GPIOC:
			CONFIG(GPIOC_CRL, GPIOC_CRH);
			break;
		default:
			break;
	}
}

#define GPIOC13 (1 << 13UL)
void set_pin(uint8_t port, uint8_t pin, uint8_t value){
	uint32_t current;
	switch(port){
		case GPIOC:
			current = GPIOC_ODR & (~(((uint32_t)1) << pin));
			GPIOC_ODR = current | ((uint32_t)value << pin);
			break;
		default:
			break;
	}
}