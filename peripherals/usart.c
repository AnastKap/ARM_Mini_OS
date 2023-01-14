#include "usart.h"
#include "gpio.h"
#include <stdint.h>


void startUSART(uint32_t baudrate){
  configPin(GPIOA, GPIO_PIN_2, ALT_FUNC_PUSH_PULL);
  configPin(GPIOA, GPIO_PIN_3, ALT_FUNC_PUSH_PULL);

  USART2_CR1 = (1 << UE) | (0 << M);
  USART2_CR2 = (00 << STOP);
  USART2_BRR = (baudrate << DIV_Mantissa);
}

// Sends idle sequence
void startUSARTTransmission(){
  // Make the TE Pulse as needed
  USART2_CR1 &= ~(1 << TE);
  USART2_CR1 |= (1 << TE);
}

void sendByteViaUSART(uint8_t byte){
  USART2_DR = byte;  // Data transmission automatically starts
}
