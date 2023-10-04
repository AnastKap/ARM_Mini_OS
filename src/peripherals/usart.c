#include "usart.h"
#include "gpio.h"
#include "../clock/clock.h"
#include <stdint.h>


void startUSART(uint32_t baudrate){
  configPin(GPIOA, GPIO_PIN_2, ALT_FUNC_PUSH_PULL);
  configPin(GPIOA, GPIO_PIN_3, INPUT_PULL_UP_DOWN);

  USART2_CR1 = (1 << UE) | (0 << M);
  USART2_CR2 = (00 << STOP);

  // Set the baudrate
  uint32_t freq = getClockFreq()*1000;
  // Get HCLK (AHB clock)
  uint32_t ahb_pre = (RCC_CFGR >> HPRE) & 0b1111;
  if((ahb_pre >> 4) == 1){
      ahb_pre &= 0b111;
      for(uint8_t i = 0; i < ahb_pre; i++){
          if(i == 0b100) freq /= 2;
          freq /= 2;
      }
  }
  // Get APB1 clock
  uint32_t apb1_pre = (RCC_CFGR >> PPRE1) & 0b111;
  if((ahb_pre >> 4) == 1){
      ahb_pre &= 0b111;
      for(uint8_t i = 0; i < apb1_pre; i++){
          freq /= 2;
      }
  }

  uint32_t usartdiv = (freq*16)/baudrate;

  USART2_BRR = (usartdiv << DIV_Mantissa);
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
