
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
Start
   ↓
Initialize LCD
   ↓
Initialize RTC
   ↓
Initialize ADC
   ↓
Read Time
   ↓
Check Day/Night
   ↓
Read LDR
   ↓
Control LEDs
   ↓
Interrupt?
   ↓
Open RTC Menu
   ↓
Update Parameters
   ↓
Return

## Results

* Reduced unnecessary daytime power consumption.
* Achieved approximately 30–40% energy savings.
* Real-time street light automation.

## Author

DivyaSri
