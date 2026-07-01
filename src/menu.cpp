#include <lcd.h>
#include <project.h>
#include <eeprom.h>
#include <gameLogic.h>

volatile char menuOptions[33] = {'P', 'L', 'A', 'Y', ' ', 'M', 'U', 'T', 'E', '/', 'U', 'N', 'M', 'U', 'T', 'E', ' ', 'A', 'B', 'O', 'U', 'T', ' ', 'H', 'I', 'G', 'H', 'S', 'C', 'O', 'R', 'E', ' '};
volatile short currMenu = 0;
volatile int highScore;

void startMenu()
{

    sendLine("Reaction Game");

    gameState = GameStates::MENU;
}

void switchOption()
{

    lcdInstruction(0xc0);

    sendLine("                ");

    lcdInstruction(0xc0);

    sendData('*');

    int NumberOfSpaces = 0;

    for (int i = 0; i > -1; i++)
    {
        if (menuOptions[i] == ' ')
        {
            NumberOfSpaces += 1;
        }

        if (NumberOfSpaces == currMenu)
        {
            if (menuOptions[i] == ' ')
            {
            }

            else
            {
                sendData(menuOptions[i]);
            }
        }

        if (NumberOfSpaces > currMenu)
        {
            break;
        }
    }
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