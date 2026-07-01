#pragma once
#include <Arduino.h>
#include <avr/io.h>
#include <pin_config.h>



void pciInit()
{

  // ENAEBLE PCIE0,1 AND 2 INTERREPT
  PCICR |= (1 << PCIE1) | (1 << PCIE0) | (1 << PCIE2);

  // ENABLE IO PINS
  PCMSK0 |= (1 << PCINT5); // BTN_FIRST

  PCMSK1 |= (1 << PCINT8); // BTN_SECOND

  PCMSK2 |= (1 << PCINT23); // BTN_THIRD

  // 1. Set PINS as inputs
  DDRC &= ~(1 << BTN_SECOND);
  DDRB &= ~(1 << BTN_FIRST);
  DDRD &= ~(1 << BTN_THIRD);

  // 2. Enable the internal pull-up resistorS on pins
  PORTC |= (1 << BTN_SECOND);
  PORTB |= (1 << BTN_FIRST);
  PORTD |= (1 << BTN_THIRD);
}