

#include <Arduino.h>
#include <avr/io.h>
#include <pin_config.h>
#include <project.h>
#include <lcd.h>
#include <eeprom.h>

void switchLed()
{

  count += 1;

  TCNT1 = 64723;

  PORTB = (PORTB & 0b11100000) | currLed;

  currLed >>= 1;

  if (currLed == 0)
  {
    currLed = 0b100;
  }

  if (count == rnd)
  {
    TIMSK1 &= ~(1 << TOIE1);
    count = 0;
    currLed = 0b100;
    TCNT1 = 0;
  }
}

void randLed()
{
  rnd = random(30) + 5;
  // SET TIMER1 VALUE
  count = 0;
  TCNT1 = 64723;
  blinking = true;
  TIMSK1 |= (1 << TOIE1);
  switchLed();
}

void ledInit()
{
  // SET PINS TO LED AS OUTPUT
  DDRB |= (1 << LED_FIRST) | (1 << LED_SECOND) | (1 << LED_THIRD);
}

void play()
{
  randLed();

  lcdInstruction(0x80);

  sendLine("Reaction Time:");

  printTime(0);
}

void About()
{
  lcdInstruction(0x80);

  sendLine("A simple Game");

  lcdInstruction(0xc0);

  sendLine("by Idris-777");
}

void highScoreMenue()
{
  readHighScore();

  lcdInstruction(0x01);
  _delay_ms(2);

  lcdInstruction(0x80);

  sendLine("Highscore:");

  lcdInstruction(0xC0);

  sendNumber(highScore);

  sendLine("ms");
}

void wonMechanics()
{

  if (btnPressed != ButtonPressed::Null)
  {
    gameState = GameStates::NEXTROUND;
    btnPressed = ButtonPressed::Null;
  }
}

void looseMechanics()
{

  PORTB &= ~((1 << 0) | (1 << 1) | (1 << 2));

  if (btnPressed != ButtonPressed::Null)
  {
    gameState = GameStates::NEXTROUND;
    btnPressed = ButtonPressed::Null;
  }
}