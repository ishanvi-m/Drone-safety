// --- actuators.c ---
#include "actuators.h"

// Pin Assignments for Registers (Digital Pin 10 = PB2)
#define MOTOR_PWM_PIN  PB2 
#define MOTOR_DIR_PIN  PD7 // Digital Pin 7

void Timer_Init_PWM(void) {
    DDRB |= (1<<MOTOR_PWM_PIN); // Set D10 as Output
    
    // Fast PWM Mode 14 (TCCR1A/B: WGM13:10 = 1110)
    TCCR1A |= (1<<WGM11) | (1<<COM1B1); 
    TCCR1B |= (1<<WGM13) | (1<<WGM12);
    
    // Prescaler F_CPU/64 
    TCCR1B |= (1<<CS11) | (1<<CS10); 
    
    // Set TOP value for 8-bit resolution
    ICR1 = 255; 
}

void Motor_Init(void) {
    DDRD |= (1<<MOTOR_DIR_PIN);
    PORTD &= ~(1<<MOTOR_DIR_PIN); // Set fixed direction
}

void Motor_Set_Speed(uint8_t speed) {
    OCR1B = speed; // Set PWM duty cycle (0-255)
}

void Motor_Stop(void) {
    OCR1B = 0; // Set duty cycle to 0
}

void LED_Set_Pattern(uint8_t state) {
    // Set LED pins (D3, D4, D5) as outputs
    DDRD |= (1<<PD3) | (1<<PD4) | (1<<PD5);
    
    // Simple state-based lighting logic (flashing handled by Timer0 logic)
    switch (state) {
        case 0: // NORMAL (D3 ON)
            PORTD = (PORTD & 0xE7) | (1<<PD3); 
            break;
        case 1: // WARNING (D4 ON)
            PORTD = (PORTD & 0xE7) | (1<<PD4);
            break;
        case 2: // CRITICAL (D5 ON)
            PORTD = (PORTD & 0xE7) | (1<<PD5);
            break;
        default:
            PORTD &= 0xE7; // All off (Clear D3, D4, D5)
            break;
    }
}