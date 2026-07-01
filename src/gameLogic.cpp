

#include <Arduino.h>
#include <avr/io.h>
#include <pin_config.h>
#include <project.h>
#include <lcd.h>
#include <eeprom.h>

volatile short currLed = 0b100;
volatile short rnd = 0;
volatile short count = 0;
volatile int time = 0;
volatile bool blinking = false;

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

  PORTB &= ~((1 << LED_FIRST) | (1 << LED_SECOND) | (1 << LED_THIRD));

  if (btnPressed != ButtonPressed::Null)
  {
    gameState = GameStates::NEXTROUND;
    btnPressed = ButtonPressed::Null;
  }
}

int calcReactTime(){

  return round((TCNT1 * 64.0) / 1000.0);

  

}