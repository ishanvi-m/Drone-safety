// --- DroneSafetySystem.ino ---

// Required AVR headers for register access
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Include all custom module headers
#include "gyro_imu.h"
#include "adc_sensor.h"
#include "actuators.h"
#include "display.h"
#include "timer_safety.h" 

// --- Global System State Variables ---
volatile uint8_t system_state = 0; // 0=NORMAL, 1=WARNING, 2=CRITICAL
uint8_t slow_task_counter = 0;

// --- Threshold Definitions (Must be documented in README) ---
#define TILT_CRITICAL_DEG   45   // Critical Tilt > 45 degrees
#define GAS_CRITICAL_ADC    500  // Raw ADC value for CRITICAL gas
#define DISTANCE_WARNING_CM 20   // Obstacle < 20cm
#define SLOW_TASK_INTERVAL  50   // 50 * 100ms = 5s for DHT11/Gas slow polling


void system_init(void) {
    // 1. Hardware Initializations using low-level registers
    I2C_Init();       
    ADC_Init();       
    Timer_Init_PWM(); 
    
    // 2. Safety and Polling Timers
    Timer0_Init_Polling(); // Start 100ms timer
    WDT_Init_Failsafe();   // Start Watchdog Timer

    // 3. Module Initializations
    IMU_Init();       
    LCD_Init();       
    Motor_Init();     
    
    sei(); // Enable Global Interrupts (must be called after WDT is set up)
    
    LCD_Update_Status("Drone Safety INIT", "STANDBY");
}

// Placeholder for slow tasks (e.g., DHT11 or power analysis)
void execute_slow_tasks(void) {
    // In a final build, DHT11_Read() would be called here.
    // For now, it updates the LCD to prove the 5-second cycle is running.
    LCD_command(0xC0 + 10); // Go to position 10 on line 2
    LCD_data('S');
    LCD_data('L');
}

// --- Main State Machine Logic ---
void check_and_set_state(void) {
    // 1. Get Sensor Data (fast polling, 100ms interval)
    int16_t roll_deg = IMU_Get_Roll_Degrees(); 
    uint16_t gas_val = ADC_Read_Gas();         
    uint16_t distance_cm = USONIC_Get_Distance(); 
    
    // Check if slow tasks (DHT11/Gas low-rate) need to run (every 5 seconds)
    if (++slow_task_counter >= SLOW_TASK_INTERVAL) {
        execute_slow_tasks();
        slow_task_counter = 0;
    }
    
    // --- 2. State Logic Check ---
    if (gas_val >= GAS_CRITICAL_ADC || roll_deg >= TILT_CRITICAL_DEG) {
        system_state = 2; // CRITICAL
    }
    else if (gas_val > (GAS_CRITICAL_ADC * 0.5) || distance_cm < DISTANCE_WARNING_CM) {
        system_state = 1; // WARNING
    }
    else {
        system_state = 0; // NORMAL
    }

    // --- 3. Act on the New State ---
    switch (system_state) {
        case 0: // NORMAL
            LED_Set_Pattern(0); 
            Motor_Stop();
            LCD_Update_Status("NORMAL", "T:25 G:Low");
            break;
        case 1: // WARNING
            LED_Set_Pattern(1); 
            // Implement halt and back-off for obstacle (Scen. 6)
            Motor_Stop();
            LCD_Update_Status("WARNING!", "Obstacle/Tilt");
            break;
        case 2: // CRITICAL
            LED_Set_Pattern(2); 
            Motor_Set_Speed(255); // Motor ON (Ventilation for Gas Leak - Scen. 3)
            LCD_Update_Status("CRITICAL!", "GAS/TILT/FIRE");
            break;
    }
}


// The standard Arduino setup function
void setup() {
    system_init();
}

// The standard Arduino loop function
void loop() {
    // 1. MUST reset the WDT at the start of every loop iteration to prevent reset
    WDT_Reset_Sequence(); 
    
    // 2. Check the flag set by the non-blocking Timer0 interrupt (100ms)
    if (timer_100ms_flag) {
        timer_100ms_flag = 0; // Clear the flag
        
        // Execute the fast polling and state checking tasks
        check_and_set_state(); 
    }
    
    // 3. Optional: Insert power saving (SLEEP MODE) here to save battery
}