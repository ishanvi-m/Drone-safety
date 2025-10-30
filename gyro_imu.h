// --- gyro_imu.h ---
#ifndef GYRO_IMU_H
#define GYRO_IMU_H
#include <avr/io.h>
#include <util/delay.h>

#ifdef __cplusplus
extern "C" {
#endif

void I2C_Init(void);
void IMU_Init(void);
int16_t IMU_Get_Roll_Degrees(void); // Used for orientation detection

#ifdef __cplusplus
}
#endif

#endif