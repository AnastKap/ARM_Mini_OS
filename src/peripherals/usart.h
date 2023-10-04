#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART2_BASE      0x40004400

#define USART2_SR       *(volatile uint32_t*)(USART2_BASE + 0x00)
#define USART2_DR       *(volatile uint32_t*)(USART2_BASE + 0x04)
#define USART2_BRR      *(volatile uint32_t*)(USART2_BASE + 0x08)
#define USART2_CR1      *(volatile uint32_t*)(USART2_BASE + 0x0c)
#define USART2_CR2      *(volatile uint32_t*)(USART2_BASE + 0x10)
#define USART2_CR3      *(volatile uint32_t*)(USART2_BASE + 0x14)
#define USART2_GPTR     *(volatile uint32_t*)(USART2_BASE + 0x18)


// USARTx_SR shift bits
#define CTS           9
#define LBD           8
#define TXE           7
#define TC            6
#define RXNE          5
#define IDLE          4
#define ORE           3
#define NE            2
#define FE            1
#define PE            0


// USARTx_BRR shift bits
#define DIV_Mantissa  4
#define DIV_Fraction  0


// USARTx_CR1 shift bits
#define UE            13
#define M             12
#define WAKE          11
#define PCE           10
#define PS            9
#define PEIE          8
#define TXEIE         7
#define TCIE          6
#define RXNEIE        5
#define IDLEIE        4
#define TE            3
#define RE            2
#define RWU           1
#define SBK           0



// USARTx_CR2 shift bits
#define LINEN         14
#define STOP          12
#define CLKEN         11
#define CPOL          10
#define CPHA          9
#define LBCL          8
#define LBDIE         6
#define LBDL          5
#define ADD           0




// USARTx_CR3 shift bits
#define CTSIE         10
#define CTSE          9
#define RTSE          8
#define DMAT          7
#define DMAR          6
#define SCEN          5
#define NACK          4
#define HDSEL         3
#define IRLP          2
#define IREN          1
#define EIE           0



// USARTx_GPTR shift bits
#define GT            8
#define PSC           0


void startUSART(uint32_t baudrate);

void startUSARTTransmission();
void sendByteViaUSART(uint8_t byte);



#endif
