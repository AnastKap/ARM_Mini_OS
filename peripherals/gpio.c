#include "gpio.h"
#include <stdint.h>

/*-------------------------------------------------------------------------------------------------------------------*/
/*    GPIOs    */
/*-------------------------------------------------------------------------------------------------------------------*/

#define CONFIG(GPIOx_CRL, GPIOx_CRH) {																	\
	switch(gpio_mode){																										\
		case OUTPUT_PUSH_PULL:																							\
			modey = 0b10;																											\
			cnfy = 0b00;																											\
			break;																														\
		case OUTPUT_OPEN_DRAIN:																							\
			modey = 0b11;																											\
			cnfy = 0b01;																											\
			break;																														\
		case ALT_FUNC_PUSH_PULL:																						\
			modey = 0b11;																											\
																													\
			cnfy = 0b10;																											\
			break;																														\
		case ALT_FUNC_OPEN_DRAIN:																						\
			modey = 0b11;																											\
			cnfy = 0b11;																											\
			break;																														\
		default:																														\
			break;																														\
	}																																			\
	uint32_t current;																											\
	if(pin < 8){																													\
		current = GPIOx_CRL & ~((uint32_t)0b1111 << (pin*4)); 							\
		GPIOx_CRL = (cnfy << ((pin*4) + 2)) | (modey << (pin*4));						\
		GPIOx_CRL = current	| GPIOx_CRL;																		\
	}																																			\
		else{																																\
		current = GPIOx_CRH & ~((uint32_t)0b1111 << ((pin - 8)*4));					\
		GPIOx_CRH = ((cnfy << (((pin - 8)*4) + 2))) | 											\
					(modey << ((pin - 8)*4));																			\
		GPIOx_CRH = current	| GPIOx_CRH; 																		\
	}																																			\
}




void configPin(uint8_t port, uint8_t pin, uint8_t gpio_mode){
	uint32_t cnfy, modey;
	switch(port){
		case GPIOA:
			CONFIG(GPIOA_CRL, GPIOA_CRH);
			break;
		case GPIOB:
			CONFIG(GPIOB_CRL, GPIOB_CRH);
			break;
		case GPIOC:
			CONFIG(GPIOC_CRL, GPIOC_CRH);
			break;
		default:
			break;
	}
}



void setPin(uint8_t port, uint8_t pin, uint8_t value){
	uint32_t current;
	switch(port){
		case GPIOA:
			current = GPIOA_ODR & (~(((uint32_t)1) << pin));
			GPIOA_ODR = current | ((uint32_t)value << pin);
			break;
		case GPIOB:
			current = GPIOB_ODR & (~(((uint32_t)1) << pin));
			GPIOB_ODR = current | ((uint32_t)value << pin);
			break;
		case GPIOC:
			current = GPIOC_ODR & (~(((uint32_t)1) << pin));
			GPIOC_ODR = current | ((uint32_t)value << pin);
			break;
		default:
			break;
	}
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*    TIMERS    */
/*-------------------------------------------------------------------------------------------------------------------*/

void setTimer(uint32_t timer,uint8_t direction,uint16_t value){
  uint32_t *curr; //pointer to registers addresses

  curr = timer+TIMX_DIER;
  *curr = 0x0001; //enable update interrupt

  curr = timer+TIMX_ARR;
  *curr = value; //set reload value

  curr = timer+TIMX_CR1;
  *curr |= (direction<<4)|(0b1); //set direction bit and CEN=1
}

void setPWM(uint32_t timer, uint32_t duty_cycle, uint32_t freq){
	setTimer(timer,UP,freq);
	uint32_t *curr;

	curr = timer+TIMx_CCR1; //using just the 1st channel
	*curr = duty_cycle;

}
