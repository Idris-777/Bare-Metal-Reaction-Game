
#include <Arduino.h>
#include <avr/io.h>
#include <pin_config.h>
#include <lcd.h>
#include <timer.h>
#include <interrepts.h>
#include <buttons.h>
#include <gameLogic.h>
#include <buzzer.h>
#include <menu.h>
#include <eeprom.h>
#include <project.h>

volatile short currLed = 0b100;
volatile short rnd = 0;
volatile short count = 0;
volatile int time = 0;
volatile bool blinking = false;
volatile char menuOptions[33] = {'P', 'L', 'A', 'Y', ' ', 'M', 'U', 'T', 'E', '/', 'U', 'N', 'M', 'U', 'T', 'E', ' ', 'A', 'B', 'O', 'U', 'T', ' ', 'H', 'I', 'G', 'H', 'S', 'C', 'O', 'R', 'E', ' '};
volatile short currMenu = 0;
volatile int highScore;
GameStates gameState = GameStates::MENU;
ButtonPressed btnPressed = ButtonPressed::Null;

int main()
{

  Serial.begin(9600);

  initialize();

  // sendLine("Reaction Time:");

  startMenu();

  pciInit();

  ledInit();

  timer1Init();

  switchOption();

  // randLed();

  buzzerInit();
  buzzerOff();

  while (1)
  {

    switch (gameState)
    {

    case MENU:
      switch (btnPressed)
      {

      case FirstBtnPressed:

        nextOption();
        btnPressed = ButtonPressed::Null;
        break;

      case SecondBtnPressed:

        selectOption();
        btnPressed = ButtonPressed::Null;
        break;

      case ThirdBtnPressed:

        backToMenu();
        btnPressed = ButtonPressed::Null;
        break;
      }

      break;

    case PLAY:
    {

      if (blinking)
      {
        switchLed();
        blinking = false;
      }

      switch (btnPressed)

      {
      case SecondBtnPressed:

        btnInGame(0b00000010);
        btnPressed = ButtonPressed::Null;
        break;

      case FirstBtnPressed:

        btnInGame(0b00000100);
        btnPressed = ButtonPressed::Null;
        break;

      case ThirdBtnPressed:

        btnInGame(0b00000001);
        btnPressed = ButtonPressed::Null;
        break;

        switchLed();
      }

      break;
    }

    case (WON):
      wonMechanics();
      Serial.println("winning sound");
      break;

    case LOST:
      looseMechanics();
      break;

    case NEXTROUND:
      gameState = GameStates::PLAY;
      nextRoundSound();
      randLed();
      break;
    }
  }

  return 0;
}

ISR(TIMER1_OVF_vect)
{
  blinking = true;
}

ISR(PCINT1_vect)
{
  if (!(PINC & (1 << BTN_SECOND)))
  {
    btnPressed = ButtonPressed::SecondBtnPressed;
    time = round((TCNT1 * 64.0) / 1000.0);
  }
}

ISR(PCINT0_vect)
{
  if (!(PINB & (1 << BTN_FIRST))){
  btnPressed = ButtonPressed::FirstBtnPressed;
  time = round((TCNT1 * 64.0) / 1000.0);
  }
}

ISR(PCINT2_vect)
{
  if (!(PIND & (1 << BTN_THIRD))){
  btnPressed = ButtonPressed::ThirdBtnPressed;
  time = round((TCNT1 * 64.0) / 1000.0);
  }
}