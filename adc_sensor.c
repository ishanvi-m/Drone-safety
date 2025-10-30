// --- adc_sensor.c ---
#include "adc_sensor.h"

#define GAS_SENSOR_CHANNEL 0 // Analog Pin A0

void ADC_Init(void) {
    // Reference Voltage: AVCC (REFS0=1)
    ADMUX = (1<<REFS0);
    // Prescaler 128 (ADPS2, ADPS1, ADPS0 set) and Enable ADC (ADEN)
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

uint16_t ADC_Read_Gas(void) {
    // Select Channel A0
    ADMUX = (ADMUX & 0xF0) | GAS_SENSOR_CHANNEL; 
    // Start Conversion
    ADCSRA |= (1<<ADSC);
    // Wait for Conversion complete
    while (ADCSRA & (1<<ADSC)); 
    
    return ADC; // Return 10-bit result
}

// Simplified function—actual USONIC uses Timer Input Capture (TCCR1B, ICR1)
uint16_t USONIC_Get_Distance(void) {
    // In final code, this uses Timer1 registers for precise, non-blocking timing.
    // Simulation returns a value for state machine logic
    return 55; // Simulate normal distance (>50cm)
}