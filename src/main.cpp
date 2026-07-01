
#include <Arduino.h>
#include <avr/io.h>
#include <pin_config.h>
#include <lcd.h>
#include <timer.h>
#include <pcint.h>
#include <buttons.h>
#include <gameLogic.h>
#include <buzzer.h>
#include <menu.h>
#include <eeprom.h>
#include <project.h>

GameStates gameState = GameStates::MENU;
ButtonPressed btnPressed = ButtonPressed::Null;

int main()
{

  

  initialize();

  startMenu();

  pciInit();

  ledInit();

  timer1Init();

  switchOption();

  buzzerInit();

  buzzerOff();

  while (1)

  //

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
      }

      break;
    }

    case ABOUT:
      if (btnPressed = ButtonPressed::ThirdBtnPressed)
      {
        gameState = GameStates::MENU;

        break;
      }

    case HIGHSCORE:
      if (btnPressed = ButtonPressed::ThirdBtnPressed)
      {
        gameState = GameStates::MENU;
        break;
      }

    case (WON):
      wonMechanics();
      
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
    if (gameState == GameStates::PLAY)
    {
      time = calcReactTime();
    }
  }
}

ISR(PCINT0_vect)
{
  if (!(PINB & (1 << BTN_FIRST)))
  {
    btnPressed = ButtonPressed::FirstBtnPressed;
    if (gameState == GameStates::PLAY)
    {
      time = calcReactTime();
    }
  }
}

ISR(PCINT2_vect)
{
  if (!(PIND & (1 << BTN_THIRD)))
  {
    btnPressed = ButtonPressed::ThirdBtnPressed;
    if (gameState == GameStates::PLAY)
    {
      time = calcReactTime();
    }
  }
}