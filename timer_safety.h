// --- timer_safety.h ---
#ifndef TIMER_SAFETY_H
#define TIMER_SAFETY_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

// Use C-Linkage for compilation safety
#ifdef __cplusplus
extern "C" {
#endif

// Global flag set by the Timer0 interrupt
extern volatile uint8_t timer_100ms_flag;

void Timer0_Init_Polling(void);
void WDT_Init_Failsafe(void);
void WDT_Reset_Sequence(void);

#ifdef __cplusplus
}
#endif

#endif