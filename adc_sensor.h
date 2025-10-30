// --- adc_sensor.h ---
#ifndef ADC_SENSOR_H
#define ADC_SENSOR_H
#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

void ADC_Init(void);
uint16_t ADC_Read_Gas(void); // Gas sensor reading (A0)
uint16_t USONIC_Get_Distance(void); // Uses simplified timing/polling

#ifdef __cplusplus
}
#endif

#endif