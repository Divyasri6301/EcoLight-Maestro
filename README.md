
# EcoLight Maestro

Time & Intensity Adaptive Street Light Automation System

## Overview

EcoLight Maestro is an intelligent street lighting system developed using the ARM7 LPC2129 microcontroller. The system automatically controls street lights based on ambient light intensity and real-time clock scheduling to reduce energy consumption and improve efficiency.

## Features

* Automatic day/night switching using LDR
* RTC-based scheduling
* Interrupt-driven architecture
* Keypad-based RTC configuration
* Manual override functionality
* Energy-efficient operation

## Hardware Used

* LPC2129 ARM7 Microcontroller
* LDR Sensor
* RTC
* LCD Display
* Keypad
* LEDs
* Power Supply

## Software Used

* Embedded C
* Keil µVision
* Flash Magic

## Working Principle

The system continuously monitors ambient light using an LDR sensor. Based on light intensity and RTC timing, the controller automatically switches street lights ON or OFF. Users can configure time settings through a keypad interface.
```mermaid
graph TD
    Start([Start]) --> InitLCD[Initialize LCD]
    InitLCD --> InitRTC[Initialize RTC]
    InitRTC --> InitADC[Initialize ADC]
    InitADC --> ReadTime[Read Time]
    ReadTime --> CheckDN{Check Day/Night}
    CheckDN --> ReadLDR[Read LDR]
    ReadLDR --> CtrlLED[Control LEDs]
    CtrlLED --> Interrupt{Interrupt?}
    
    Interrupt -- Yes --> OpenMenu[Open RTC Menu]
    OpenMenu --> UpdateParam[Update Parameters]
    UpdateParam --> Return([Return])
    
    Interrupt -- No --> ReadTime
## Results

* Reduced unnecessary daytime power consumption.
* Achieved approximately 30–40% energy savings.
* Real-time street light automation.

## Author

DivyaSri
