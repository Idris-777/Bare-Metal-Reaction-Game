
#pragma once
#include <avr/io.h>
#include <Arduino.h>
#include <timer.h>

void buzzerInit()
{

  DDRB |= (1 << PB3);

  timer2Init();

  OCR2A = 0;
}

void buzzerSound(int freq)
{

  if (freq == 0)
  {
    OCR2A = 0;
  }

  OCR2A = ((16000000L) / (2 * 64 * freq)) - 1;
}

void buzzerOff()
{
  TCCR2A &= ~(1 << COM2A1);
  TCCR2A &= ~(1 << COM2A0);
}

void buzzerOn()
{
  TCCR2A &= ~(1 << COM2A1);
  TCCR2A |= (1 << COM2A0);
}

void winningSound()
{

  buzzerOn();

  buzzerSound(262);
  _delay_ms(40);

  buzzerOff();
  _delay_ms(15);

  buzzerSound(523);
  _delay_ms(120);

  buzzerOff();
}

void losingSound()
{

  buzzerOn();

  buzzerSound(400);
  _delay_ms(200);

  buzzerOff();
}

void nextRoundSound()
{

  buzzerOn();

  buzzerSound(250);
  _delay_ms(25);

  buzzerOff();
}