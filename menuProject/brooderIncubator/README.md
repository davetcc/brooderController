## Brooder and Incubator

This project is a control facility based around an Uno or other ATMega32x controller.

## Wiring

### Rotary encoder

All inputs

A: 2
B: A5
OK: A4


### LCD display

Standard 16x2 LCD connected directly. Backlight always on. All outputs

D0-D3: 9, 10, 11, 12 
RS: 8
EN: 7

### POWER_OFF

This is taken from the PSU and will cause an immediate write to ROM. Input

Pin: 5

### FAN Control

The fan is current boosted by a transistor, output turns on fan.

Pin: 13

### Heater control

The heater control is provided by a triac circuit with zero cross. Output turns on heater.

Pin: 7

### Speaker

The speaker is a small speaker connected to a PWM pin and pulsed.

Pin: 6

