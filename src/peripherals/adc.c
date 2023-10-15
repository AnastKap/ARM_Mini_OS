#include "adc.h"
#include <stdint.h>

// TODO: 
void startContinuousConversion(uint8_t sequence[], uint8_t seq_len){
  uint8_t i;
  //ADC1_CR2 |= (1 << CAL);
  // Set the length
  ADC1_SQR1 &= ~0b1111;
  ADC1_SQR1 |= ((seq_len - 1) & 0b1111);

  for(i = 0; i < seq_len; i++){
      ADC1_SQR3 &= ~(0b11111 << i*5);
      ADC1_SQR3 |= sequence[i] & 0b11111;
  }

  // Enable ADC Conversion
  ADC1_CR2 |= (1 << CONT);
  ADC1_CR2 |= (1 << ADON);
  ADC1_CR2 |= (1 << CAL);
  ADC1_CR2 |= (1 << ADON);
}

/*
 * Returns converted data
 */
uint16_t readDataConverted(){
  while(!((ADC1_SR >> EOC) & 1));
  ADC1_SR &= ~(1 << EOC);
  return (uint16_t)ADC1_DR & 0xffff;
}
