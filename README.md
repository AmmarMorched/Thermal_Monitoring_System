# Environmental Monitoring System with Automated Control

## Project description

The “Environmental Monitoring System with Automated Control” is an Arduino based project that aims to monitor various environmental parameters such as ambient temperature and color. The system uses components such as DS1621, TCS34725, LCD I2C, a servo motor, 2 LEDs, a button, and an SD card module.

## Features

- Real-time display of ambient temperature and color on the I2C LCD screen.
- Saving temperature and color data to an SD card.
- Automated servo motor control to adjust a physical object based on temperature.
- One button operation to activate or deactivate the system and automated control.
- Indicator LEDs to signal system status.

## Hardware Configuration

- DS1621 for temperature measurement.
- TCS34725 for color measurement.
- I2C LCD for display.
- Servo motor for automated control.
- 2 LEDs for visual indicators.
- Button to activate/deactivate the system.
- SD card module for data recording.

## Software Configuration

The Arduino source code is available in the [code](code/) directory. Make sure you have the necessary libraries installed.

## Installation and Use Instructions

1. Connect the components according to the diagram provided in the [schema](schema/) directory.
2. Download the source code from the [code](code/) directory and upload it to your Arduino board.
3. Make sure to install the required libraries.
4. Power on the system and observe the data on the LCD screen.
5. Use the button to turn the system on/off.
6. View the data saved on the SD card.

## Connection Diagram

Refer to the [connection diagram](diagram/) to help you connect the components correctly.

## Licence

This project is licensed under [MIT License](LICENSE).

---
