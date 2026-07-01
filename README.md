# AVR Reaction Game

A reaction time game built from scratch on the **ATmega328P** using **register-level programming** without relying on Arduino libraries for the core functionality.

The project was created to learn embedded systems by working directly with AVR peripherals such as timers, interrupts, EEPROM, GPIO, and LCD interfacing.

---

## Features

* 🎯 Random LED reaction game
* ⏱ Measures player's reaction time
* 💾 Stores best (lowest) reaction time in EEPROM
* 📟 16x2 LCD user interface
* 🔊 Sound effects for:

  * Winning
  * Losing
  * Menu navigation
  * Next round
* 📋 Interactive menu system
* 🔇 Mute/Unmute option
* ⚡ Interrupt-driven button handling
* 🎲 Randomized LED sequence

---

## Hardware Used

* Arduino Uno (ATmega328P)
* 16x2 HD44780 LCD
* 3 Push Buttons
* 3 LEDs
* Passive Buzzer
* Breadboard
* Resistors
* Jumper Wires

---

## Pin Assignment 

## Hardware Connections

| Component | ATmega328P Pin | Arduino Pin |
|-----------|----------------|-------------|
| LED 1 | PB0 | D8 |
| LED 2 | PB1 | D9 |
| LED 3 | PB2 | D10 |
| Buzzer | PB3 | D11 |
| LCD Enable (E) | PB4 | D12 |
| Button 1 | PB5 | D13 |
| LCD RS | PD6 | D6 |
| LCD D7 | PD5 | D5 |
| LCD D6 | PD4 | D4 |
| LCD D5 | PD3 | D3 |
| LCD D4 | PD2 | D2 |
| Button 3 | PD7 | D7 |
| Button 2 | PC0 | A0 |


## Software

* PlatformIO
* C++
* AVR Register Programming

---

## AVR Peripherals Used

### GPIO

* Direct port manipulation
* Button input
* LED control
* LCD interface

### Timers

* Timer1

  * LED timing
  * Reaction time measurement

* Timer2

  * Passive buzzer tone generation using PWM

### Interrupts

* Pin Change Interrupts (PCINT)
* Timer Overflow Interrupts

### EEPROM

* 16-bit high score storage
* High score retained after power loss

---

## Gameplay

1. Start the game from the menu.
2. LEDs cycle randomly.
3. Press the button corresponding to the lit LED.
4. Correct timing wins the round.
5. Incorrect input loses the round.
6. Fastest reaction time is automatically saved in EEPROM.

##
