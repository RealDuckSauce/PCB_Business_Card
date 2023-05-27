# PCB Business Card Particle Simulation

![alt text](https://imgur.com/a/iTSjqdG)

This is a personal project, creating a coin-cell powered PCB business card with a simple particle simulation.

## Design
The design utilises an 8x8 square led matrix, run by the HT16K33 LED driver. 

The pitch and roll of the card are determined by an ADXL335 accelerometer. 

All is controlled by an Atemga328p.

The scope of the stimulation includes just one particle in 2D space; for simplicity.

## Assembly
The circuit may be assesmbled on a breadboard, or manurfactured on a PCB.
The schematic for the cicuit is posted within this repo.

On a breadboard:
The cicuit can be contructed with commercially available modules, namely:
- Arduino Nano/Uno (or any MCU)
- Adafruit 8x8 Mini LED Matrix w/Backpack (PID 870)
- ADXL335 Accelerometer module (integrates 3.3v supply and resistor network)

## Programming

Ensure you have the Arduino IDE with the following libraries installed:

- Adafruit GFX
- Adafruit LED Backpack

The PCB cannot be programmed without an ISP programmer, as there is no serial interface on board.
See the ardunio documentation regardgin this process:
https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP

- Connect an ISP programmer to the ISP header
- Flash the Atmega328p: Either with a bootloader first, or the project code directly.

That's all!

## Tuning the Behaviour of the Simulation

Feel free to tune any of the constants that are declared in the beginning of the code to your liking.
You can change the elasticity, acceleration multiplier, and others.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
