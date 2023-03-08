#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC1_BASE    0x40012400
#define ADC2_BASE    0x40012800
#define ADC3_BASE    0x40013c00


#define ADC1_SR       *(volatile uint32_t*) (ADC1_BASE + 0x00)
#define ADC1_CR1      *(volatile uint32_t*) (ADC1_BASE + 0x04)
#define ADC1_CR2      *(volatile uint32_t*) (ADC1_BASE + 0x08)
#define ADC1_SMPR1    *(volatile uint32_t*) (ADC1_BASE + 0x0c)
#define ADC1_SMPR2    *(volatile uint32_t*) (ADC1_BASE + 0x10)
#define ADC1_JOFR1    *(volatile uint32_t*) (ADC1_BASE + 0x14)
#define ADC1_JOFR2    *(volatile uint32_t*) (ADC1_BASE + 0x18)
#define ADC1_JOFR3    *(volatile uint32_t*) (ADC1_BASE + 0x1c)
#define ADC1_JOFR4    *(volatile uint32_t*) (ADC1_BASE + 0x20)
#define ADC1_HTR      *(volatile uint32_t*) (ADC1_BASE + 0x24)
#define ADC1_LTR      *(volatile uint32_t*) (ADC1_BASE + 0x28)
#define ADC1_SQR1     *(volatile uint32_t*) (ADC1_BASE + 0x2c)
#define ADC1_SQR2     *(volatile uint32_t*) (ADC1_BASE + 0x30)
#define ADC1_SQR3     *(volatile uint32_t*) (ADC1_BASE + 0x34)
#define ADC1_JSQR     *(volatile uint32_t*) (ADC1_BASE + 0x38)
#define ADC1_JDR1     *(volatile uint32_t*) (ADC1_BASE + 0x3c)
#define ADC1_JDR2     *(volatile uint32_t*) (ADC1_BASE + 0x40)
#define ADC1_JDR3     *(volatile uint32_t*) (ADC1_BASE + 0x44)
#define ADC1_JDR4     *(volatile uint32_t*) (ADC1_BASE + 0x48)
#define ADC1_DR       *(volatile uint32_t*) (ADC1_BASE + 0x4c)


#define ADON    0
#define CONT    1
#define EOC     1
#define CAL     2


void startContinuousConversion(uint8_t sequence[], uint8_t seq_len);

uint16_t readDataConverted();

#endif
