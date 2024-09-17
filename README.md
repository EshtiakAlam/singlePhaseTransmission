# Single Phase Transmission Line Fault Detection with Arduino

## Overview
This project implements a real-time fault detection system for single-phase transmission lines using an Arduino MEGA 2560, current sensors (ACS712), and relays. The system alerts users through LEDs and a piezo buzzer when faults such as short circuits or power theft are detected.

## Features
- Real-time detection of faults (e.g., short circuits, power theft)
- Visual (LED) and audible (buzzer) alerts
- Simple, cost-effective hardware setup

## Components
- Arduino MEGA 2560
- ACS712 Current Sensors
- Relays
- LEDs and Piezo Buzzer

## Installation
1. Clone the repository.
2. Set up the hardware as per the circuit diagram.
3. Upload the provided Arduino code to your Arduino MEGA 2560.

## Usage
- The system continuously monitors the current in the transmission line.
- If a fault is detected (current drops below the threshold), the system will trigger visual and audio alerts, and the relay will disconnect the faulty circuit.

