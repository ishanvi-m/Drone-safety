// --- actuators.h ---
#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

void Timer_Init_PWM(void);
void Motor_Init(void);
void Motor_Set_Speed(uint8_t speed);
void Motor_Stop(void);
void LED_Set_Pattern(uint8_t state); 

#ifdef __cplusplus
}
#endif

#endif