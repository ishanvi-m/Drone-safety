# 📄 README: Drone-Based Safety System (Low-Level AVR)

## 1. Project Overview

This project implements a **Drone-Based Safety System** on an Arduino Uno (ATmega328P) using **low-level register programming only**. The system monitors environmental and orientation hazards, performing self-stabilization and critical safety actions.

The core idea is that the system must continuously sense its orientation using the gyro sensor and perform stabilization or corrective actions when it tilts, falls, or experiences unusual motion.

## 2. Decision Thresholds and States

The system classifies its state into one of three modes: **NORMAL, WARNING, or CRITICAL**  by fusing data from all sensors.

| State | Primary Sensor Condition | Suggested Automated Response | LCD & LED Indicator |
| :--- | :--- | :--- | :--- |
| **NORMAL** |Temp 20–30 °C, Roll/Pitch $\approx 0^\circ$ | [Low-power monitoring, periodic sampling | LCD: NORMAL, LED: Green (Steady) |
| **WARNING** |Isolated Overheat ($\ge 40^\circ\text{C}$) **OR** Obstacle ($<20\ \text{cm}$) during movement  | Halt corrective motor movement, show warning | LCD: WARNING, LED: Yellow (Slow Blink) |
| **CRITICAL** |]Gas $\mathbf{\ge 500}$ ADC value **OR** Tilt $\mathbf{\ge 45^\circ}$ |Immediate lockout, motor ON (ventilation) or motor OFF (fire)  | LCD: CRITICAL, LED: Red (Rapid Flash) |

---

## 3. Mandatory Threshold Values

The following numeric values are defined in the source code (`DroneSafetySystem.ino`) for the Decision Logic:

| Parameter | Threshold Value | Reference Requirement |
| :--- | :--- | :--- |
| **Tilt (Correction Trigger)** | **$> 15^\circ$** | Gyro/IMU polled to detect tilt events. |
| **Tilt (Critical Lockout)** | **$\mathbf{\ge 45^\circ}$** | Required for Scenario 5: Device fell, triggering critical lockout. |
| **Gas Sensor (Critical)** | **ADC Value $\ge 500$** | High concentration threshold for immediate CRITICAL alert. |
| **Temperature (Warning)** | **$\ge 40^\circ\text{C}$** | Threshold for Overheat (isolated) WARNING. |
| **Ultrasonic (Obstacle)** | **$< 20\ \text{cm}$** | Distance threshold for collision/obstacle during stabilization. |

---

## 4. How to Reproduce and Demonstrate Scenarios

The judge can use these steps to verify the system's compliance with the core requirements and automated response].

### Scenario 1: CRITICAL - Gas Leak and Ventilation (Response: Motor ON)

1.  **System State:** Ensure the device is stable and monitoring (NORMAL state).
2.  **Trigger:** Introduce a test gas source (e.g., alcohol vapor) near the gas sensor until the raw ADC value surpasses **500**.
3.  **Expected Outcome:** The system should transition immediately to **CRITICAL**. The Red LED should flash, the LCD should display the alert, and the **DC Motor must activate** (to simulate ventilation/gas dispersal).

### Scenario 2: CRITICAL - Toppled Device + Hazard (Response: Motor OFF/Lockout)

1.  **Trigger 1:** Introduce gas near the sensor (ADC $\mathbf{\ge 500}$).
2.  **Trigger 2:** While gas is detected, quickly tilt or invert the device past the $\mathbf{45^\circ}$ threshold.
3.  **Expected Outcome:** The system should enter the CRITICAL lockout state. The **DC Motor must stop** (or remain off if not running), the Red LED flashes, and the system requests human intervention.

### Scenario 3: WARNING - Obstacle while Correction

1.  **Trigger 1 (Tilt):** Tilt the device $\mathbf{\approx 18^\circ}$ to trigger the stabilization logic and activate motor correction.
2.  **Trigger 2 (Obstacle):** While the motor is running, place an object less than $\mathbf{20\ \text{cm}}$ from the ultrasonic sensor.
3.  **Expected Outcome:** The system should transition to **WARNING**. The **corrective motor movement must halt**, the motor should back off, and the Yellow LED should blink.

---

## 5. Source Code and Compilation

The entire system's logic is contained within the single **`DroneSafetySystem.ino`** file. All register definitions (DDRx, TCCR1A, TWCR, ADCSRA, etc.) are **manually defined** within the source code to satisfy the low-level programming constraint.

To reproduce the project, upload this single file to an **Arduino Uno SMD** after selecting the board type in the Arduino IDE.
