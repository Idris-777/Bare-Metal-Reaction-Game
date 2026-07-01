
#include <Arduino.h>
#include <avr/io.h>
#include <project.h>
#include <gameLogic.h>
#include <string.h>
#include <lcd.h>
#include <menu.h>
#include <pin_config.h>
#include <buzzer.h>
#include <eeprom.h>

void btnInGame(uint8_t btn_mask)
{

  
    if ((PORTB & 0b00000111) == btn_mask)
    {

     PORTB |= (1 << LED_FIRST) | (1 << LED_SECOND) | (1 << LED_THIRD);
      printTime(time);
      gameState = GameStates::WON;
      winningSound();

      if ((time < highScore))
      {

        highScore = time;

        writeHighScore();
      }
    }
    else
    {
      gameState = GameStates::LOST;
      losingSound();
    }
  }




void nextOption()
{

  if (!(PINB & (1 << PB5)))
  {

    if (currMenu == 3)
    {
      currMenu = 0;
      switchOption();
      nextRoundSound();
    }

    else

    {

      currMenu += 1;
      switchOption();
      nextRoundSound();
    }
  }
}

void backToMenu()
{
  if (!(PIND & (1 << PD7)))
  {
    lcdInstruction(0x80);
    sendLine("Reaction Game");
    switchOption();
  }
}

void selectOption()
{
  if (!(PINC & (1 << PC0)))
  {

    if (currMenu == 0)
    {
      gameState = GameStates::PLAY;
      play();
    }

    else if (currMenu == 1)
    {

      if ((DDRB & (1 << PB3)))
      {

        DDRB &= ~(1 << BUZZER);
      }

      else
      {
        DDRB |= (1 << BUZZER);
      }
    }

    else if (currMenu == 2)
    {
      gameState = GameStates::ABOUT;

      About();
    }

    else if (currMenu == 3)
    {
      gameState = GameStates::HIGHSCORE;

      highScoreMenue();
    }

    nextRoundSound();
  }
}