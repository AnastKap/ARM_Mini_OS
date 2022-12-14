#ifndef CONTEXT_SWITCHING_H
#define CONTEXT_SWITCHING_H

void Reset_ISR();
void NMI();
void HardFAult();
void MemManage();
void BusFault();
void UsageFault();
void SVCall();
void DebugMonitor();
void PendSV();
void SysTick_ISR();

#endif