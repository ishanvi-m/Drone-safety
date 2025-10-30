// --- timer_safety.c ---
#include "timer_safety.h"

volatile uint8_t timer_100ms_flag = 0;

/**
 * @brief Initializes Timer/Counter 0 for 100ms periodic interrupts.
 */
void Timer0_Init_Polling(void) {
    // CTC mode, Prescaler 1024, OCR0A = 1562
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS02) | (1 << CS00);
    OCR0A = 1562; 
    TIMSK0 |= (1 << OCIE0A); 
}

/**
 * @brief Watchdog Timer (WDT) Initialization for a 1.0 second timeout.
 */
void WDT_Init_Failsafe(void) {
    // Clear WDE and set WDT change enable sequence
    WDTCSR |= (1 << WDCE) | (1 << WDE); 
    
    // Set WDE=1 (WDT Enable), WDP2=1, WDP1=1 for ~1.0s timeout
    WDTCSR = (1 << WDE) | (1 << WDP2) | (1 << WDP1);
}

/**
 * @brief Must be called periodically to prevent WDT reset.
 */
void WDT_Reset_Sequence(void) {
    wdt_reset(); 
}

// --- Timer0 Interrupt Service Routine (ISR) ---
ISR(TIMER0_COMPA_vect) {
    timer_100ms_flag = 1;
}